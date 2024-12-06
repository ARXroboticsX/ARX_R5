#include <rclcpp/rclcpp.hpp>
#include <arx_msgs/msg/joint_information.hpp>
#include <arx_msgs/msg/joint_control.hpp>
#include <arx_msgs/msg/pos_cmd.hpp>
#include "arx_r5_src/interfaces/InterfacesThread.hpp"

using namespace arx;
using namespace arx::r5;

std::shared_ptr<InterfacesThread> l5_pro_interface_ptr;

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("arm_node");
    node->declare_parameter("bus_name", std::string("can1"));
    std::string bus_name = node->get_parameter("bus_name").as_string();
    l5_pro_interface_ptr = std::make_shared<InterfacesThread>(bus_name,1);
    l5_pro_interface_ptr->setArmStatus(InterfacesThread::G_COMPENSATION);

    auto pub_joint = node->create_publisher<arx_msgs::msg::JointControl>("joint_control",10);
    auto pub_pos = node->create_publisher<arx_msgs::msg::PosCmd>("/ARX_VR_L", 10);

    rclcpp::Rate loop_rate(200);

    while(rclcpp::ok())
    {
        std::vector<double> joint_pos_vector = l5_pro_interface_ptr->getJointPositons();
        std::vector<double> joint_vel_vector = l5_pro_interface_ptr->getJointVelocities();
        //发送关节数据
        arx_msgs::msg::JointControl msg_joint;
        for (int i = 0;i < 7;i++) {
            msg_joint.joint_pos[i] = joint_pos_vector[i];
            msg_joint.joint_vel[i] = joint_vel_vector[i];
        }
        pub_joint->publish(msg_joint);
        //发送末端姿态
        arx_msgs::msg::PosCmd msg_pos_back;
        Eigen::Isometry3d transform = l5_pro_interface_ptr->getEndPose();
        std::vector<double> xyzrpy = {0, 0, 0, 0, 0, 0};
        xyzrpy = solve::Isometry2Xyzrpy(transform);
        msg_pos_back.x = xyzrpy[0];
        msg_pos_back.y = xyzrpy[1];
        msg_pos_back.z = xyzrpy[2];
        msg_pos_back.roll = xyzrpy[3];
        msg_pos_back.pitch = xyzrpy[4];
        msg_pos_back.yaw = xyzrpy[5];
        pub_pos->publish(msg_pos_back);
        //topic
        rclcpp::spin_some(node);
        loop_rate.sleep();
    }
    return 0;
}
