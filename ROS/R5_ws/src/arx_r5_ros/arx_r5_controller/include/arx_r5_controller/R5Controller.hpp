#pragma once

#include <ros/ros.h>
#include "arx_r5_src/interfaces/InterfacesThread.hpp"
#include "arx5_arm_msg/RobotCmd.h"
#include "arx5_arm_msg/RobotStatus.h"
#include "arm_control/PosCmd.h"
#include <chrono>
#include <memory>

namespace arx::r5
{
    class R5Controller
    {
    public:
        R5Controller(ros::NodeHandle nh);

        void CmdCallback(const arx5_arm_msg::RobotCmd::ConstPtr& msg);
        void PubState(const ros::TimerEvent&);

        void VrCmdCallback(const arm_control::PosCmd::ConstPtr& msg);
        void VrPubState(const ros::TimerEvent&);

        void FollowCmdCallback(const arx5_arm_msg::RobotStatus::ConstPtr& msg);

    private:
        std::shared_ptr<InterfacesThread> interfaces_ptr_;

        ros::Publisher joint_state_publisher_;
        ros::Subscriber joint_state_subscriber_;

        ros::Timer timer_;
    };
}
