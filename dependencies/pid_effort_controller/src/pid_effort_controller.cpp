#include "pid_effort_controller/pid_effort_controller.hpp"

#include <algorithm>
#include <string>
#include <utility>

namespace pid_effort_controller
{

PIDEffortController::PIDEffortController() : controller_interface::ControllerInterface() {}

controller_interface::CallbackReturn PIDEffortController::on_init()
{
  try {
    // Initialize parameters
    auto_declare<std::vector<std::string>>("joints", std::vector<std::string>());
    auto_declare<std::vector<double>>("p_gains", std::vector<double>());
    auto_declare<std::vector<double>>("i_gains", std::vector<double>());
    auto_declare<std::vector<double>>("d_gains", std::vector<double>());
  } catch (const std::exception & e) {
    fprintf(stderr, "Exception thrown during init stage with message: %s \n", e.what());
    return controller_interface::CallbackReturn::ERROR;
  }
  return controller_interface::CallbackReturn::SUCCESS;
}

controller_interface::InterfaceConfiguration PIDEffortController::command_interface_configuration() const
{
  controller_interface::InterfaceConfiguration config;
  config.type = controller_interface::interface_configuration_type::INDIVIDUAL;
  for (const auto & joint_name : joint_names_) {
    config.names.push_back(joint_name + "/effort");
  }
  return config;
}

controller_interface::InterfaceConfiguration PIDEffortController::state_interface_configuration() const
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

controller_interface::CallbackReturn PIDEffortController::on_configure(
  const rclcpp_lifecycle::State & /*previous_state*/)
{
  // Get parameters
  joint_names_ = get_node()->get_parameter("joints").as_string_array();
  if (joint_names_.empty()) {
    RCLCPP_ERROR(get_node()->get_logger(), "No joints provided");
    return controller_interface::CallbackReturn::ERROR;
  }

  // Get gains
  p_gains_ = get_node()->get_parameter("p_gains").as_double_array();
  i_gains_ = get_node()->get_parameter("i_gains").as_double_array();
  d_gains_ = get_node()->get_parameter("d_gains").as_double_array();

  // Verify gains size matches number of joints
  if (p_gains_.size() != joint_names_.size() || 
      i_gains_.size() != joint_names_.size() || 
      d_gains_.size() != joint_names_.size()) {
    RCLCPP_ERROR(get_node()->get_logger(), "Gains size does not match number of joints");
    return controller_interface::CallbackReturn::ERROR;
  }

  // Initialize command buffers
  position_command_ = std::vector<double>(joint_names_.size(), 0.0);
  position_command_buffer_.writeFromNonRT(position_command_);

  // Initialize error terms
  prev_errors_ = std::vector<double>(joint_names_.size(), 0.0);
  integral_terms_ = std::vector<double>(joint_names_.size(), 0.0);

  // Create subscriber for commands
  position_command_sub_ = get_node()->create_subscription<std_msgs::msg::Float64MultiArray>(
    "~/commands", 10,
    [this](const std_msgs::msg::Float64MultiArray::SharedPtr msg) {
      if (msg->data.size() != joint_names_.size()) {
        RCLCPP_ERROR(
          get_node()->get_logger(),
          "Received %zu positions but expected %zu", msg->data.size(), joint_names_.size());
        return;
      }
      position_command_buffer_.writeFromNonRT(msg->data);
    });

  RCLCPP_INFO(get_node()->get_logger(), "Configure successful");
  return controller_interface::CallbackReturn::SUCCESS;
}

controller_interface::CallbackReturn PIDEffortController::on_activate(
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

controller_interface::CallbackReturn PIDEffortController::on_deactivate(
  const rclcpp_lifecycle::State & /*previous_state*/)
{
  // Reset commands to zero
  std::vector<double> zero_commands(joint_names_.size(), 0.0);
  position_command_buffer_.writeFromNonRT(zero_commands);
  
  return controller_interface::CallbackReturn::SUCCESS;
}

controller_interface::return_type PIDEffortController::update(
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

  // Get latest commands
  position_command_ = *position_command_buffer_.readFromRT();

  // Process each joint
  for (size_t i = 0; i < joint_names_.size(); ++i) {
    // Get current position from state interface
    const double current_position = state_interfaces_[i * 3].get_value();
    
    // Compute position error
    const double error = position_command_[i] - current_position;
    
    // Update integral term
    integral_terms_[i] += error * period.seconds();
    
    // Compute derivative term (divide by zero is handled by period guarantees)
    const double derivative = (error - prev_errors_[i]) / period.seconds();
    
    // PID computation
    const double command = p_gains_[i] * error +                    // Proportional term
                          i_gains_[i] * integral_terms_[i] +        // Integral term
                          d_gains_[i] * derivative;                 // Derivative term
    
    // Store current error for next iteration
    prev_errors_[i] = error;
    
    // Set effort command
    command_interfaces_[i].set_value(command);
  }

  return controller_interface::return_type::OK;
}

}  // namespace pid_effort_controller

#include "pluginlib/class_list_macros.hpp"
PLUGINLIB_EXPORT_CLASS(
  pid_effort_controller::PIDEffortController,
  controller_interface::ControllerInterface)