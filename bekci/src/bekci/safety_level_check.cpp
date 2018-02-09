#include <ros/ros.h>
#include <iostream>
#include <map>
#include <string>
#include <sensor_msgs/JointState.h>
#include <fstream>
#include <vector>
#include <ros/package.h>
#include <boost/algorithm/string.hpp>
#include <control_msgs/FollowJointTrajectoryActionGoal.h>
#include <actionlib_msgs/GoalID.h>
#include <stdlib.h>
using namespace std;


int main(int argc,char** argv) {
    ros::init(argc, argv, "quantative_limiter");
    ros::NodeHandle nh;
 /*   string line;
    ifstream inFile("/home/fatih/bekci/src/bekci/limits.txt");
    string::size_type sz;
    string pack("bekci");
    string  a= ros::package::getPath(pack);
    ROS_INFO_STREAM(a);
    if(inFile.is_open()) {
        ROS_INFO_STREAM("1");
        while( getline(inFile,line)) {
            ROS_INFO_STREAM(line);
            vector<string> temp;
            boost::split(temp, line, boost::is_any_of("="));
            given_limits[temp[0]] = stof(temp[1],&sz);
            ROS_INFO_STREAM(temp[0]<<temp[1]);
        }
        inFile.close();
    }
    ROS_INFO_STREAM("2");
    ros::Rate rate(10);

    ros::Subscriber sub_state = nh.subscribe("/joint_states", 100, &limiter);
    ros::Subscriber sub_goal = nh.subscribe("/follow_joint_trajectory/goal",1000,&goalIDKeeper);
    
    pub= new ros::Publisher(nh.advertise<actionlib_msgs::GoalID>("/follow_joint_trajectory/cancel",10));
    while(ros::ok()) {

        ros::spinOnce();
        rate.sleep();
    }
    ofstream outFile("/home/fatih/bekci/src/bekci/output.txt");
    if(outFile.is_open()) {
        string temp("");
        string vir(",");
        for(int i=0;i<vec_keep.size();i++) {
            temp = temp+to_string(vec_keep[i])+vir;
        }
        outFile<<temp;
        outFile.close();
    }
    delete pub;*/
}