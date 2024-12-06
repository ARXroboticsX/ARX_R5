cmake_minimum_required(VERSION 3.8)
project(arx_msgs)

# find dependencies
find_package(catkin REQUIRED COMPONENTS
        roscpp
        message_generation
        std_msgs
)

add_message_files(
        FILES
        ChassisCtrl.msg
        JointControl.msg
        JointInformation.msg
        PosCmd.msg
)

generate_messages(
        DEPENDENCIES
        std_msgs
)

catkin_package(
        CATKIN_DEPENDS message_runtime
)