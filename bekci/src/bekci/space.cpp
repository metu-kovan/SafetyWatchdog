#include <ros/ros.h>
#include <iostream>
#include <bekci/Pose.h>
#include <bekci/JointPose.h>
#include <map>
#include <string>

#include <fstream>
#include <vector>
#include <ros/package.h>
#include <boost/algorithm/string.hpp>
#include <control_msgs/FollowJointTrajectoryActionGoal.h>
#include <actionlib_msgs/GoalID.h>
#include <stdlib.h>
using namespace std;


bool fault = false;
ros::Publisher* pub; 
map<string,float> ordered_q;
string current_goal;
struct bekci::Pose max_pose;
struct bekci::Pose min_pose;
vector<bekci::Pose> holder;
/*a smaller than b*/
int smaller(bekci::Pose & a,bekci::Pose & b) {
    if(a.x<=b.x && a.y<=b.y && a.z<=b.z)
        return 1;
    return 0;
}
/*a larger than b*/
int larger(bekci.Pose & a,bekci::Pose & b) {
    if(a.x>=b.x && a.y>=b.y && a.z>=b.z)
        return 1;
    return 0;
}
void pose_print(bekci::Pose & a) {
    ROS_INFO_STREAM("x:"<<a.x<<" y:"<<a.y<<" z:"<<a.z);
}



int main(int argc,char** argv) {
    ros::init(argc, argv, "space_restriction");
    ros::NodeHandle nh;
    string line;
    ifstream inFile("/home/fatih/bekci/src/bekci/space_limits.txt");

    holder.resize(6);
    string::size_type sz;
    string pack("bekci");
    ordered_q["shoulder_pan_joint"] = 0;
    ordered_q["shoulder_lift_joint"] = 0;
    ordered_q["elbow_joint"] = 0;
    ordered_q["wrist_1_joint"] = 0;
    ordered_q["wrist_2_joint"] = 0;
    ordered_q["wrist_3_joint"] = 0;
    string  a= ros::package::getPath(pack);
    ROS_INFO_STREAM(a);
    if(inFile.is_open()) {
        ROS_INFO_STREAM("1");
        while( getline(inFile,line)) {
            ROS_INFO_STREAM(line);
            vector<string> temp;
            boost::split(temp, line, boost::is_any_of("="));
            if (temp[0].compare(string("max_x"))==0) {
                max_pose.x = stof(temp[1]);
            } else if (temp[0].compare(string("max_y"))==0) {
                max_pose.y = stof(temp[1]);
            } else if (temp[0].compare(string("max_z"))==0) {
                max_pose.z = stof(temp[1]);
            } else if (temp[0].compare(string("min_x"))==0) {
                min_pose.x = stof(temp[1]);
            } else if (temp[0].compare(string("min_y"))==0) {
                min_pose.y = stof(temp[1]);
            } else if (temp[0].compare(string("min_z"))==0) {
                min_pose.z = stof(temp[1]);
            }

            
        }
        inFile.close();
    }
    ROS_INFO_STREAM("2");
    ros::Rate rate(10);

    ros::Subscriber sub_state = nh.subscribe("/robot_pose_value", 100, &receiver);
    ros::Subscriber sub_goal = nh.subscribe("/follow_joint_trajectory/goal",1000,&goalIDKeeper);
    
    pub= new ros::Publisher(nh.advertise<actionlib_msgs::GoalID>("/follow_joint_trajectory/cancel",10));
    while(ros::ok()) {
        if(fault) {
            return 1;
        }
        ros::spinOnce();
        rate.sleep();
    }

    delete pub;
}