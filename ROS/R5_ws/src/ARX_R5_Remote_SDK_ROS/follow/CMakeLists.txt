cmake_minimum_required(VERSION 3.8)
project(follow)

add_compile_options(-std=c++17)

# find dependencies
find_package(catkin REQUIRED COMPONENTS
        roscpp
        arx_msgs
)

catkin_package()
include_directories(
        ${catkin_INCLUDE_DIRS}
        lib/arx_hardware_interface/include
        lib/arx_r5_src/include
)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/arx_r5_src)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/arx_hardware_interface)
add_executable(arm_follow_node src/arx.cpp)
target_link_libraries(arm_follow_node
        ${catkin_LIBRARIES}
        libarx_r5_src.so
        libarx_hardware_interface.so
)
