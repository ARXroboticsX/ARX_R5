cmake_minimum_required(VERSION 3.8)
project(arx_r5_controller)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(arm_control REQUIRED)
find_package(arx5_arm_msg REQUIRED)

find_package(tf2_msgs REQUIRED)
find_package(tf2 REQUIRED)

include_directories(include)

find_library(ARX_SRC_LIB
    NAMES arx_r5_src
    PATHS ${CMAKE_CURRENT_SOURCE_DIR}/lib/arx_r5_src
    NO_DEFAULT_PATH  # 禁止在其他路径中搜索
)

# 确保库文件被找到
if (NOT ARX_SRC_LIB)
    message(FATAL_ERROR "library not found!")
endif()

# 添加可执行文件
add_executable(R5Controller src/R5Controller.cpp)
target_include_directories(R5Controller PUBLIC lib/arx_hardware_interface/include lib/arx_r5_src/include)
target_link_libraries(R5Controller ${ARX_SRC_LIB})
ament_target_dependencies(R5Controller rclcpp std_msgs arx5_arm_msg arm_control tf2 tf2_msgs)

# 添加可执行文件
add_executable(R5Visualization src/R5Visualization.cpp)
target_include_directories(R5Visualization PUBLIC lib/arx_hardware_interface/include lib/arx_r5_src/include)
target_link_libraries(R5Visualization ${ARX_SRC_LIB})
ament_target_dependencies(R5Visualization rclcpp std_msgs arx5_arm_msg arm_control tf2 tf2_msgs)

add_executable(KeyBoard src/KeyBoard.cpp)
ament_target_dependencies(KeyBoard rclcpp std_msgs arx5_arm_msg)

install(TARGETS
    R5Controller
    R5Visualization
    KeyBoard
  DESTINATION lib/${PROJECT_NAME})

install(FILES ${ARX_SRC_LIB}
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