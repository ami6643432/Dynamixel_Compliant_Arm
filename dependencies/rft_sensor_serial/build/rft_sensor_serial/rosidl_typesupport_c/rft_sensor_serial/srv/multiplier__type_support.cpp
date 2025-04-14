// generated from rosidl_typesupport_c/resource/idl__type_support.cpp.em
// with input from rft_sensor_serial:srv/Multiplier.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rft_sensor_serial/srv/detail/multiplier__struct.h"
#include "rft_sensor_serial/srv/detail/multiplier__type_support.h"
#include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/message_type_support_dispatch.h"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_c/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace rft_sensor_serial
{

namespace srv
{

namespace rosidl_typesupport_c
{

typedef struct _Multiplier_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _Multiplier_Request_type_support_ids_t;

static const _Multiplier_Request_type_support_ids_t _Multiplier_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _Multiplier_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _Multiplier_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _Multiplier_Request_type_support_symbol_names_t _Multiplier_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, rft_sensor_serial, srv, Multiplier_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rft_sensor_serial, srv, Multiplier_Request)),
  }
};

typedef struct _Multiplier_Request_type_support_data_t
{
  void * data[2];
} _Multiplier_Request_type_support_data_t;

static _Multiplier_Request_type_support_data_t _Multiplier_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _Multiplier_Request_message_typesupport_map = {
  2,
  "rft_sensor_serial",
  &_Multiplier_Request_message_typesupport_ids.typesupport_identifier[0],
  &_Multiplier_Request_message_typesupport_symbol_names.symbol_name[0],
  &_Multiplier_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t Multiplier_Request_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_Multiplier_Request_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace rft_sensor_serial

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, rft_sensor_serial, srv, Multiplier_Request)() {
  return &::rft_sensor_serial::srv::rosidl_typesupport_c::Multiplier_Request_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rft_sensor_serial/srv/detail/multiplier__struct.h"
// already included above
// #include "rft_sensor_serial/srv/detail/multiplier__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace rft_sensor_serial
{

namespace srv
{

namespace rosidl_typesupport_c
{

typedef struct _Multiplier_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _Multiplier_Response_type_support_ids_t;

static const _Multiplier_Response_type_support_ids_t _Multiplier_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _Multiplier_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _Multiplier_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _Multiplier_Response_type_support_symbol_names_t _Multiplier_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, rft_sensor_serial, srv, Multiplier_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rft_sensor_serial, srv, Multiplier_Response)),
  }
};

typedef struct _Multiplier_Response_type_support_data_t
{
  void * data[2];
} _Multiplier_Response_type_support_data_t;

static _Multiplier_Response_type_support_data_t _Multiplier_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _Multiplier_Response_message_typesupport_map = {
  2,
  "rft_sensor_serial",
  &_Multiplier_Response_message_typesupport_ids.typesupport_identifier[0],
  &_Multiplier_Response_message_typesupport_symbol_names.symbol_name[0],
  &_Multiplier_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t Multiplier_Response_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_Multiplier_Response_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace rft_sensor_serial

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, rft_sensor_serial, srv, Multiplier_Response)() {
  return &::rft_sensor_serial::srv::rosidl_typesupport_c::Multiplier_Response_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "rft_sensor_serial/srv/detail/multiplier__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/service_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace rft_sensor_serial
{

namespace srv
{

namespace rosidl_typesupport_c
{

typedef struct _Multiplier_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _Multiplier_type_support_ids_t;

static const _Multiplier_type_support_ids_t _Multiplier_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _Multiplier_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _Multiplier_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _Multiplier_type_support_symbol_names_t _Multiplier_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, rft_sensor_serial, srv, Multiplier)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rft_sensor_serial, srv, Multiplier)),
  }
};

typedef struct _Multiplier_type_support_data_t
{
  void * data[2];
} _Multiplier_type_support_data_t;

static _Multiplier_type_support_data_t _Multiplier_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _Multiplier_service_typesupport_map = {
  2,
  "rft_sensor_serial",
  &_Multiplier_service_typesupport_ids.typesupport_identifier[0],
  &_Multiplier_service_typesupport_symbol_names.symbol_name[0],
  &_Multiplier_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t Multiplier_service_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_Multiplier_service_typesupport_map),
  rosidl_typesupport_c__get_service_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace rft_sensor_serial

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_c, rft_sensor_serial, srv, Multiplier)() {
  return &::rft_sensor_serial::srv::rosidl_typesupport_c::Multiplier_service_type_support_handle;
}

#ifdef __cplusplus
}
#endif
