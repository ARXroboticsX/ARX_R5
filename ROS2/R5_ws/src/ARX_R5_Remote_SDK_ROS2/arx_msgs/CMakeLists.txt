cmake_minimum_required(VERSION 3.8)
project(arx_msgs)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)

# 声明消息文件
rosidl_generate_interfaces(${PROJECT_NAME}
        "msg/ChassisCtrl.msg"
        "msg/JointControl.msg"
        "msg/JointInformation.msg"
        "msg/PosCmd.msg"
        DEPENDENCIES
        std_msgs
)

# 添加对接口的依赖
ament_export_dependencies(rosidl_default_runtime)

ament_package()
