cmake_minimum_required(VERSION 3.8)
project(master)

add_compile_options(-std=c++17)

# find dependencies
find_package(catkin REQUIRED COMPONENTS
        roscpp
        arx_msgs
)

include_directories(
        ${catkin_INCLUDE_DIRS}
        lib/arx_hardware_interface/include
        lib/arx_r5_src/include
)
catkin_package()
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/arx_r5_src)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/arx_hardware_interface)
add_executable(arm_master_node src/arx.cpp)
target_link_libraries(arm_master_node
        ${catkin_LIBRARIES}
        libarx_r5_src.so
        libarx_hardware_interface.so
)
