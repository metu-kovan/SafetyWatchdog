#include <ros/ros.h>

#include <pugi/pugixml.hpp>
//#include <geometric_shapes/shapes.h>
#include "Point.h"
#include "Sphere.h"
#include "Vec3d.h"
#include "Plane.h"

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

#define warning_margin 0.1

/*





*/

ros::Publisher* pub; 
string current_goal;
vector<bekci::Pose> pose_holder;
//vector<shapes::Plane> plane_holder;

void pose_print(bekci::Pose & a) {
    ROS_INFO_STREAM("x:"<<a.x<<" y:"<<a.y<<" z:"<<a.z);
}


void goalIDKeeper(const control_msgs::FollowJointTrajectoryActionGoal & msg) {
    current_goal = msg.goal_id.id;
}



void robotPoseReceiver(const bekci::JointPose & in_msg) {
    pose_holder[0] = in_msg.poses[0];
    pose_holder[1] = in_msg.poses[1];
    pose_holder[2] = in_msg.poses[2];
    pose_holder[3] = in_msg.poses[3];
    pose_holder[4] = in_msg.poses[4];
    pose_holder[5] = in_msg.poses[5];


}


int main(int argc,char** argv) {
    ros::init(argc, argv, "space_restriction");
    ros::NodeHandle nh;
    string line;
    //ifstream inFile("inputs/space_limits.xml");

    pose_holder.resize(6);
    string::size_type sz;
    string pack("bekci");
    string  a= ros::package::getPath(pack);

    pugi::xml_document doc;

    pugi::xml_parse_result result = doc.load_file("/home/fatih/git/GuvenlikBekcisi/bekci/src/bekci/input/space_limits.xml");

    

    /*for (pugi::xml_node plane = doc.child("Planes").child("Plane"); plane; plane = plane.next_sibling("Plane"))
    {


        shapes::Plane temp(plane.attribute("A").as_float(),plane.attribute("B").as_float(),
            plane.attribute("C").as_float(),plane.attribute("D").as_float());

        plane_holder.push_back(temp);
    }

    

    for(int i = 0;i<4;i++) {
        plane_holder[i].print();
    }*/
    ros::Rate rate(10);
    ros::Subscriber sub_state = nh.subscribe("/robot_pose_value", 100, &robotPoseReceiver);
    ros::Subscriber sub_goal = nh.subscribe("/follow_joint_trajectory/goal",1000,&goalIDKeeper);
    
    pub= new ros::Publisher(nh.advertise<actionlib_msgs::GoalID>("/follow_joint_trajectory/cancel",10));
    while(ros::ok()) {

        ros::spinOnce();
        rate.sleep();
    }

    delete pub;
}