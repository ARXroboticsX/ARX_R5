#include "arx_r5_controller/KeyBoard.hpp"

#include <termio.h>
#include <stdio.h>
#include <unistd.h>

namespace arx::r5
{
    KeyBoardNode::KeyBoardNode() : Node("keyboard_node")
    {
        joint_cmd_publisher_ = this->create_publisher<arx5_arm_msg::msg::RobotCmd>("arm_cmd", 1);

        joint_status_subscriber_ = this->create_subscription<arx5_arm_msg::msg::RobotStatus>(
            "arm_status", 1, std::bind(&KeyBoardNode::getEndPoseCallBack, this, std::placeholders::_1));

        timer_ = this->create_wall_timer(std::chrono::milliseconds(1), std::bind(&KeyBoardNode::Update, this));
    }

    void KeyBoardNode::Update()
    {

        key_[0] = ScanKeyBoard();

        printf(":%d\r\n", key_[0]);

        // 让切换重力补偿模式时目标位置跟随
        if (g_comp_flag_ == true)
        {
            // 让目标位置等于现在位置
            message_.end_pos[0] = status_end_positions_[0];
            message_.end_pos[1] = status_end_positions_[1];
            message_.end_pos[2] = status_end_positions_[2];
            message_.end_pos[3] = status_end_positions_[3];
            message_.end_pos[4] = status_end_positions_[4];
            message_.end_pos[5] = status_end_positions_[5];
            g_comp_flag_ = false;
        }

        /*up*/
        if (key_[0] == 65 && key_[1] == 91 && key_[2] == 27)
        {
            message_.end_pos[2] += 0.005;
            message_.mode = 4;
        }

        /*down*/
        else if (key_[0] == 66 && key_[1] == 91 && key_[2] == 27)
        {
            message_.end_pos[2] -= 0.005;
            message_.mode = 4;
        }

        /*left*/
        else if (key_[0] == 68 && key_[1] == 91 && key_[2] == 27)
        {
            message_.end_pos[1] += 0.005;
            message_.mode = 4;
        }

        /*right*/
        else if (key_[0] == 67 && key_[1] == 91 && key_[2] == 27)
        {
            message_.end_pos[1] -= 0.005;
            message_.mode = 4;
        }

        /*w*/
        else if (key_[0] == 119)
        {
            message_.end_pos[0] += 0.005;
            message_.mode = 4;
        }

        /*s*/
        else if (key_[0] == 115)
        {
            message_.end_pos[0] -= 0.005;
            message_.mode = 4;
        }

        /*a*/
        else if (key_[0] == 97)
        {
            message_.end_pos[1] += 0.005;
            message_.mode = 4;
        }

        /*d*/
        else if (key_[0] == 100)
        {
            message_.end_pos[1] -= 0.005;
            message_.mode = 4;
        }

        /*i*/
        else if (key_[0] == 105)
        {
            printf("重力补偿\n");
            message_.mode = 3;
            g_comp_flag_ = true;
        }

        /*n*/
        else if (key_[0] == 110)
        {
            message_.end_pos[3] -= 0.05;
            message_.mode = 4;
        }

        /*m*/
        else if (key_[0] == 109)
        {
            message_.end_pos[3] += 0.05;
            message_.mode = 4;
        }

        /*,*/
        else if (key_[0] == 44)
        {
            message_.end_pos[5] += 0.05;
            message_.mode = 4;
        }

        /*/*/
        else if (key_[0] == 47)
        {
            message_.end_pos[5] -= 0.05;
            message_.mode = 4;
        }

        /*.*/
        else if (key_[0] == 46)
        {
            message_.end_pos[4] -= 0.05;
            message_.mode = 4;
        }

        /*l*/
        else if (key_[0] == 108)
        {
            message_.end_pos[4] += 0.05;
            message_.mode = 4;
        }

        /*r*/
        else if (key_[0] == 114)
        {
            message_.end_pos[0] = 0;
            message_.end_pos[1] = 0;
            message_.end_pos[2] = 0;
            message_.end_pos[3] = 0;
            message_.end_pos[4] = 0;
            message_.end_pos[5] = 0;
            message_.mode = 1;
            message_.gripper = 0;
        }

        /*o*/
        else if (key_[0] == 111)
        {
            message_.gripper += 0.15;
            message_.mode = 4;
        }

        /*c*/
        else if (key_[0] == 99)
        {
            message_.gripper -= 0.15;
            message_.mode = 4;
        }

        key_[2] = key_[1];
        key_[1] = key_[0];

        message_.header.stamp = this->get_clock()->now();

        joint_cmd_publisher_->publish(message_);
    }

    int KeyBoardNode::ScanKeyBoard()
    {
        int in;
        struct termios new_settings;
        struct termios stored_settings;
        tcgetattr(STDIN_FILENO, &stored_settings); // 获得stdin 输入
        new_settings = stored_settings;            //
        new_settings.c_lflag &= (~ICANON);         //
        new_settings.c_cc[VTIME] = 0;
        tcgetattr(STDIN_FILENO, &stored_settings); // 获得stdin 输入
        new_settings.c_cc[VMIN] = 1;
        tcsetattr(STDIN_FILENO, TCSANOW, &new_settings); //
        in = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &stored_settings);
        return in;
    }

    void KeyBoardNode::getEndPoseCallBack(const arx5_arm_msg::msg::RobotStatus::SharedPtr msg)
    {
        for (size_t i = 0; i < 6; i++)
        {
            status_end_positions_[i] = msg->end_pos[i];
        }
    }
}

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<arx::r5::KeyBoardNode>());
    rclcpp::shutdown();
    return 0;
}
