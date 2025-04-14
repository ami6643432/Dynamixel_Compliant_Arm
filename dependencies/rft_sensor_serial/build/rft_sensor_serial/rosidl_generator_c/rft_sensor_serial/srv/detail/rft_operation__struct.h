// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rft_sensor_serial:srv/RftOperation.idl
// generated code does not contain a copyright notice

#ifndef RFT_SENSOR_SERIAL__SRV__DETAIL__RFT_OPERATION__STRUCT_H_
#define RFT_SENSOR_SERIAL__SRV__DETAIL__RFT_OPERATION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/RftOperation in the package rft_sensor_serial.
typedef struct rft_sensor_serial__srv__RftOperation_Request
{
  uint8_t op_type;
  uint8_t param1;
  uint8_t param2;
  uint8_t param3;
} rft_sensor_serial__srv__RftOperation_Request;

// Struct for a sequence of rft_sensor_serial__srv__RftOperation_Request.
typedef struct rft_sensor_serial__srv__RftOperation_Request__Sequence
{
  rft_sensor_serial__srv__RftOperation_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rft_sensor_serial__srv__RftOperation_Request__Sequence;


// Constants defined in the message

/// Struct defined in srv/RftOperation in the package rft_sensor_serial.
typedef struct rft_sensor_serial__srv__RftOperation_Response
{
  uint8_t result;
} rft_sensor_serial__srv__RftOperation_Response;

// Struct for a sequence of rft_sensor_serial__srv__RftOperation_Response.
typedef struct rft_sensor_serial__srv__RftOperation_Response__Sequence
{
  rft_sensor_serial__srv__RftOperation_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rft_sensor_serial__srv__RftOperation_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RFT_SENSOR_SERIAL__SRV__DETAIL__RFT_OPERATION__STRUCT_H_
