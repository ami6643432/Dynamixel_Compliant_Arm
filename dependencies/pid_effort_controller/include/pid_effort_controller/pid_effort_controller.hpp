#ifndef PID_EFFORT_CONTROLLER__PID_EFFORT_CONTROLLER_HPP_
#define PID_EFFORT_CONTROLLER__PID_EFFORT_CONTROLLER_HPP_

#include <string>
#include <vector>

#include "controller_interface/controller_interface.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_lifecycle/state.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
#include "realtime_tools/realtime_buffer.hpp"

namespace pid_effort_controller
{

class PIDEffortController : public controller_interface::ControllerInterface
{
public:
  PIDEffortController();

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
  std::vector<std::string> joint_names_;
  std::vector<double> p_gains_;
  std::vector<double> i_gains_;
  std::vector<double> d_gains_;

  // Previous error terms for D control
  std::vector<double> prev_errors_;
  // Accumulated error terms for I control
  std::vector<double> integral_terms_;
  
  // Command subscriber and buffer
  rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr position_command_sub_;
  realtime_tools::RealtimeBuffer<std::vector<double>> position_command_buffer_;

  // Target positions
  std::vector<double> position_command_;
};

}  // namespace pid_effort_controller

#endif  // PID_EFFORT_CONTROLLER__PID_EFFORT_CONTROLLER_HPP_