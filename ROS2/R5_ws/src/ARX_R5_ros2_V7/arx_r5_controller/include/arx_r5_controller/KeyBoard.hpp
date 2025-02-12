#pragma once

#include "arx5_arm_msg/msg/robot_cmd.hpp"
#include "arx5_arm_msg/msg/robot_status.hpp"

#include <rclcpp/rclcpp.hpp>
#include <chrono>
#include <memory>

namespace arx::r5 
{
    class KeyBoardNode : public rclcpp::Node
    {
    public:
        KeyBoardNode();

        void getEndPoseCallBack(const arx5_arm_msg::msg::RobotStatus::SharedPtr msg);

        int ScanKeyBoard();
        void Update();

    private:
        std::vector<double> status_end_positions_ = {0, 0, 0, 0, 0, 0};

        rclcpp::Publisher<arx5_arm_msg::msg::RobotCmd>::SharedPtr joint_cmd_publisher_;
        rclcpp::Subscription<arx5_arm_msg::msg::RobotStatus>::SharedPtr joint_status_subscriber_;

        rclcpp::TimerBase::SharedPtr timer_;

        arx5_arm_msg::msg::RobotCmd message_;

        int key_[3] = {0};

        bool g_comp_flag_ = false;
    };
}