#include <ros/ros.h>
#include <arx_msgs/JointInformation.h>
#include <arx_msgs/JointControl.h>
#include <arx_msgs/PosCmd.h>
#include "arx_r5_src/interfaces/InterfacesThread.hpp"

using namespace arx;
using namespace arx::r5;

std::shared_ptr<InterfacesThread> r5_interface_ptr;

int main(int argc, char** argv)
{
    ros::init(argc, argv, "arm_node");
    ros::NodeHandle nh = ros::NodeHandle("~");
    std::string bus_name = nh.param("bus_name", std::string("can0"));
    ROS_INFO("bus_name: %s", bus_name.c_str());
    r5_interface_ptr = std::make_shared<InterfacesThread>(bus_name, 1);
    r5_interface_ptr->setArmStatus(InterfacesThread::G_COMPENSATION);

    ros::Publisher pub_joint = nh.advertise<arx_msgs::JointControl>("joint_control", 10);
    ros::Publisher pub_pos = nh.advertise<arx_msgs::PosCmd>("/ARX_VR_L", 10);

    ros::Rate loop_rate(200);

    while (ros::ok())
    {
        std::vector<double> joint_pos_vector = r5_interface_ptr->getJointPositons();
        std::vector<double> joint_vel_vector = r5_interface_ptr->getJointVelocities();
        //发送关节数据
        arx_msgs::JointControl msg_joint;
        for (int i = 0; i < 7; i++)
        {
            msg_joint.joint_pos[i] = joint_pos_vector[i];
            msg_joint.joint_vel[i] = joint_vel_vector[i];
        }
        pub_joint.publish(msg_joint);
        //发送末端姿态
        arx_msgs::PosCmd msg_pos_back;
        Eigen::Isometry3d transform = r5_interface_ptr->getEndPose();
        std::vector<double> xyzrpy = {0, 0, 0, 0, 0, 0};
        xyzrpy = solve::Isometry2Xyzrpy(transform);
        msg_pos_back.x = xyzrpy[0];
        msg_pos_back.y = xyzrpy[1];
        msg_pos_back.z = xyzrpy[2];
        msg_pos_back.roll = xyzrpy[3];
        msg_pos_back.pitch = xyzrpy[4];
        msg_pos_back.yaw = xyzrpy[5];
        pub_pos.publish(msg_pos_back);
        //topic
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}
