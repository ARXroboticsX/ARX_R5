#pragma once

#include <rclcpp/rclcpp.hpp>
#include <chrono>
#include <memory>

#include "arx_r5_src/interfaces/InterfacesThread.hpp"
#include "arx_r5_src/interfaces/InterfaceTools.hpp"

#include "arx5_arm_msg/msg/robot_cmd.hpp"
#include "arx5_arm_msg/msg/robot_status.hpp"
#include "arm_control/msg/pos_cmd.hpp"

#include "tf2_msgs/msg/tf_message.hpp"
#include "sensor_msgs/msg/joint_state.hpp"

namespace arx::r5
{
    class R5Visualization : public rclcpp::Node
    {
    public:
        R5Visualization();

    private:
        void subArmCallback(const arx5_arm_msg::msg::RobotStatus::SharedPtr msg);
        void PubState();

        rclcpp::Subscription<arx5_arm_msg::msg::RobotStatus>::SharedPtr joint_state_subscriber_;
        
        rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr joint_state_publisher_;

        rclcpp::Publisher<tf2_msgs::msg::TFMessage>::SharedPtr joint_tf_publisher_;

        rclcpp::TimerBase::SharedPtr timer_;

        std::vector<double> joint_positions_ = {0, 0, 0, 0, 0, 0, 0};
        std::vector<double> end_positions_ = {0, 0, 0, 0, 0, 0};

        std::unique_ptr<InterfacesTools> tools_;
    };
}