cmake_minimum_required(VERSION 3.8)
project(arx_r5_controller)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(arm_control REQUIRED)
find_package(arx5_arm_msg REQUIRED)

include_directories(include)

# 添加共享库路径
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

# 添加可执行文件
add_executable(R5Controller src/R5Controller.cpp)
target_include_directories(R5Controller PUBLIC lib/arx_hardware_interface/include lib/arx_r5_src/include)
target_link_libraries(R5Controller ${CMAKE_CURRENT_SOURCE_DIR}/lib/arx_r5_src/libarx_r5_src.so ${CMAKE_CURRENT_SOURCE_DIR}/lib/arx_hardware_interface/libarx_hardware_interface.so)
ament_target_dependencies(R5Controller rclcpp std_msgs arx5_arm_msg arm_control)

add_executable(KeyBoard src/KeyBoard.cpp)
ament_target_dependencies(KeyBoard rclcpp std_msgs arx5_arm_msg)

install(TARGETS
    R5Controller
    KeyBoard
  DESTINATION lib/${PROJECT_NAME})

install(FILES lib/arx_r5_src/libarx_r5_src.so lib/arx_hardware_interface/libarx_hardware_interface.so
  DESTINATION lib/
)

install(DIRECTORY launch/
  DESTINATION share/${PROJECT_NAME}/launch
  FILES_MATCHING PATTERN "*.launch.py")

install(DIRECTORY config/
  DESTINATION share/${PROJECT_NAME}/config
  FILES_MATCHING PATTERN "*.yaml")

ament_export_dependencies(rosidl_default_runtime)

ament_package()