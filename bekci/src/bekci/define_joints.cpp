#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <bekci/JointVelocity.h>
#include <map>
#include <vector>
#include <array>
#include <iostream>

using namespace std;

ros::Publisher *pubJoint;
map<string,float> ordered_q;

void turnerCallback(const sensor_msgs::JointState & msg) {
    bekci::JointVelocity converted_msg;
    for(int i=0;i<6;i++) {
      if (msg.velocity.empty() == 0)
      {
        ordered_q[msg.name[i]] = msg.velocity[i];
      }else
      {
        ordered_q[msg.name[i]] = 0;
      }
    }
    converted_msg.DOF = 6;
    converted_msg.names.push_back("shoulder_pan_joint");
    converted_msg.names.push_back("shoulder_lift_joint");
    converted_msg.names.push_back("elbow_joint");
    converted_msg.names.push_back("wrist_1_joint");
    converted_msg.names.push_back("wrist_2_joint");
    converted_msg.names.push_back("wrist_3_joint");
    converted_msg.velocities.push_back(ordered_q["shoulder_pan_joint"]);
    converted_msg.velocities.push_back(ordered_q["shoulder_lift_joint"]);
    converted_msg.velocities.push_back(ordered_q["elbow_joint"]);
    converted_msg.velocities.push_back(ordered_q["wrist_1_joint"]);
    converted_msg.velocities.push_back(ordered_q["wrist_2_joint"]);
    converted_msg.velocities.push_back(ordered_q["wrist_3_joint"]);
    ROS_INFO_STREAM(converted_msg);
    pubJoint->publish(converted_msg);
}


int main(int argc, char  *argv[])
{
    ordered_q["shoulder_pan_joint"] = 0;
    ordered_q["shoulder_lift_joint"] = 0;
    ordered_q["elbow_joint"] = 0;
    ordered_q["wrist_1_joint"] = 0;
    ordered_q["wrist_2_joint"] = 0;
    ordered_q["wrist_3_joint"] = 0;

    ros::init(argc,argv,"Joint_Velocity_Converter");
    ros::NodeHandle nh;
    ros::Subscriber sub_state = nh.subscribe("/joint_states", 1000, &turnerCallback);
    pubJoint = new ros::Publisher(nh.advertise<bekci::JointVelocity>("/converted_joint_velocities",1000));
    while(ros::ok()) {
        ros::spinOnce();
    }


   delete pubJoint;

    return 0;

}
