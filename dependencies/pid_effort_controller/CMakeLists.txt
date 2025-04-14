cmake_minimum_required(VERSION 3.8)
project(pid_effort_controller)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(effort_controllers REQUIRED)
find_package(controller_interface REQUIRED)
find_package(rclcpp REQUIRED)
find_package(pluginlib REQUIRED)
find_package(hardware_interface REQUIRED)
find_package(realtime_tools REQUIRED)

# Create controller library
add_library(${PROJECT_NAME} SHARED
  src/pid_effort_controller.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
  include
)

ament_target_dependencies(${PROJECT_NAME}
  effort_controllers
  controller_interface
  rclcpp
  pluginlib
  hardware_interface
  realtime_tools
)

# Export controller plugin
pluginlib_export_plugin_description_file(controller_interface pid_effort_controller.xml)

# Install
install(
  DIRECTORY include/
  DESTINATION include
)

install(
  TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_export_dependencies(
  effort_controllers
  controller_interface
  rclcpp
  pluginlib
  hardware_interface
  realtime_tools
)
ament_export_include_directories(
  include
)
ament_export_libraries(
  ${PROJECT_NAME}
)

ament_package()