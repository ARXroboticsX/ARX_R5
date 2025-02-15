from bimanual import SingleArm
from typing import Dict, Any
import numpy as np

def test_single_arm(single_arm0: SingleArm, single_arm1: SingleArm):
    #single_arm.go_home()
    while(1):
        xyzrpy = np.array([0.0, 0.0, 0.1,0.0, 0.0, 0.0])  # x, y, z 位置

        success = single_arm0.set_ee_pose_xyzrpy(xyzrpy)
        success = single_arm1.set_ee_pose_xyzrpy(xyzrpy)

        while(1):
            print("testing ...")

        #print(single_arm0.get_ee_pose())
        #print(single_arm0.get_joint_positions())

        #positions = [0.5, 1.0, -0.5]  # 指定每个关节的位置
        #joint_names = ["joint1", "joint2", "joint3"]  # 对应关节的名称

        #success = single_arm0.set_joint_positions(positions=positions, joint_names=joint_names)

if __name__ == "__main__":
    arm_config_0: Dict[str, Any] = {
        "can_port": "can1",
        "type": 0,
        # Add necessary configuration parameters for the left arm
    }

    arm_config_1: Dict[str, Any] = {
        "can_port": "can3",
        "type": 0,
        # Add necessary configuration parameters for the left arm
    }
    single_arm0 = SingleArm(arm_config_0)
    single_arm1 = SingleArm(arm_config_1)
    test_single_arm(single_arm0,single_arm1)