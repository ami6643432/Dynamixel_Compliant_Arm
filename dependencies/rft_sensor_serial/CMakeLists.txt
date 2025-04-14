cmake_minimum_required(VERSION 3.8)
project(rft_sensor_serial)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(hardware_interface REQUIRED)
find_package(pluginlib REQUIRED)
find_package(rclcpp_lifecycle REQUIRED)

# Generate services
rosidl_generate_interfaces(${PROJECT_NAME}
  "srv/RftOperation.srv"
  "srv/Multiplier.srv"
  DEPENDENCIES std_msgs
)

# Create the RFT sensor node executable
add_executable(${PROJECT_NAME}_node
  src/main.cpp
  src/RFT_COM.cpp
  src/RFT_IF_PACKET_Rev1.2.cpp
)

# Get the typesupport target for the node
rosidl_get_typesupport_target(cpp_typesupport_target 
  ${PROJECT_NAME} "rosidl_typesupport_cpp")

# Link the node
target_include_directories(${PROJECT_NAME}_node PUBLIC
  include
)

target_link_libraries(${PROJECT_NAME}_node 
  "${cpp_typesupport_target}"
)

ament_target_dependencies(${PROJECT_NAME}_node
  rclcpp
  std_msgs
  geometry_msgs
)

# Create the hardware interface library
add_library(
  ${PROJECT_NAME}_hardware
  SHARED
  src/hardware/rft_sensor_hardware.cpp
  src/RFT_COM.cpp
  src/RFT_IF_PACKET_Rev1.2.cpp
)

target_include_directories(${PROJECT_NAME}_hardware PUBLIC
  include
)

ament_target_dependencies(${PROJECT_NAME}_hardware
  hardware_interface
  rclcpp
  pluginlib
  rclcpp_lifecycle
)

# Install
install(
  TARGETS 
    ${PROJECT_NAME}_node
    ${PROJECT_NAME}_hardware
  RUNTIME DESTINATION lib/${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
)

install(
  DIRECTORY include/
  DESTINATION include/
)

# Export plugin description file
pluginlib_export_plugin_description_file(
  hardware_interface
  rft_sensor_hardware.xml
)

ament_package()