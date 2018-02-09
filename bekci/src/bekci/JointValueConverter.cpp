#include <ros/ros.h>
#include <bekci/JointValue.h>
#include <sensor_msgs/JointState.h>

ros::Publisher *pubPtr;

void turner(const sensor_msgs::JointState & msg) {
    bekci::JointValue converted_msg;
}


int main(int argc, char const *argv[])
{
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