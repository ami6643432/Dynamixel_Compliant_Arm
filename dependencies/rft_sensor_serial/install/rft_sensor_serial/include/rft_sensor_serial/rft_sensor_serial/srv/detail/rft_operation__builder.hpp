// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rft_sensor_serial:srv/RftOperation.idl
// generated code does not contain a copyright notice

#ifndef RFT_SENSOR_SERIAL__SRV__DETAIL__RFT_OPERATION__BUILDER_HPP_
#define RFT_SENSOR_SERIAL__SRV__DETAIL__RFT_OPERATION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rft_sensor_serial/srv/detail/rft_operation__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rft_sensor_serial
{

namespace srv
{

namespace builder
{

class Init_RftOperation_Request_param3
{
public:
  explicit Init_RftOperation_Request_param3(::rft_sensor_serial::srv::RftOperation_Request & msg)
  : msg_(msg)
  {}
  ::rft_sensor_serial::srv::RftOperation_Request param3(::rft_sensor_serial::srv::RftOperation_Request::_param3_type arg)
  {
    msg_.param3 = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rft_sensor_serial::srv::RftOperation_Request msg_;
};

class Init_RftOperation_Request_param2
{
public:
  explicit Init_RftOperation_Request_param2(::rft_sensor_serial::srv::RftOperation_Request & msg)
  : msg_(msg)
  {}
  Init_RftOperation_Request_param3 param2(::rft_sensor_serial::srv::RftOperation_Request::_param2_type arg)
  {
    msg_.param2 = std::move(arg);
    return Init_RftOperation_Request_param3(msg_);
  }

private:
  ::rft_sensor_serial::srv::RftOperation_Request msg_;
};

class Init_RftOperation_Request_param1
{
public:
  explicit Init_RftOperation_Request_param1(::rft_sensor_serial::srv::RftOperation_Request & msg)
  : msg_(msg)
  {}
  Init_RftOperation_Request_param2 param1(::rft_sensor_serial::srv::RftOperation_Request::_param1_type arg)
  {
    msg_.param1 = std::move(arg);
    return Init_RftOperation_Request_param2(msg_);
  }

private:
  ::rft_sensor_serial::srv::RftOperation_Request msg_;
};

class Init_RftOperation_Request_op_type
{
public:
  Init_RftOperation_Request_op_type()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RftOperation_Request_param1 op_type(::rft_sensor_serial::srv::RftOperation_Request::_op_type_type arg)
  {
    msg_.op_type = std::move(arg);
    return Init_RftOperation_Request_param1(msg_);
  }

private:
  ::rft_sensor_serial::srv::RftOperation_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::rft_sensor_serial::srv::RftOperation_Request>()
{
  return rft_sensor_serial::srv::builder::Init_RftOperation_Request_op_type();
}

}  // namespace rft_sensor_serial


namespace rft_sensor_serial
{

namespace srv
{

namespace builder
{

class Init_RftOperation_Response_result
{
public:
  Init_RftOperation_Response_result()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::rft_sensor_serial::srv::RftOperation_Response result(::rft_sensor_serial::srv::RftOperation_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rft_sensor_serial::srv::RftOperation_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::rft_sensor_serial::srv::RftOperation_Response>()
{
  return rft_sensor_serial::srv::builder::Init_RftOperation_Response_result();
}

}  // namespace rft_sensor_serial

#endif  // RFT_SENSOR_SERIAL__SRV__DETAIL__RFT_OPERATION__BUILDER_HPP_
