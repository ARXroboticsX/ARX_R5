cmake_minimum_required(VERSION 3.8)
project(arx_r5_controller)

find_package(catkin REQUIRED COMPONENTS
        arm_control
        arx_r5_msg
        roscpp
        std_msgs
        message_generation
)

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS arm_control arx_r5_msg roscpp std_msgs
)

include_directories(
        include
        ${catkin_INCLUDE_DIRS}
)

# 添加共享库路径
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

# 添加可执行文件
add_executable(R5Controller src/R5Controller.cpp)
target_include_directories(R5Controller PUBLIC lib/arx_hardware_interface/include lib/arx_r5_src/include)
target_link_libraries(R5Controller ${catkin_LIBRARIES} ${CMAKE_CURRENT_SOURCE_DIR}/lib/arx_r5_src/libarx_r5_src.so ${CMAKE_CURRENT_SOURCE_DIR}/lib/arx_hardware_interface/libarx_hardware_interface.so)
add_dependencies(R5Controller  ${catkin_EXPORTED_TARGETS})

add_executable(R5ControllerVr src/R5ControllerVr.cpp)
target_include_directories(R5ControllerVr PUBLIC lib/arx_hardware_interface/include lib/arx_r5_src/include)
target_link_libraries(R5ControllerVr ${catkin_LIBRARIES} ${CMAKE_CURRENT_SOURCE_DIR}/lib/arx_r5_src/libarx_r5_src.so ${CMAKE_CURRENT_SOURCE_DIR}/lib/arx_hardware_interface/libarx_hardware_interface.so)
add_dependencies(R5ControllerVr  ${catkin_EXPORTED_TARGETS})

add_executable(KeyBoard src/KeyBoard.cpp)
target_include_directories(KeyBoard PUBLIC lib/arx_hardware_interface/include lib/arx_r5_src/include)
target_link_libraries(KeyBoard ${catkin_LIBRARIES} ${CMAKE_CURRENT_SOURCE_DIR}/lib/arx_r5_src/libarx_r5_src.so ${CMAKE_CURRENT_SOURCE_DIR}/lib/arx_hardware_interface/libarx_hardware_interface.so)
add_dependencies(KeyBoard  ${catkin_EXPORTED_TARGETS})

install(TARGETS
        R5Controller
        R5ControllerVr
        DESTINATION lib/${PROJECT_NAME})

install(FILES lib/arx_r5_src/libarx_r5_src.so lib/arx_hardware_interface/libarx_hardware_interface.so
        DESTINATION lib/
)
