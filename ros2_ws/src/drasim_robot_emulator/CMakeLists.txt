cmake_minimum_required(VERSION 3.8)
project(drasim_robot_emulator)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(drasim_interfaces REQUIRED)

add_executable(robot_emulator_node
  src/robot_emulator_node_main.cpp
  src/robot_emulator_node.cpp
  src/motion_engine.cpp
)

target_include_directories(robot_emulator_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

ament_target_dependencies(robot_emulator_node
  rclcpp
  drasim_interfaces
)

install(TARGETS robot_emulator_node
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
