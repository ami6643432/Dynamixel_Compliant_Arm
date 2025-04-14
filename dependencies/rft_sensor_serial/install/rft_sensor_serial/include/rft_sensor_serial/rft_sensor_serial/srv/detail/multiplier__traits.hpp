// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from rft_sensor_serial:srv/Multiplier.idl
// generated code does not contain a copyright notice

#ifndef RFT_SENSOR_SERIAL__SRV__DETAIL__MULTIPLIER__TRAITS_HPP_
#define RFT_SENSOR_SERIAL__SRV__DETAIL__MULTIPLIER__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "rft_sensor_serial/srv/detail/multiplier__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace rft_sensor_serial
{

namespace srv
{

inline void to_flow_style_yaml(
  const Multiplier_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: a
  {
    out << "a: ";
    rosidl_generator_traits::value_to_yaml(msg.a, out);
    out << ", ";
  }

  // member: b
  {
    out << "b: ";
    rosidl_generator_traits::value_to_yaml(msg.b, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Multiplier_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: a
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "a: ";
    rosidl_generator_traits::value_to_yaml(msg.a, out);
    out << "\n";
  }

  // member: b
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "b: ";
    rosidl_generator_traits::value_to_yaml(msg.b, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Multiplier_Request & msg, bool use_flow_style = false)
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
  const rft_sensor_serial::srv::Multiplier_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  rft_sensor_serial::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use rft_sensor_serial::srv::to_yaml() instead")]]
inline std::string to_yaml(const rft_sensor_serial::srv::Multiplier_Request & msg)
{
  return rft_sensor_serial::srv::to_yaml(msg);
}

template<>
inline const char * data_type<rft_sensor_serial::srv::Multiplier_Request>()
{
  return "rft_sensor_serial::srv::Multiplier_Request";
}

template<>
inline const char * name<rft_sensor_serial::srv::Multiplier_Request>()
{
  return "rft_sensor_serial/srv/Multiplier_Request";
}

template<>
struct has_fixed_size<rft_sensor_serial::srv::Multiplier_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<rft_sensor_serial::srv::Multiplier_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<rft_sensor_serial::srv::Multiplier_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rft_sensor_serial
{

namespace srv
{

inline void to_flow_style_yaml(
  const Multiplier_Response & msg,
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
  const Multiplier_Response & msg,
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

inline std::string to_yaml(const Multiplier_Response & msg, bool use_flow_style = false)
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
  const rft_sensor_serial::srv::Multiplier_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  rft_sensor_serial::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use rft_sensor_serial::srv::to_yaml() instead")]]
inline std::string to_yaml(const rft_sensor_serial::srv::Multiplier_Response & msg)
{
  return rft_sensor_serial::srv::to_yaml(msg);
}

template<>
inline const char * data_type<rft_sensor_serial::srv::Multiplier_Response>()
{
  return "rft_sensor_serial::srv::Multiplier_Response";
}

template<>
inline const char * name<rft_sensor_serial::srv::Multiplier_Response>()
{
  return "rft_sensor_serial/srv/Multiplier_Response";
}

template<>
struct has_fixed_size<rft_sensor_serial::srv::Multiplier_Response>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<rft_sensor_serial::srv::Multiplier_Response>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<rft_sensor_serial::srv::Multiplier_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<rft_sensor_serial::srv::Multiplier>()
{
  return "rft_sensor_serial::srv::Multiplier";
}

template<>
inline const char * name<rft_sensor_serial::srv::Multiplier>()
{
  return "rft_sensor_serial/srv/Multiplier";
}

template<>
struct has_fixed_size<rft_sensor_serial::srv::Multiplier>
  : std::integral_constant<
    bool,
    has_fixed_size<rft_sensor_serial::srv::Multiplier_Request>::value &&
    has_fixed_size<rft_sensor_serial::srv::Multiplier_Response>::value
  >
{
};

template<>
struct has_bounded_size<rft_sensor_serial::srv::Multiplier>
  : std::integral_constant<
    bool,
    has_bounded_size<rft_sensor_serial::srv::Multiplier_Request>::value &&
    has_bounded_size<rft_sensor_serial::srv::Multiplier_Response>::value
  >
{
};

template<>
struct is_service<rft_sensor_serial::srv::Multiplier>
  : std::true_type
{
};

template<>
struct is_service_request<rft_sensor_serial::srv::Multiplier_Request>
  : std::true_type
{
};

template<>
struct is_service_response<rft_sensor_serial::srv::Multiplier_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // RFT_SENSOR_SERIAL__SRV__DETAIL__MULTIPLIER__TRAITS_HPP_
