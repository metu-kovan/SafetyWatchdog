#include <ros/ros.h>
#include <bekci/JointValue.h>
#include <sensor_msgs/JointState.h>
#include <map>
#include <vector>

using namespace std;

ros::Publisher *pubPtr;
map<string,float> ordered_q;



void turner(const sensor_msgs::JointState & msg) {
    bekci::JointValue converted_msg;
    for(int i=0;i<6;i++) {
        ordered_q[msg.name[i]] = msg.position[i];
    }
    converted_msg.DOF = 6;
    converted_msg.names.push_back("shoulder_pan_joint");
    converted_msg.names.push_back("shoulder_lift_joint");
    converted_msg.names.push_back("elbow_joint");
    converted_msg.names.push_back("wrist_1_joint");
    converted_msg.names.push_back("wrist_2_joint");
    converted_msg.names.push_back("wrist_3_joint");
    converted_msg.values.push_back(ordered_q["shoulder_pan_joint"]);
    converted_msg.values.push_back(ordered_q["shoulder_lift_joint"]);
    converted_msg.values.push_back(ordered_q["elbow_joint"]);
    converted_msg.values.push_back(ordered_q["wrist_1_joint"]);
    converted_msg.values.push_back(ordered_q["wrist_2_joint"]);
    converted_msg.values.push_back(ordered_q["wrist_3_joint"]);
    pubPtr->publish(converted_msg);
}


int main(int argc, char  *argv[])
{
    ordered_q["shoulder_pan_joint"] = 0;
    ordered_q["shoulder_lift_joint"] = 0;
    ordered_q["elbow_joint"] = 0;
    ordered_q["wrist_1_joint"] = 0;
    ordered_q["wrist_2_joint"] = 0;
    ordered_q["wrist_3_joint"] = 0;
    ros::init(argc,argv,"Joint_Value_Converter");
    ros::NodeHandle nh;
    ros::Subscriber sub_state = nh.subscribe("/joint_states", 1000, &turner);
    pubPtr = new ros::Publisher(nh.advertise<bekci::JointValue>("/converted_joint_values",1000));
    while(ros::ok()) {
        ros::spinOnce();    
    }

    
    delete pubPtr;
    
    return 0;

}