#include <ros/ros.h>
#include <ros/package.h>
#include <control_msgs/FollowJointTrajectoryActionGoal.h>
#include <actionlib_msgs/GoalID.h>
#include <bekci/JointVelocity.h>

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <stdlib.h>

#include "JointLimits.h"
#include <pugi/pugixml.hpp>
#include <boost/algorithm/string.hpp>

using namespace std;

ros::Publisher* pub; 

vector<JointLimits> joint_limits;

double margin;


//this is the main node which block and also subscriber
void limiter(const bekci::JointVelocity & msg)
{


    for(int i=0;i<msg.DOF;i++) //because of 6 joints
    {
        if(name.compare(msg.names[i])==0)
        {
            vec_keep.push_back(msg.velocities[i]);
        }
        //MEssages print to see
        ROS_INFO_STREAM(msg.names[i]<<" limit "<<given_limits[msg.names[i]]<<" message "<<msg.velocities[i]);

        if(abs(given_limits[msg.names[i]]) < abs(msg.velocities[i]))
        {

            ROS_INFO_STREAM("wow");
            fault = true;
            cancel.id=current_goal; //that lib for canceling moveit command **sera
            pub->publish(cancel);
            break;
        }

    }
}

int main(int argc,char** argv)
{
    ros::init(argc, argv, "QuantativeController");
    ros::NodeHandle nh;

    string pack("bekci");
    string  a= ros::package::getPath(pack);
    string j_name;
    double j_limit;
    pugi::xml_document doc;

    pugi::xml_parse_result result = doc.load_file(argv[2]);

    
    margin = doc.child("Joints").attribute("WarningM").as_float();
    for (pugi::xml_node joint = doc.child("Joints").child("Joint"); joint; joint = joint.next_sibling("Joint"))
    {

        j_name = joint.attribute("Name").as_string();
        j_limit = joint.attribute("Limit").as_float();
        
        JointLimits temp(j_name,j_limit);

        joint_limits.push_back(temp);
    }
    ros::Rate rate(10);


    ros::Subscriber sub_state = nh.subscribe("/joint_velocity", 100, &limiter);

    
    pub= new ros::Publisher(nh.advertise<actionlib_msgs::GoalID>("/quantative_safety",10));

    while(ros::ok())
    {
        ros::spinOnce();
        rate.sleep();
    }


    
    delete pub;
}
