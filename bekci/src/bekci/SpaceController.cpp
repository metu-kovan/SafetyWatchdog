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


#include <vector>
#include <ros/package.h>
#include <boost/algorithm/string.hpp>
#include <control_msgs/FollowJointTrajectoryActionGoal.h>
#include <actionlib_msgs/GoalID.h>
#include <stdlib.h>
using namespace std;


ros::Publisher* pub; 
string current_goal;
vector<Sphere> sphere_holder;
vector<Plane> plane_holder;
double margin;




void goalIDKeeper(const control_msgs::FollowJointTrajectoryActionGoal & msg) {
    current_goal = msg.goal_id.id;
}



void robotPoseReceiver(const bekci::JointPose & in_msg) {
    for(int i=0;i<in_msg.DOF;i++) {
        sphere_holder[i].setValues (in_msg.radiuses[i],in_msg.poses[i]);
        
    }

    int status;
    int old_status;
    int sp;
    for(int i=0;i<plane_holder.size();i++) {
        old_status = 0;
        sp = 0;
        for(int k=0;k<sphere_holder.size();k++) {

            status = plane_holder[i].checkSphereStatus(sphere_holder[k],margin);
            if(status> old_status) {
                old_status = status;
                sp = k;
            }
            //cout<<"For plane "<<i<< " Sphere "<<k<<"in the status of "<<status<<endl;
        }
        if(old_status>0) {
            ROS_INFO_STREAM("For Plane "<<i<<" higshest danger from sphere "<<sp<<"with status "<<old_status );    
        }
        
    }


}


int main(int argc,char** argv) {
    ros::init(argc, argv, "space_restriction");
    ros::NodeHandle nh;
    string line;
    double n_x;
    double n_y;
    double n_z;
    double p_x;
    double p_y;
    double p_z;
    //ifstream inFile("inputs/space_limits.xml");
    Point dummy(0,0,0);
    sphere_holder.resize(6);
    for(int i=0;i<6;i++) {
        sphere_holder[i].setValues(0.1,dummy)    ;
    }
    
    string::size_type sz;
    string pack("bekci");
    string  a= ros::package::getPath(pack);

    pugi::xml_document doc;

    pugi::xml_parse_result result = doc.load_file(argv[2]);

    
    margin = doc.child("Planes").attribute("WarningM").as_float();
    for (pugi::xml_node plane = doc.child("Planes").child("Plane"); plane; plane = plane.next_sibling("Plane"))
    {

        n_x = plane.child("Normal").attribute("x").as_float();
        n_y = plane.child("Normal").attribute("y").as_float();
        n_z = plane.child("Normal").attribute("z").as_float();

        p_x = plane.child("Point").attribute("x").as_float();
        p_y = plane.child("Point").attribute("y").as_float();
        p_z = plane.child("Point").attribute("z").as_float();

        Plane temp(n_x, n_y, n_z, p_x, p_y, p_z);
        temp.normal.normalize();
        plane_holder.push_back(temp);
    }

    

    for(int i = 0;i<4;i++) {
        plane_holder[i].print();
    }
    plane_holder[0].normal.normalize();
    plane_holder[0].print();
    ros::Rate rate(10);
    ros::Subscriber sub_state = nh.subscribe("/robot_joint_pose", 100, &robotPoseReceiver);
    ros::Subscriber sub_goal = nh.subscribe("/follow_joint_trajectory/goal",1000,&goalIDKeeper);
    
    pub= new ros::Publisher(nh.advertise<actionlib_msgs::GoalID>("/follow_joint_trajectory/cancel",10));
    while(ros::ok()) {

        ros::spinOnce();
        rate.sleep();
    }

    delete pub;
}