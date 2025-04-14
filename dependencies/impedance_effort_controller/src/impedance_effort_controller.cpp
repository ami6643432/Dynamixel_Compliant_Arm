#include "impedance_effort_controller/impedance_effort_controller.hpp"
#include <algorithm>
#include <string>
#include <utility>

namespace impedance_effort_controller
{

ImpedanceEffortController::ImpedanceEffortController() : controller_interface::ControllerInterface() {}

controller_interface::CallbackReturn ImpedanceEffortController::on_init()
{
  try {
    // Existing parameter declarations
    auto_declare<std::vector<std::string>>("joints", std::vector<std::string>());
    auto_declare<std::vector<double>>("p_gains", std::vector<double>());
    auto_declare<std::vector<double>>("i_gains", std::vector<double>());
    auto_declare<std::vector<double>>("d_gains", std::vector<double>());
    auto_declare<std::vector<double>>("stiffness", std::vector<double>());

    auto_declare<double>("link_1_length", 0.25);
    auto_declare<double>("link_2_length", 0.25);
    
    auto_declare<std::string>("ft_sensor_topic", "/RFT_FORCE");
    auto_declare<bool>("use_relative_position", false);
    auto_declare<std::vector<double>>("home_position", std::vector<double>());
    auto_declare<std::vector<double>>("force_bias", {+5, 0, +27});
    
    // New impedance control parameters
    auto_declare<std::vector<double>>("desired_mass", std::vector<double>());
    auto_declare<std::vector<double>>("desired_damping", std::vector<double>());
    auto_declare<std::vector<double>>("desired_stiffness", std::vector<double>());
    auto_declare<std::vector<double>>("phi_initial", std::vector<double>());
    auto_declare<std::vector<double>>("gamma_initial", std::vector<double>());
    auto_declare<std::vector<double>>("lambda_matrix", std::vector<double>());
    auto_declare<double>("rho", 1.0);
    auto_declare<double>("varpi", 0.05);
  } catch (const std::exception & e) {
    fprintf(stderr, "Exception thrown during init stage with message: %s \n", e.what());
    return controller_interface::CallbackReturn::ERROR;
  }
  return controller_interface::CallbackReturn::SUCCESS;
}

controller_interface::InterfaceConfiguration ImpedanceEffortController::command_interface_configuration() const
{
  controller_interface::InterfaceConfiguration config;
  config.type = controller_interface::interface_configuration_type::INDIVIDUAL;
  for (const auto & joint_name : joint_names_) {
    config.names.push_back(joint_name + "/effort");
  }
  return config;
}

controller_interface::InterfaceConfiguration ImpedanceEffortController::state_interface_configuration() const
{
  controller_interface::InterfaceConfiguration config;
  config.type = controller_interface::interface_configuration_type::INDIVIDUAL;
  for (const auto & joint_name : joint_names_) {
    config.names.push_back(joint_name + "/position");
    config.names.push_back(joint_name + "/velocity");
    config.names.push_back(joint_name + "/effort");
  }
  return config;
}

controller_interface::CallbackReturn ImpedanceEffortController::on_configure(
  const rclcpp_lifecycle::State & /*previous_state*/)
{
  // Get parameters
  joint_names_ = get_node()->get_parameter("joints").as_string_array();
  if (joint_names_.empty()) {
    RCLCPP_ERROR(get_node()->get_logger(), "No joints provided");
    return controller_interface::CallbackReturn::ERROR;
  }

  // Force bias
  std::vector<double> bias_vec = get_node()->get_parameter("force_bias").as_double_array();
  bias_force_ = {bias_vec[0], bias_vec[1], bias_vec[2]};

  // Get gains
  p_gains_ = get_node()->get_parameter("p_gains").as_double_array();
  i_gains_ = get_node()->get_parameter("i_gains").as_double_array();
  d_gains_ = get_node()->get_parameter("d_gains").as_double_array();
  stiffness_ = get_node()->get_parameter("stiffness").as_double_array();

  // Verify gains size matches number of joints
  if (p_gains_.size() != joint_names_.size() || 
      i_gains_.size() != joint_names_.size() || 
      d_gains_.size() != joint_names_.size() ||
      stiffness_.size() != joint_names_.size()) {
    RCLCPP_ERROR(get_node()->get_logger(), "Number of gains does not match number of joints");
    return controller_interface::CallbackReturn::ERROR;
  }

  // Initialize vectors for PID control
  prev_errors_.resize(joint_names_.size(), 0.0);
  integral_terms_.resize(joint_names_.size(), 0.0);

  // Get robot link lengths
  l1_ = get_node()->get_parameter("link_1_length").as_double();
  l2_ = get_node()->get_parameter("link_2_length").as_double();

  // Create command subscriber and buffer
  position_command_buffer_.writeFromNonRT(std::vector<double>(joint_names_.size(), 0.0));

  // Create F/T sensor subscriber
  ft_sensor_sub_ = get_node()->create_subscription<geometry_msgs::msg::WrenchStamped>(
    get_node()->get_parameter("ft_sensor_topic").as_string(),
    rclcpp::SensorDataQoS(),
    std::bind(&ImpedanceEffortController::ft_sensor_callback, this, std::placeholders::_1));

  // --- New impedance control parameters ---
  std::vector<double> desired_mass = get_node()->get_parameter("desired_mass").as_double_array();
  std::vector<double> desired_damping = get_node()->get_parameter("desired_damping").as_double_array();
  std::vector<double> desired_stiffness = get_node()->get_parameter("desired_stiffness").as_double_array();
  std::vector<double> phi_initial = get_node()->get_parameter("phi_initial").as_double_array();
  std::vector<double> gamma_initial = get_node()->get_parameter("gamma_initial").as_double_array();
  std::vector<double> lambda_matrix = get_node()->get_parameter("lambda_matrix").as_double_array();
  rho_ = get_node()->get_parameter("rho").as_double();
  varpi_ = get_node()->get_parameter("varpi").as_double();

  // Validate sizes or set defaults
  size_t num_joints = joint_names_.size();
  
  // Initialize Eigen matrices (diagonal matrices for simplicity)
  Md_ = Eigen::MatrixXd::Zero(num_joints, num_joints);
  Kd_ = Eigen::MatrixXd::Zero(num_joints, num_joints);
  Kp_ = Eigen::MatrixXd::Zero(num_joints, num_joints);
  Phi_ = Eigen::MatrixXd::Zero(num_joints, num_joints);
  Lambda_ = Eigen::MatrixXd::Zero(num_joints, num_joints);
  gamma_ = Eigen::VectorXd::Zero(num_joints);
  gamma_dot_ = Eigen::VectorXd::Zero(num_joints);
  
  e_prev_ = Eigen::VectorXd::Zero(num_joints);
  e_dot_prev_ = Eigen::VectorXd::Zero(num_joints);

  // Fill matrices with parameter values
  for (size_t i = 0; i < num_joints; ++i) {
    // If parameters are provided, use them, otherwise use defaults
    if (i < desired_mass.size()) {
      Md_(i, i) = desired_mass[i];
    } else {
      Md_(i, i) = 1.0;  // Default mass
    }
    
    if (i < desired_damping.size()) {
      Kd_(i, i) = desired_damping[i];
    } else {
      Kd_(i, i) = d_gains_[i];  // Use existing D gain as default
    }
    
    if (i < desired_stiffness.size()) {
      Kp_(i, i) = desired_stiffness[i];
    } else {
      Kp_(i, i) = stiffness_[i];  // Use existing stiffness as default
    }
    
    if (i < phi_initial.size()) {
      Phi_(i, i) = phi_initial[i];
    } else {
      Phi_(i, i) = 5.0;  // Default filter gain
    }
    
    if (i < lambda_matrix.size()) {
      Lambda_(i, i) = lambda_matrix[i];
    } else {
      Lambda_(i, i) = 10.0;  // Default control gain
    }
    
    if (i < gamma_initial.size()) {
      gamma_(i) = gamma_initial[i];
    } else {
      gamma_(i) = 0.0;  // Default initial gamma
    }
  }

  b0_ = 0.020083365564211;
  b1_ = 0.040166731128422;
  b2_ = 0.020083365564211;
  a1_ = -1.561018075800718;
  a2_ = 0.641351538057562;

  // Initialize filter state arrays
  filtered_base_force_ = {0.0, 0.0, 0.0};
  for (size_t i = 0; i < 3; ++i) {
    past_inputs_[i] = {0.0, 0.0};
    past_outputs_[i] = {0.0, 0.0};
  }

  RCLCPP_INFO(get_node()->get_logger(), "Impedance controller configured with %zu joints", num_joints);
  return controller_interface::CallbackReturn::SUCCESS;
}


controller_interface::CallbackReturn ImpedanceEffortController::on_activate(
  const rclcpp_lifecycle::State & /*previous_state*/)
{
  // Reset error terms
  std::fill(prev_errors_.begin(), prev_errors_.end(), 0.0);
  std::fill(integral_terms_.begin(), integral_terms_.end(), 0.0);

  // Get current positions as initial commands
  position_command_.resize(joint_names_.size());
  for (size_t i = 0; i < joint_names_.size(); ++i) {
    position_command_[i] = state_interfaces_[i * 3].get_value();  // Get current position
  }
  position_command_buffer_.writeFromNonRT(position_command_);

  RCLCPP_INFO(get_node()->get_logger(), "Controller activated");
  return controller_interface::CallbackReturn::SUCCESS;
}

controller_interface::CallbackReturn ImpedanceEffortController::on_deactivate(
  const rclcpp_lifecycle::State & /*previous_state*/)
{
  // Reset commands to zero
  std::vector<double> zero_commands(joint_names_.size(), 0.0);
  position_command_buffer_.writeFromNonRT(zero_commands);
  
  return controller_interface::CallbackReturn::SUCCESS;
}

controller_interface::return_type ImpedanceEffortController::update(
  const rclcpp::Time & /*time*/, const rclcpp::Duration & period)
{
  if (state_interfaces_.empty()) {
    RCLCPP_ERROR_THROTTLE(
      get_node()->get_logger(),
      *get_node()->get_clock(),
      1000,
      "No state interfaces available");
    return controller_interface::return_type::ERROR;
  }

  const double dt = period.seconds();
  
  // Get latest commands
  position_command_ = *position_command_buffer_.readFromRT();

  // Get latest force/torque sensor data
  latest_ft_sensor_data_ = *ft_sensor_buffer_.readFromRT();

  // Extract force/torque data with bias correction
  const double fx = latest_ft_sensor_data_.wrench.force.x + bias_force_[0];
  const double fy = latest_ft_sensor_data_.wrench.force.y + bias_force_[1];
  const double fz = latest_ft_sensor_data_.wrench.force.z + bias_force_[2];
  const double tx = latest_ft_sensor_data_.wrench.torque.x;
  const double ty = latest_ft_sensor_data_.wrench.torque.y;
  const double tz = latest_ft_sensor_data_.wrench.torque.z;

  // Create force and torque arrays
  std::array<double, 3> ee_force = {fx, fy, fz};
  std::array<double, 3> ee_torque = {tx, ty, tz};
  
  // Get current joint positions and velocities
  std::vector<double> joint_positions(joint_names_.size());
  std::vector<double> joint_velocities(joint_names_.size());
  
  for (size_t i = 0; i < joint_names_.size(); ++i) {
    // Position is at index i*3, velocity at i*3+1
    joint_positions[i] = state_interfaces_[i * 3].get_value();
    joint_velocities[i] = state_interfaces_[i * 3 + 1].get_value();
  }

  // Transform forces to base frame
  std::array<double, 3> base_force;
  std::array<double, 3> base_torque;

  
  transform_force_to_base_frame(ee_force, ee_torque, 
                          joint_positions[0], joint_positions[1], 
                          base_force, base_torque);


  static bool first_run = true;
  if (first_run) {
    // Initialize filter states with current values
    for (size_t i = 0; i < 3; ++i) {
      filtered_base_force_[i] = base_force[i];
      past_inputs_[i][0] = base_force[i];
      past_inputs_[i][1] = base_force[i];
      past_outputs_[i][0] = base_force[i];
      past_outputs_[i][1] = base_force[i];
    }
    first_run = false;
  } else {
    // Apply second-order (biquad) IIR filter to each component
    for (size_t i = 0; i < 3; ++i) {
      // Compute filtered output: y[n] = b0*x[n] + b1*x[n-1] + b2*x[n-2] - a1*y[n-1] - a2*y[n-2]
      filtered_base_force_[i] = b0_ * base_force[i] + 
                                b1_ * past_inputs_[i][0] + 
                                b2_ * past_inputs_[i][1] - 
                                a1_ * past_outputs_[i][0] - 
                                a2_ * past_outputs_[i][1];
      
      // Update state variables for next iteration
      past_inputs_[i][1] = past_inputs_[i][0];
      past_inputs_[i][0] = base_force[i];
      past_outputs_[i][1] = past_outputs_[i][0];
      past_outputs_[i][0] = filtered_base_force_[i];
    }
  }

  // Calculate joint torques from external forces
  std::vector<double> force_torque_contribution(joint_names_.size(), 0.0);
  force_to_joint_torques(filtered_base_force_, base_torque, joint_positions, force_torque_contribution);

  // Convert to Eigen vectors for impedance control calculation
  Eigen::VectorXd q_d = Eigen::Map<Eigen::VectorXd>(position_command_.data(), position_command_.size());
  Eigen::VectorXd q = Eigen::Map<Eigen::VectorXd>(joint_positions.data(), joint_positions.size());
  Eigen::VectorXd q_dot = Eigen::Map<Eigen::VectorXd>(joint_velocities.data(), joint_velocities.size());
  Eigen::VectorXd tau_d = Eigen::Map<Eigen::VectorXd>(force_torque_contribution.data(), force_torque_contribution.size());

  // Calculate position and velocity errors
  Eigen::VectorXd e = q_d - q;
  Eigen::VectorXd e_dot;
  
  if (e_prev_.size() == e.size()) {
    // Numerical differentiation with smoothing
    double alpha = 0.7;  // Filter coefficient (0 < alpha < 1)
    
    // Calculate raw derivative
    Eigen::VectorXd raw_e_dot = (e - e_prev_) / dt;
    
    // Apply filtering to the derivative
    if (e_dot_prev_.size() == e.size()) {
      e_dot = alpha * raw_e_dot + (1 - alpha) * e_dot_prev_;
    } else {
      // First time execution, initialize e_dot_prev_
      e_dot = raw_e_dot;
      e_dot_prev_ = e_dot;
    }
  } else {
    // Initialize e_dot with zeros and e_prev for first iteration
    e_dot = Eigen::VectorXd::Zero(e.size());
    e_prev_ = e;
    e_dot_prev_ = e_dot;
  }
  
  // Store values for next iteration
  e_prev_ = e;
  e_dot_prev_ = e_dot;

  // ----------------------------------------------------
  // Impedance Control Implementation
  // ----------------------------------------------------
  
  // 1. Update adaptive state gamma
  gamma_ = update_gamma(e, tau_d, dt);

  // 2. Compute auxiliary error variable s
  Eigen::VectorXd s = calculate_s(e, e_dot);

  // 3. Compute switching term delta_tau
  Eigen::VectorXd delta_tau = calculate_delta_tau(s);

  // 4. Desired acceleration (zero for regulation tasks)
  Eigen::VectorXd q_ddot_d = Eigen::VectorXd::Zero(q.size());

  // 5. Compute control input
  Eigen::VectorXd tau = compute_control_input(q_ddot_d, e, e_dot, delta_tau, tau_d);

  // Apply control output to joints
  double max_effort = 600.0;  // Get from parameters
  for (size_t i = 0; i < joint_names_.size(); ++i) {
    tau(i) = std::clamp(tau(i), -max_effort, max_effort);
    command_interfaces_[i].set_value(tau(i));
  }

  // Store current error for next iteration
  e_prev_ = e;
  e_dot_prev_ = e_dot;

  RCLCPP_DEBUG(
    get_node()->get_logger(),
    "Control output: [%.2f, %.2f]",
    tau(0), tau(1));

  return controller_interface::return_type::OK;
}

  void ImpedanceEffortController::ft_sensor_callback(
    const geometry_msgs::msg::WrenchStamped::SharedPtr msg)
  {
    ft_sensor_buffer_.writeFromNonRT(*msg);
  }

  void ImpedanceEffortController::transform_force_to_base_frame(
    const std::array<double, 3>& ee_force,
    const std::array<double, 3>& ee_torque,
    double q1, double q2,
    std::array<double, 3>& base_force,
  std::array<double, 3>& base_torque)
{
  // Calculate total end effector angle relative to global frame
  double total_angle = q1 + q2;
  
  // Compute rotation matrix elements for Y-axis rotation
  double cos_theta = std::cos(total_angle);
  double sin_theta = std::sin(total_angle);
  
// Combine rotations (first apply 180° rotation, then apply -total_angle rotation)
// R_combined = R_y * R_y_180
std::array<std::array<double, 3>, 3> R_combined = {{
  {-cos_theta, 0.0, sin_theta},
  {0.0, 1.0, 0.0},
  {-sin_theta, 0.0, -cos_theta}
}};

// Apply combined rotation matrix to force vector
base_force[0] = R_combined[0][0] * ee_force[0] + R_combined[0][1] * ee_force[1] + R_combined[0][2] * ee_force[2];
base_force[1] = R_combined[1][0] * ee_force[0] + R_combined[1][1] * ee_force[1] + R_combined[1][2] * ee_force[2];
base_force[2] = R_combined[2][0] * ee_force[0] + R_combined[2][1] * ee_force[1] + R_combined[2][2] * ee_force[2];

// Apply combined rotation matrix to torque vector similarly
base_torque[0] = R_combined[0][0] * ee_torque[0] + R_combined[0][1] * ee_torque[1] + R_combined[0][2] * ee_torque[2];
base_torque[1] = R_combined[1][0] * ee_torque[0] + R_combined[1][1] * ee_torque[1] + R_combined[1][2] * ee_torque[2];
base_torque[2] = R_combined[2][0] * ee_torque[0] + R_combined[2][1] * ee_torque[1] + R_combined[2][2] * ee_torque[2];
  
  RCLCPP_DEBUG(
    get_node()->get_logger(),
    "Force transform: EE [%.2f, %.2f, %.2f] -> Base [%.2f, %.2f, %.2f]",
    ee_force[0], ee_force[1], ee_force[2], 
    base_force[0], base_force[1], base_force[2]);
}


  void ImpedanceEffortController::calculate_jacobian(
    double q1, double q2, std::vector<std::vector<double>> & jacobian)
  {
    // Ensure jacobian has correct dimensions
    jacobian.resize(2);
    jacobian[0].resize(2);
    jacobian[1].resize(2);
    
    // In your robot's configuration:
    // When q1=0, q2=0: arm points down (-Z direction)
    // When q1=π/2, q2=0: arm points in +X direction
    
    // Calculate trigonometric values once
    double c1 = std::cos(q1);
    double s1 = std::sin(q1);
    double c12 = std::cos(q1 + q2);
    double s12 = std::sin(q1 + q2);
    
    // Jacobian elements for this configuration
    // Note: This already accounts for the robot's default orientation
    jacobian[0][0] = -l1_ * s1 - l2_ * s12;  // dx/dq1
    jacobian[0][1] = -l2_ * s12;             // dx/dq2
    jacobian[1][0] = -l1_ * c1 - l2_ * c12;  // dz/dq1 (negative because Z is down)
    jacobian[1][1] = -l2_ * c12;             // dz/dq2 (negative because Z is down)

  }

  void ImpedanceEffortController::force_to_joint_torques(
    const std::array<double, 3> & base_force,  // Already in base frame
    const std::array<double, 3> & base_torque, // Already in base frame
    const std::vector<double> & joint_positions, 
    std::vector<double> & output)
  {
    // Get joint positions
    double q1 = joint_positions[0];
    double q2 = joint_positions[1];
    
    // For planar robot, only X and Z forces contribute to joint torques
    double fx_planar = 5*(base_force[0]);       // X force in base frame 
    double fy_planar = -base_force[2];      // Z force in base frame with sign flipped
    
    // Calculate Jacobian for current joint positions
    std::vector<std::vector<double>> jacobian;
    calculate_jacobian(q1, q2, jacobian);
    
    // Calculate joint torques: τ = J^T * F
    output[0] = jacobian[0][0] * fx_planar + jacobian[1][0] * fy_planar;
    output[1] = jacobian[0][1] * fx_planar + jacobian[1][1] * fy_planar;
    
    // Add rotational torque contribution if needed
    double torque_z_planar = base_torque[1];  // Y-axis torque in base frame
    output[0] += torque_z_planar * 0.5;       // Distribute evenly between joints
    output[1] += torque_z_planar * 0.5;
  }

  // Other methods for impedance control calculations
    Eigen::VectorXd ImpedanceEffortController::update_gamma(
    const Eigen::VectorXd& e,
    const Eigen::VectorXd& tau_d,
    double dt)
  {
    // Compute gamma_dot = Md^{-1} * (tau_d + (Kd - Md * Phi) * gamma)
    Eigen::MatrixXd Md_inv = Md_.inverse();
    gamma_dot_ = Md_inv * (tau_d + (Kd_ - Md_ * Phi_) * gamma_);
    
    // Integrate using Euler method
    return gamma_ + gamma_dot_ * dt;
  }

  Eigen::VectorXd ImpedanceEffortController::calculate_s(
    const Eigen::VectorXd& e,
    const Eigen::VectorXd& e_dot)
  {
    return e_dot + Phi_ * e + gamma_;
    // return e_dot + Phi_ * e;
  }

  Eigen::VectorXd ImpedanceEffortController::calculate_delta_tau(const Eigen::VectorXd& s)
  {
    double norm_s = s.norm();
    
    if (norm_s >= varpi_) {
      return -rho_ * s / norm_s;
    } else {
      return -rho_ * s / varpi_;
    }
  }

  Eigen::VectorXd ImpedanceEffortController::compute_control_input(
  const Eigen::VectorXd& q_ddot_d,
  const Eigen::VectorXd& e,
  const Eigen::VectorXd& e_dot,
  const Eigen::VectorXd& delta_tau,
  const Eigen::VectorXd& tau_d)
  {
    // Full impedance control law:
    // tau = -Lambda * s - tau_d + delta_tau + Md * (q_ddot_d - Phi * e_dot) - (Kd - Md * Phi) * gamma
    Eigen::VectorXd s = calculate_s(e, e_dot);
    
    // Calculate each term separately for clarity
    Eigen::VectorXd term1 = 1000 * Lambda_ * s;
    Eigen::VectorXd term2 = tau_d;
    Eigen::VectorXd term3 = delta_tau;
    Eigen::VectorXd term4 = Md_ * (q_ddot_d - Phi_ * e_dot);
    Eigen::VectorXd term5 = -(Kd_ - Md_ * Phi_) * gamma_;
    
    // Combine all terms to get the final control input
    return term1 + term2 + term3 + term4 + term5;
  }

}  // namespace impedance_effort_controller

#include "pluginlib/class_list_macros.hpp"
PLUGINLIB_EXPORT_CLASS(
  impedance_effort_controller::ImpedanceEffortController,
  controller_interface::ControllerInterface)