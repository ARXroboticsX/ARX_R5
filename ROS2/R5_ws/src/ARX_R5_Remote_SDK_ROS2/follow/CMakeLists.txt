cmake_minimum_required(VERSION 3.8)
project(follow)
# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()
# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(arx_msgs REQUIRED)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)
add_executable(arm_follow_node src/arx.cpp)
target_include_directories(arm_follow_node PUBLIC
        lib/arx_hardware_interface/include lib/arx_r5_src/include)
target_link_libraries(arm_follow_node ${CMAKE_CURRENT_SOURCE_DIR}/lib/arx_r5_src/libarx_r5_src.so ${CMAKE_CURRENT_SOURCE_DIR}/lib/arx_hardware_interface/libarx_hardware_interface.so)
ament_target_dependencies(arm_follow_node rclcpp std_msgs arx_msgs)
install(TARGETS
        arm_follow_node
        DESTINATION lib/${PROJECT_NAME})

install(FILES lib/arx_r5_src/libarx_r5_src.so lib/arx_hardware_interface/libarx_hardware_interface.so
        DESTINATION lib/
)
install(DIRECTORY
        launch
        DESTINATION share/${PROJECT_NAME}
)

ament_package()
