#ifndef RFT_SENSOR_SERIAL_HARDWARE_RFT_SENSOR_HARDWARE_HPP_
#define RFT_SENSOR_SERIAL_HARDWARE_RFT_SENSOR_HARDWARE_HPP_

#include <memory>
#include <string>
#include <vector>
#include <array>

#include "hardware_interface/sensor_interface.hpp"
#include "hardware_interface/system_interface.hpp"
#include "hardware_interface/handle.hpp"
#include "hardware_interface/hardware_info.hpp"
#include "rclcpp/macros.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_lifecycle/state.hpp"
#include "rft_sensor_serial/RFT_COM.h"

namespace rft_sensor_serial
{

class RFTSensorHardware : public hardware_interface::SensorInterface
{
public:
  RFTSensorHardware() = default;

  hardware_interface::CallbackReturn on_init(const hardware_interface::HardwareInfo & info) override;

  std::vector<hardware_interface::StateInterface> export_state_interfaces() override;

  hardware_interface::CallbackReturn on_activate(const rclcpp_lifecycle::State & previous_state) override;
  hardware_interface::CallbackReturn on_deactivate(const rclcpp_lifecycle::State & previous_state) override;

  hardware_interface::return_type read(const rclcpp::Time & time, const rclcpp::Duration & period) override;

private:
  CRT_RFT_UART sensor_;
  std::array<double, 3> forces_ = {0.0, 0.0, 0.0};
  std::array<double, 3> torques_ = {0.0, 0.0, 0.0};

  rclcpp::Logger logger_ = rclcpp::get_logger("RFTSensorHardware");
};

}  // namespace rft_sensor_serial

#endif  // RFT_SENSOR_SERIAL_HARDWARE_RFT_SENSOR_HARDWARE_HPP_