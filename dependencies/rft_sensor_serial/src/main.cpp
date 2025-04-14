#include <memory>
#include <mutex>
#include <thread> // <-- Added thread header for std::this_thread::sleep_for
#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/wrench_stamped.hpp>
#include "rft_sensor_serial/srv/rft_operation.hpp"
#include "rft_sensor_serial/RFT_COM.h"
#include "rft_sensor_serial/RFT_IF_PACKET_Rev1.2.h"

#define ROS_RFT_SERIAL_SW_VER "VER 0.0.1(Read Only)"

#define RFT_SERVICE_OK (0)
#define RFT_SERVICE_RQST_TIMEOUT (0xF0)

class RftSensorNode : public rclcpp::Node
{
public:
  RftSensorNode() : Node("rft_sensor_serial")
  {
    init_param();

    // Automatically optimize hardware settings (USB latency and CPU affinity)
    autoOptimizeHardware();

    // Initialize COM port
    if (!rft_sensor_.openPort((char*)com_port_.c_str(), baud_rate_))
    {
      RCLCPP_ERROR(this->get_logger(), "COM Port Open Error");
      return;
    }

    // Initialize force/torque divider
    rft_sensor_.m_RFT_IF_PACKET.setDivider(force_divider_, torque_divider_);

    // Create service
    service_ = create_service<rft_sensor_serial::srv::RftOperation>(
      "rft_serial_op_service",
      std::bind(&RftSensorNode::rft_operation_service, this, 
                std::placeholders::_1, std::placeholders::_2));

    // Create publisher
    rft_publisher_ = create_publisher<geometry_msgs::msg::WrenchStamped>(
      "RFT_FORCE", 1);

    // Create timer for data publishing
    timer_ = create_wall_timer(
      std::chrono::milliseconds(5),
      std::bind(&RftSensorNode::timer_callback, this));

    // Automatically start communication (e.g. continuous force/torque output)
    autoStartCommunication();

    RCLCPP_INFO(this->get_logger(), "RFT Force/Torque Sensor <Serial> is ready!!!!");
  }

private:
  // Declare member variables first
  std::string com_port_ = "/dev/ttyUSB0";
  int baud_rate_ = 115200;
  float force_divider_ = 50.0f;
  float torque_divider_ = 1000.0f;
  std::mutex com_port_mutex_;
  CRT_RFT_UART rft_sensor_;

  rclcpp::Service<rft_sensor_serial::srv::RftOperation>::SharedPtr service_;
  rclcpp::Publisher<geometry_msgs::msg::WrenchStamped>::SharedPtr rft_publisher_;
  rclcpp::TimerBase::SharedPtr timer_;

  // Then declare member functions
  void init_param()
  {
    // Declare parameters and get values
    this->declare_parameter("RFT_COM_PORT", "/dev/ttyUSB0");
    this->declare_parameter("RFT_COM_BAUD", 115200);
    this->declare_parameter("RFT_FORCE_DEVIDER", 50.0f);
    this->declare_parameter("RFT_TORQUE_DEVIDER", 1000.0f);

    com_port_ = this->get_parameter("RFT_COM_PORT").as_string();
    baud_rate_ = this->get_parameter("RFT_COM_BAUD").as_int();
    force_divider_ = this->get_parameter("RFT_FORCE_DEVIDER").as_double();
    torque_divider_ = this->get_parameter("RFT_TORQUE_DEVIDER").as_double();

    // Log parameter values
    RCLCPP_INFO(this->get_logger(), "RFT Serial port: %s", com_port_.c_str());
    RCLCPP_INFO(this->get_logger(), "RFT Serial baud-rate: %d", baud_rate_);
    RCLCPP_INFO(this->get_logger(), "Force Divider: %f", force_divider_);
    RCLCPP_INFO(this->get_logger(), "Torque Divider: %f", torque_divider_);
  }

  // New function to automatically set USB latency and CPU affinity.
  void autoOptimizeHardware()
  {
    // Set USB latency timer
    int ret = system("sudo sh -c 'echo 1 > /sys/bus/usb-serial/devices/ttyUSB0/latency_timer'");
    if(ret == 0)
      RCLCPP_INFO(this->get_logger(), "USB latency timer set successfully.");
    else
      RCLCPP_WARN(this->get_logger(), "Failed to set USB latency timer. Check USB connection and permissions.");

    // Set CPU affinity for USB IRQ
    // This command extracts the first USB IRQ and sets its affinity to CPU core 0.
    // ret = system("irq=$(cat /proc/interrupts | grep -i usb | head -n 1 | awk '{print $1}' | sed 's/://') && sudo sh -c 'echo 1 > /proc/irq/$irq/smp_affinity_list'");
    // if(ret == 0)
    //   RCLCPP_INFO(this->get_logger(), "CPU affinity for USB IRQ set successfully.");
    // else
    //   RCLCPP_WARN(this->get_logger(), "Failed to set CPU affinity for USB IRQ. Verify USB IRQ exists and you have sufficient privileges.");
  }

  // Updated autoStartCommunication(): Removed output rate command.
  void autoStartCommunication() 
  {
    auto req = std::make_shared<rft_sensor_serial::srv::RftOperation::Request>();
    req->op_type = CMD_FT_CONT; // Command to start continuous force/torque readings
    std::unique_lock<std::mutex> lock(com_port_mutex_);
    uint8_t result = rft_send_command(req);
    lock.unlock();
    if(result == RFT_SERVICE_OK)
    {
      result = rft_response_wait(req->op_type);
      RCLCPP_INFO(this->get_logger(), "Automatic communication start command sent.");
    }
    else
    {
      RCLCPP_WARN(this->get_logger(), "Failed to automatically start communication.");
    }
  }

  void timer_callback()
  {
    std::unique_lock<std::mutex> lock(com_port_mutex_);
    bool isSensorOk = rft_sensor_.readWorker();
    lock.unlock();

    if ((rft_sensor_.m_nCurrMode == CMD_FT_CONT) && isSensorOk)
    {
      auto ft_data = std::make_unique<geometry_msgs::msg::WrenchStamped>();
      ft_data->header.stamp = this->now();
      ft_data->header.frame_id = "rft_sensor";

      ft_data->wrench.force.x = rft_sensor_.m_RFT_IF_PACKET.m_rcvdForce[0];
      ft_data->wrench.force.y = rft_sensor_.m_RFT_IF_PACKET.m_rcvdForce[1];
      ft_data->wrench.force.z = rft_sensor_.m_RFT_IF_PACKET.m_rcvdForce[2];
      ft_data->wrench.torque.x = rft_sensor_.m_RFT_IF_PACKET.m_rcvdForce[3];
      ft_data->wrench.torque.y = rft_sensor_.m_RFT_IF_PACKET.m_rcvdForce[4];
      ft_data->wrench.torque.z = rft_sensor_.m_RFT_IF_PACKET.m_rcvdForce[5];

      rft_publisher_->publish(std::move(ft_data));
    }
  }

  uint8_t rft_send_command(const std::shared_ptr<rft_sensor_serial::srv::RftOperation::Request> request)
  {
    uint8_t result = RFT_SERVICE_OK;
    switch(request->op_type)
    {
      case CMD_GET_PRODUCT_NAME:
        RCLCPP_INFO(get_logger(), "RCVD SERVICE REQUEST: get product name");
        rft_sensor_.rqst_ProductName();
        break;

      case CMD_GET_SERIAL_NUMBER:
        RCLCPP_INFO(get_logger(), "RCVD SERVICE REQUEST: get serial number");
        rft_sensor_.rqst_SerialNumber();
        break;

      case CMD_GET_FIRMWARE_VER:
        RCLCPP_INFO(get_logger(), "RCVD SERVICE REQUEST: get firmware version");
        rft_sensor_.rqst_Firmwareverion();
        break;

      case CMD_SET_COMM_BAUDRATE:
        RCLCPP_INFO(get_logger(), "RCVD SERVICE REQUEST: set baud-rate");
        rft_sensor_.set_Comm_Speed(request->param1);
        break;

      case CMD_GET_COMM_BAUDRATE:
        RCLCPP_INFO(get_logger(), "RCVD SERVICE REQUEST: get baud-rate");
        rft_sensor_.rqst_CommSpeed();
        break;

      case CMD_SET_FT_FILTER:
        RCLCPP_INFO(get_logger(), "RCVD SERVICE REQUEST: set filter type");
        rft_sensor_.set_FT_Filter_Type(request->param1, request->param2);
        break;

      case CMD_GET_FT_FILTER:
        RCLCPP_INFO(get_logger(), "RCVD SERVICE REQUEST: get filter type");
        rft_sensor_.rqst_FT_Filter_Type();
        break;

      case CMD_FT_ONCE:
        RCLCPP_INFO(get_logger(), "RCVD SERVICE REQUEST: get force/torque once");
        rft_sensor_.rqst_FT();
        break;

      case CMD_FT_CONT:
        RCLCPP_INFO(get_logger(), "RCVD SERVICE REQUEST: get force/torque cont.");
        rft_sensor_.rqst_FT_Continuous();
        break;

      case CMD_FT_CONT_STOP:
        RCLCPP_INFO(get_logger(), "RCVD SERVICE REQUEST: stop force/torque  - There is no response packet");
        rft_sensor_.rqst_FT_Stop();
        break;

      case CMD_SET_CONT_OUT_FRQ:
        RCLCPP_INFO(get_logger(), "RCVD SERVICE REQUEST: set output frq.");
        rft_sensor_.set_FT_Cont_Interval(request->param1);
        break;

      case CMD_GET_CONT_OUT_FRQ:
        RCLCPP_INFO(get_logger(), "RCVD SERVICE REQUEST: get output frq.");
        rft_sensor_.rqst_FT_Cont_Interval();
        break;

      case CMD_SET_BIAS:
        RCLCPP_INFO(get_logger(), "RCVD SERVICE REQUEST: set bias - There is no response packet");
        rft_sensor_.set_FT_Bias(request->param1);
        break;

      case CMD_GET_OVERLOAD_COUNT:
        RCLCPP_INFO(get_logger(), "RCVD SERVICE REQUEST: get overload count");
        rft_sensor_.rqst_FT_OverloadCnt();
        break;

      default:
        result = NOT_SUPPORTED_CMD;
        break;
    }
    return result;
  }

  uint8_t rft_response_display(uint8_t opType)
  {
    uint8_t result = RFT_SERVICE_OK;
    switch(opType)
    {
      case CMD_GET_PRODUCT_NAME:
        RCLCPP_INFO(get_logger(), "%s", rft_sensor_.m_RFT_IF_PACKET.m_rcvd_product_name);
        break;
      case CMD_GET_SERIAL_NUMBER:
        RCLCPP_INFO(get_logger(), "%s", rft_sensor_.m_RFT_IF_PACKET.m_rcvd_serial_number);
        break;
      case CMD_GET_FIRMWARE_VER:
        RCLCPP_INFO(get_logger(), "%s", rft_sensor_.m_RFT_IF_PACKET.m_rcvd_firmware_version);
        break;
      case CMD_SET_COMM_BAUDRATE:
        RCLCPP_INFO(get_logger(), "Cmd Type: %d, Result: %d, Err. Code: %d",
                    rft_sensor_.m_RFT_IF_PACKET.m_response_cmd,
                    rft_sensor_.m_RFT_IF_PACKET.m_response_result,
                    rft_sensor_.m_RFT_IF_PACKET.m_response_errcode);
        result = rft_sensor_.m_RFT_IF_PACKET.m_response_errcode;
        break;
      // Add other cases as needed...
      default:
        result = NOT_SUPPORTED_CMD;
        break;
    }
    return result;
  }

  uint8_t rft_response_wait(uint8_t opType)
  {
    int result = RFT_SERVICE_OK;
    int waitTimeOut = 0;
    bool isRcvd = false;

    do {
      if(waitTimeOut >= 50)
      {
        RCLCPP_WARN(get_logger(), "RCVD SERVICE TIMEOUT");
        isRcvd = true;
        result = RFT_SERVICE_RQST_TIMEOUT;
      }

      if(rft_sensor_.m_bIsRcvd_Response_Pkt)
      {
        isRcvd = true;
        rft_response_display(opType);
      }

      waitTimeOut++;
      std::this_thread::sleep_for(std::chrono::microseconds(500));

    } while(!isRcvd);

    return result;
  }

  void rft_operation_service(
    const std::shared_ptr<rft_sensor_serial::srv::RftOperation::Request> request,
    std::shared_ptr<rft_sensor_serial::srv::RftOperation::Response> response)
  {
    uint8_t commandSend = RFT_SERVICE_OK;

    std::unique_lock<std::mutex> lock(com_port_mutex_);
    commandSend = rft_send_command(request);
    lock.unlock();

    if (commandSend == RFT_SERVICE_OK)
    {
      if ((request->op_type != CMD_SET_BIAS) && (request->op_type != CMD_FT_CONT_STOP))
      {
        response->result = rft_response_wait(request->op_type);
      }
    }
    else
    {
      response->result = commandSend;
    }
  }
};

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<RftSensorNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}