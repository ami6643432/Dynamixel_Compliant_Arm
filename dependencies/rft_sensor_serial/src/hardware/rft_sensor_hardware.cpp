#include "rft_sensor_serial/hardware/rft_sensor_hardware.hpp"

#include <string>
#include <vector>

namespace rft_sensor_serial
{

hardware_interface::CallbackReturn RFTSensorHardware::on_init(
  const hardware_interface::HardwareInfo & info)
{
  if (hardware_interface::SensorInterface::on_init(info) != CallbackReturn::SUCCESS)
  {
    return CallbackReturn::ERROR;
  }

  // Get parameters
  const auto port = info_.hardware_parameters["port"];
  const auto baud_rate = std::stoi(info_.hardware_parameters["baud_rate"]);

  RCLCPP_INFO(logger_, "Initializing RFT sensor on port %s at %d baud", port.c_str(), baud_rate);

  if (!sensor_.openPort(const_cast<char*>(port.c_str()), baud_rate)) {
    RCLCPP_ERROR(logger_, "Failed to open sensor port");
    return CallbackReturn::ERROR;
  }

  RCLCPP_INFO(logger_, "Successfully initialized RFT sensor");
  return CallbackReturn::SUCCESS;
}

std::vector<hardware_interface::StateInterface> RFTSensorHardware::export_state_interfaces()
{
  std::vector<hardware_interface::StateInterface> state_interfaces;
  
  // Force interfaces
  state_interfaces.emplace_back(
    hardware_interface::StateInterface(info_.sensors[0].name, "force.x", &forces_[0]));
  state_interfaces.emplace_back(
    hardware_interface::StateInterface(info_.sensors[0].name, "force.y", &forces_[1]));
  state_interfaces.emplace_back(
    hardware_interface::StateInterface(info_.sensors[0].name, "force.z", &forces_[2]));
  
  // Torque interfaces
  state_interfaces.emplace_back(
    hardware_interface::StateInterface(info_.sensors[0].name, "torque.x", &torques_[0]));
  state_interfaces.emplace_back(
    hardware_interface::StateInterface(info_.sensors[0].name, "torque.y", &torques_[1]));
  state_interfaces.emplace_back(
    hardware_interface::StateInterface(info_.sensors[0].name, "torque.z", &torques_[2]));

  return state_interfaces;
}

hardware_interface::CallbackReturn RFTSensorHardware::on_activate(
  const rclcpp_lifecycle::State & /*previous_state*/)
{
  RCLCPP_INFO(logger_, "Starting continuous force/torque readings");
  sensor_.rqst_FT_Continuous();
  return CallbackReturn::SUCCESS;
}

hardware_interface::CallbackReturn RFTSensorHardware::on_deactivate(
  const rclcpp_lifecycle::State & /*previous_state*/)
{
  RCLCPP_INFO(logger_, "Stopping continuous force/torque readings");
  sensor_.rqst_FT_Stop();
  return CallbackReturn::SUCCESS;
}

hardware_interface::return_type RFTSensorHardware::read(
  const rclcpp::Time & /*time*/, const rclcpp::Duration & /*period*/)
{
  if (sensor_.readWorker()) {
    forces_[0] = sensor_.m_RFT_IF_PACKET.m_rcvdForce[0];
    forces_[1] = sensor_.m_RFT_IF_PACKET.m_rcvdForce[1];  
    forces_[2] = sensor_.m_RFT_IF_PACKET.m_rcvdForce[2];
    torques_[0] = sensor_.m_RFT_IF_PACKET.m_rcvdForce[3];
    torques_[1] = sensor_.m_RFT_IF_PACKET.m_rcvdForce[4];
    torques_[2] = sensor_.m_RFT_IF_PACKET.m_rcvdForce[5];
    return hardware_interface::return_type::OK;
  }
  return hardware_interface::return_type::ERROR;
}

}  // namespace rft_sensor_serial

#include "pluginlib/class_list_macros.hpp"
PLUGINLIB_EXPORT_CLASS(
  rft_sensor_serial::RFTSensorHardware,
  hardware_interface::SensorInterface)