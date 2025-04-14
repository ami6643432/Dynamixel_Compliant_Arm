// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from rft_sensor_serial:srv/RftOperation.idl
// generated code does not contain a copyright notice

#ifndef RFT_SENSOR_SERIAL__SRV__DETAIL__RFT_OPERATION__TRAITS_HPP_
#define RFT_SENSOR_SERIAL__SRV__DETAIL__RFT_OPERATION__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "rft_sensor_serial/srv/detail/rft_operation__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace rft_sensor_serial
{

namespace srv
{

inline void to_flow_style_yaml(
  const RftOperation_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: op_type
  {
    out << "op_type: ";
    rosidl_generator_traits::value_to_yaml(msg.op_type, out);
    out << ", ";
  }

  // member: param1
  {
    out << "param1: ";
    rosidl_generator_traits::value_to_yaml(msg.param1, out);
    out << ", ";
  }

  // member: param2
  {
    out << "param2: ";
    rosidl_generator_traits::value_to_yaml(msg.param2, out);
    out << ", ";
  }

  // member: param3
  {
    out << "param3: ";
    rosidl_generator_traits::value_to_yaml(msg.param3, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const RftOperation_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: op_type
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "op_type: ";
    rosidl_generator_traits::value_to_yaml(msg.op_type, out);
    out << "\n";
  }

  // member: param1
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "param1: ";
    rosidl_generator_traits::value_to_yaml(msg.param1, out);
    out << "\n";
  }

  // member: param2
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "param2: ";
    rosidl_generator_traits::value_to_yaml(msg.param2, out);
    out << "\n";
  }

  // member: param3
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "param3: ";
    rosidl_generator_traits::value_to_yaml(msg.param3, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const RftOperation_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace rft_sensor_serial

namespace rosidl_generator_traits
{

[[deprecated("use rft_sensor_serial::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const rft_sensor_serial::srv::RftOperation_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  rft_sensor_serial::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use rft_sensor_serial::srv::to_yaml() instead")]]
inline std::string to_yaml(const rft_sensor_serial::srv::RftOperation_Request & msg)
{
  return rft_sensor_serial::srv::to_yaml(msg);
}

template<>
inline const char * data_type<rft_sensor_serial::srv::RftOperation_Request>()
{
  return "rft_sensor_serial::srv::RftOperation_Request";
}

template<>
inline const char * name<rft_sensor_serial::srv::RftOperation_Request>()
{
  return "rft_sensor_serial/srv/RftOperation_Request";
}

template<>
struct has_fixed_size<rft_sensor_serial::srv::RftOperation_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<rft_sensor_serial::srv::RftOperation_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<rft_sensor_serial::srv::RftOperation_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rft_sensor_serial
{

namespace srv
{

inline void to_flow_style_yaml(
  const RftOperation_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: result
  {
    out << "result: ";
    rosidl_generator_traits::value_to_yaml(msg.result, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const RftOperation_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: result
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "result: ";
    rosidl_generator_traits::value_to_yaml(msg.result, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const RftOperation_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace rft_sensor_serial

namespace rosidl_generator_traits
{

[[deprecated("use rft_sensor_serial::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const rft_sensor_serial::srv::RftOperation_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  rft_sensor_serial::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use rft_sensor_serial::srv::to_yaml() instead")]]
inline std::string to_yaml(const rft_sensor_serial::srv::RftOperation_Response & msg)
{
  return rft_sensor_serial::srv::to_yaml(msg);
}

template<>
inline const char * data_type<rft_sensor_serial::srv::RftOperation_Response>()
{
  return "rft_sensor_serial::srv::RftOperation_Response";
}

template<>
inline const char * name<rft_sensor_serial::srv::RftOperation_Response>()
{
  return "rft_sensor_serial/srv/RftOperation_Response";
}

template<>
struct has_fixed_size<rft_sensor_serial::srv::RftOperation_Response>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<rft_sensor_serial::srv::RftOperation_Response>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<rft_sensor_serial::srv::RftOperation_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<rft_sensor_serial::srv::RftOperation>()
{
  return "rft_sensor_serial::srv::RftOperation";
}

template<>
inline const char * name<rft_sensor_serial::srv::RftOperation>()
{
  return "rft_sensor_serial/srv/RftOperation";
}

template<>
struct has_fixed_size<rft_sensor_serial::srv::RftOperation>
  : std::integral_constant<
    bool,
    has_fixed_size<rft_sensor_serial::srv::RftOperation_Request>::value &&
    has_fixed_size<rft_sensor_serial::srv::RftOperation_Response>::value
  >
{
};

template<>
struct has_bounded_size<rft_sensor_serial::srv::RftOperation>
  : std::integral_constant<
    bool,
    has_bounded_size<rft_sensor_serial::srv::RftOperation_Request>::value &&
    has_bounded_size<rft_sensor_serial::srv::RftOperation_Response>::value
  >
{
};

template<>
struct is_service<rft_sensor_serial::srv::RftOperation>
  : std::true_type
{
};

template<>
struct is_service_request<rft_sensor_serial::srv::RftOperation_Request>
  : std::true_type
{
};

template<>
struct is_service_response<rft_sensor_serial::srv::RftOperation_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // RFT_SENSOR_SERIAL__SRV__DETAIL__RFT_OPERATION__TRAITS_HPP_
