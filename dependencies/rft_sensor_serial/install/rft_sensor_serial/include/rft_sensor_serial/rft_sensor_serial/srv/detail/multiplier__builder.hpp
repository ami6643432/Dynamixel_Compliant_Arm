// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rft_sensor_serial:srv/Multiplier.idl
// generated code does not contain a copyright notice

#ifndef RFT_SENSOR_SERIAL__SRV__DETAIL__MULTIPLIER__BUILDER_HPP_
#define RFT_SENSOR_SERIAL__SRV__DETAIL__MULTIPLIER__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rft_sensor_serial/srv/detail/multiplier__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rft_sensor_serial
{

namespace srv
{

namespace builder
{

class Init_Multiplier_Request_b
{
public:
  explicit Init_Multiplier_Request_b(::rft_sensor_serial::srv::Multiplier_Request & msg)
  : msg_(msg)
  {}
  ::rft_sensor_serial::srv::Multiplier_Request b(::rft_sensor_serial::srv::Multiplier_Request::_b_type arg)
  {
    msg_.b = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rft_sensor_serial::srv::Multiplier_Request msg_;
};

class Init_Multiplier_Request_a
{
public:
  Init_Multiplier_Request_a()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Multiplier_Request_b a(::rft_sensor_serial::srv::Multiplier_Request::_a_type arg)
  {
    msg_.a = std::move(arg);
    return Init_Multiplier_Request_b(msg_);
  }

private:
  ::rft_sensor_serial::srv::Multiplier_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::rft_sensor_serial::srv::Multiplier_Request>()
{
  return rft_sensor_serial::srv::builder::Init_Multiplier_Request_a();
}

}  // namespace rft_sensor_serial


namespace rft_sensor_serial
{

namespace srv
{

namespace builder
{

class Init_Multiplier_Response_result
{
public:
  Init_Multiplier_Response_result()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::rft_sensor_serial::srv::Multiplier_Response result(::rft_sensor_serial::srv::Multiplier_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rft_sensor_serial::srv::Multiplier_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::rft_sensor_serial::srv::Multiplier_Response>()
{
  return rft_sensor_serial::srv::builder::Init_Multiplier_Response_result();
}

}  // namespace rft_sensor_serial

#endif  // RFT_SENSOR_SERIAL__SRV__DETAIL__MULTIPLIER__BUILDER_HPP_
