#include <ros/ros.h>
#include <ros/package.h>

#include <bekci/QuantativeSafetyStatus.h>
#include <bekci/JointVelocity.h>

#include <iostream>

#include <string>
#include <vector>
#include <math.h>

#include "JointLimits.h"
#include <pugi/pugixml.hpp>


using namespace std;

ros::Publisher* pub; 

vector<JointLimits> joint_limits;


double margin;
double maxi;

//this is the main node which block and also subscriber
void limiter(const bekci::JointVelocity & in_msg)
{
    maxi = 0;
    bekci::QuantativeSafetyStatus out_msg;
    out_msg.joint_status.resize(in_msg.DOF);
    for(int i=0;i<in_msg.DOF;i++) //because of 6 joints
    {
        //ROS_INFO_STREAM("for joint "<<i<<" "<<joint_limits[i].joint_name<<" joint speed" 
        //        "limits is "<<joint_limits[i].speed_limit<<" and its current speed is " <<abs(in_msg.velocities[i]));
        if (fabs(in_msg.velocities[i])>maxi) {
            maxi = fabs(in_msg.velocities[i]);
        }
        out_msg.joint_status[i] = 0;
        if(joint_limits[i].isSmaller(fabs(in_msg.velocities[i]))==true) {
            ROS_INFO_STREAM("joint "<<joint_limits[i].joint_name<<" off limits with speed"<< in_msg.velocities[i]);
            out_msg.joint_status[i] = 2;
        } else if(joint_limits[i].isSmaller(fabs(in_msg.velocities[i])+margin)==true)
        {
            ROS_INFO_STREAM("joint "<<joint_limits[i].joint_name<<" in margin with speed"<< in_msg.velocities[i]);
            out_msg.joint_status[i] = 1;
        } 
    }
    cout<<maxi<<endl;
    pub->publish(out_msg);
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

    pugi::xml_parse_result result = doc.load_file(argv[1]);

    
    margin = doc.child("Joints").attribute("WarningM").as_float();
    cout<<margin<<endl;
    for (pugi::xml_node joint = doc.child("Joints").child("Joint"); joint; joint = joint.next_sibling("Joint"))
    {

        j_name = joint.attribute("Name").as_string();
        j_limit = joint.attribute("SpeedLimit").as_float();
        cout<<"j_name "<<j_name<<endl;
        JointLimits temp(j_name,j_limit);

        joint_limits.push_back(temp);
    }
    cout<<joint_limits.size()<<endl;
    ros::Rate rate(10);


    ros::Subscriber sub_state = nh.subscribe("/joint_velocity", 100, &limiter);

    
    pub= new ros::Publisher(nh.advertise<bekci::QuantativeSafetyStatus>("/quantative_safety",10));

    while(ros::ok())
    {
        ros::spinOnce();
        rate.sleep();
    }


    
    delete pub;
}
