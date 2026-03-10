cmake_minimum_required(VERSION 3.8)
project(drasim_interfaces)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(builtin_interfaces REQUIRED)
find_package(std_msgs REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/DigitalIO.msg"
  "msg/MotionState.msg"
  "msg/ModbusRegister.msg"
  "srv/SetDO.srv"
  "srv/GetDI.srv"
  "srv/ReadModbus.srv"
  "srv/WriteModbus.srv"
  "srv/MovJ.srv"
  "srv/MovL.srv"
  "srv/MovP.srv"
  DEPENDENCIES builtin_interfaces std_msgs
)

ament_package()
