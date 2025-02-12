#include "arx_r5_controller/R5Visualization.hpp"

namespace arx::r5
{
    R5Visualization::R5Visualization() : Node("r5_visualization_node")
    {
        tools_ = std::make_unique<InterfacesTools>(0);
        // Create a subscription to the IMU topic
        joint_state_subscriber_ = this->create_subscription<arx5_arm_msg::msg::RobotStatus>(
            "/arm_status", 10, std::bind(&R5Visualization::subArmCallback, this, std::placeholders::_1));

        joint_state_publisher_ = this->create_publisher<sensor_msgs::msg::JointState>("/joint_status", 10);
        joint_tf_publisher_ = this->create_publisher<tf2_msgs::msg::TFMessage>("/tf", 10);

        timer_ = this->create_wall_timer(std::chrono::milliseconds(10), std::bind(&R5Visualization::PubState, this));
    }

    void R5Visualization::subArmCallback(const arx5_arm_msg::msg::RobotStatus::SharedPtr msg)
    {
        for (int i = 0; i < msg->joint_pos.size(); i++)
        {
            joint_positions_[i] = msg->joint_pos[i];
        }

        for (int i = 0; i < msg->end_pos.size(); i++)
        {
            end_positions_[i] = msg->end_pos[i];
        }
    }

    void R5Visualization::PubState()
    {
        sensor_msgs::msg::JointState joint_state_msg;
        joint_state_msg.header.stamp = this->now();
        joint_state_msg.header.frame_id = "arm_base_link";
        joint_state_msg.name = {"joint1", "joint2", "joint3", "joint4", "joint5", "joint6", "joint7"};
        joint_state_msg.position = joint_positions_;
        joint_state_publisher_->publish(joint_state_msg);

        tf2_msgs::msg::TFMessage tf_msg;
        
        //==============================================================================================================
        geometry_msgs::msg::TransformStamped tf_stamped;

        tf_stamped.header.frame_id = "odom";
        tf_stamped.child_frame_id = "end";

        tf_stamped.transform.translation.x = end_positions_[0];
        tf_stamped.transform.translation.y = end_positions_[1];
        tf_stamped.transform.translation.z = end_positions_[2];

        Eigen::Isometry3d transform = solve::Xyzrpy2Isometry(&end_positions_[0]);

        Eigen::Quaterniond quaternion = Eigen::Quaterniond(transform.rotation());

        tf_stamped.transform.rotation.w = quaternion.w();
        tf_stamped.transform.rotation.x = quaternion.x();
        tf_stamped.transform.rotation.y = quaternion.y();
        tf_stamped.transform.rotation.z = quaternion.z();

        tf_msg.transforms.push_back(tf_stamped);
        //==============================================================================================================
        tf_stamped.header.frame_id = "odom";
        tf_stamped.child_frame_id = "tool_end";
        
        std::vector<double> xyzrpy = tools_->ForwardKinematicsRpy(joint_positions_);

        tf_stamped.transform.translation.x = xyzrpy[0];
        tf_stamped.transform.translation.y = xyzrpy[1];
        tf_stamped.transform.translation.z = xyzrpy[2];

        Eigen::Isometry3d transform_tool = solve::Xyzrpy2Isometry(&xyzrpy[0]);

        Eigen::Quaterniond quaternion_tool = Eigen::Quaterniond(transform_tool.rotation());

        tf_stamped.transform.rotation.w = quaternion_tool.w();
        tf_stamped.transform.rotation.x = quaternion_tool.x();
        tf_stamped.transform.rotation.y = quaternion_tool.y();
        tf_stamped.transform.rotation.z = quaternion_tool.z();

        tf_msg.transforms.push_back(tf_stamped);  
        //==============================================================================================================

        joint_tf_publisher_->publish(tf_msg);
    }
}

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<arx::r5::R5Visualization>());
    rclcpp::shutdown();
    return 0;
}
