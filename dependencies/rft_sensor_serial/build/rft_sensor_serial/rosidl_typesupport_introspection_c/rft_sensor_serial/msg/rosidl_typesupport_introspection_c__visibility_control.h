// generated from
// rosidl_typesupport_introspection_c/resource/rosidl_typesupport_introspection_c__visibility_control.h.in
// generated code does not contain a copyright notice

#ifndef RFT_SENSOR_SERIAL__MSG__ROSIDL_TYPESUPPORT_INTROSPECTION_C__VISIBILITY_CONTROL_H_
#define RFT_SENSOR_SERIAL__MSG__ROSIDL_TYPESUPPORT_INTROSPECTION_C__VISIBILITY_CONTROL_H_

#ifdef __cplusplus
extern "C"
{
#endif

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_rft_sensor_serial __attribute__ ((dllexport))
    #define ROSIDL_TYPESUPPORT_INTROSPECTION_C_IMPORT_rft_sensor_serial __attribute__ ((dllimport))
  #else
    #define ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_rft_sensor_serial __declspec(dllexport)
    #define ROSIDL_TYPESUPPORT_INTROSPECTION_C_IMPORT_rft_sensor_serial __declspec(dllimport)
  #endif
  #ifdef ROSIDL_TYPESUPPORT_INTROSPECTION_C_BUILDING_DLL_rft_sensor_serial
    #define ROSIDL_TYPESUPPORT_INTROSPECTION_C_PUBLIC_rft_sensor_serial ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_rft_sensor_serial
  #else
    #define ROSIDL_TYPESUPPORT_INTROSPECTION_C_PUBLIC_rft_sensor_serial ROSIDL_TYPESUPPORT_INTROSPECTION_C_IMPORT_rft_sensor_serial
  #endif
#else
  #define ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_rft_sensor_serial __attribute__ ((visibility("default")))
  #define ROSIDL_TYPESUPPORT_INTROSPECTION_C_IMPORT_rft_sensor_serial
  #if __GNUC__ >= 4
    #define ROSIDL_TYPESUPPORT_INTROSPECTION_C_PUBLIC_rft_sensor_serial __attribute__ ((visibility("default")))
  #else
    #define ROSIDL_TYPESUPPORT_INTROSPECTION_C_PUBLIC_rft_sensor_serial
  #endif
#endif

#ifdef __cplusplus
}
#endif

#endif  // RFT_SENSOR_SERIAL__MSG__ROSIDL_TYPESUPPORT_INTROSPECTION_C__VISIBILITY_CONTROL_H_
