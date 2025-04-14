// impedance_effort_controller/include/impedance_effort_controller/impedance_effort_controller.hpp
#ifndef IMPEDANCE_EFFORT_CONTROLLER__IMPEDANCE_EFFORT_CONTROLLER_HPP_
#define IMPEDANCE_EFFORT_CONTROLLER__IMPEDANCE_EFFORT_CONTROLLER_HPP_

#include <string>
#include <vector>
#include <array>
#include <Eigen/Dense>

#include "controller_interface/controller_interface.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_lifecycle/state.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
#include "realtime_tools/realtime_buffer.hpp"
#include "geometry_msgs/msg/wrench_stamped.hpp"

namespace impedance_effort_controller
{

class ImpedanceEffortController : public controller_interface::ControllerInterface
{
public:
  ImpedanceEffortController();

  controller_interface::CallbackReturn on_init() override;

  controller_interface::InterfaceConfiguration command_interface_configuration() const override;

  controller_interface::InterfaceConfiguration state_interface_configuration() const override;

  controller_interface::CallbackReturn on_configure(
    const rclcpp_lifecycle::State & previous_state) override;

  controller_interface::CallbackReturn on_activate(
    const rclcpp_lifecycle::State & previous_state) override;

  controller_interface::CallbackReturn on_deactivate(
    const rclcpp_lifecycle::State & previous_state) override;

  controller_interface::return_type update(
    const rclcpp::Time & time, const rclcpp::Duration & period) override;

protected:
  // Existing member variables
  std::vector<std::string> joint_names_;
  std::vector<double> p_gains_;
  std::vector<double> i_gains_;
  std::vector<double> d_gains_;
  std::vector<double> stiffness_;
  std::vector<double> prev_errors_;
  std::vector<double> integral_terms_;
  
  // Robot link parameters
  double l1_;
  double l2_;
  
  // Command buffer for position commands
  realtime_tools::RealtimeBuffer<std::vector<double>> position_command_buffer_;
  std::vector<double> position_command_;

  // Force/Torque sensor subscription
  rclcpp::Subscription<geometry_msgs::msg::WrenchStamped>::SharedPtr ft_sensor_sub_;
  realtime_tools::RealtimeBuffer<geometry_msgs::msg::WrenchStamped> ft_sensor_buffer_;
  geometry_msgs::msg::WrenchStamped latest_ft_sensor_data_;
  std::array<double, 3> bias_force_;
  
  // Callback for force/torque sensor data
  void ft_sensor_callback(const geometry_msgs::msg::WrenchStamped::SharedPtr msg);

  // Existing helper functions
  void calculate_jacobian(double q1, double q2, std::vector<std::vector<double>> & jacobian);
  void transform_force_to_base_frame(
    const std::array<double, 3>& ee_force,
    const std::array<double, 3>& ee_torque,
    double q1, double q2,
    std::array<double, 3>& base_force,
    std::array<double, 3>& base_torque);
  void force_to_joint_torques(
    const std::array<double, 3> & force, 
    const std::array<double, 3> & torque,
    const std::vector<double> & joint_positions,
    std::vector<double> & output);
    
  // --- New Impedance Control Parameters ---
  Eigen::MatrixXd Md_;      // Desired inertia (M_d)
  Eigen::MatrixXd Kd_;      // Desired damping (K_d)
  Eigen::MatrixXd Kp_;      // Desired stiffness (K_p)
  Eigen::MatrixXd Phi_;     // Filter gain (Φ)
  Eigen::MatrixXd Lambda_;  // Control gain (Λ)
  Eigen::VectorXd gamma_;   // Adaptive state vector (γ)
  Eigen::VectorXd gamma_dot_; // Adaptive state derivative
  double rho_;              // Gain for discontinuous term (ρ)
  double varpi_;            // Threshold for the switching law (ϖ)
  
  // Store previous error values for derivative calculations
  Eigen::VectorXd e_prev_;
  Eigen::VectorXd e_dot_prev_;

  // --- Helper Function Declarations ---
  Eigen::VectorXd update_gamma(const Eigen::VectorXd& e,
                               const Eigen::VectorXd& tau_d,
                               double dt);
  Eigen::VectorXd calculate_s(const Eigen::VectorXd& e,
                              const Eigen::VectorXd& e_dot);
  Eigen::VectorXd calculate_delta_tau(const Eigen::VectorXd& s);
  Eigen::VectorXd compute_control_input(const Eigen::VectorXd& q_ddot_d,
                                        const Eigen::VectorXd& e,
                                        const Eigen::VectorXd& e_dot,
                                        const Eigen::VectorXd& delta_tau,
                                        const Eigen::VectorXd& tau_d);

private:  
  // Force filtering variables
  std::array<double, 3> filtered_base_force_;
  std::array<std::array<double, 2>, 3> past_inputs_;   // Store x[n-1], x[n-2] for each axis
  std::array<std::array<double, 2>, 3> past_outputs_;  // Store y[n-1], y[n-2] for each axis
  // Filter coefficients
  double b0_, b1_, b2_;  // Numerator coefficients
  double a1_, a2_;       // Denominator coefficients
};

}  // namespace impedance_effort_controller

#endif  // IMPEDANCE_EFFORT_CONTROLLER__IMPEDANCE_EFFORT_CONTROLLER_HPP_