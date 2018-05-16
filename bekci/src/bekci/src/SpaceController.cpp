#include <ros/ros.h>

#include <pugi/pugixml.hpp>
//#include <geometric_shapes/shapes.h>
#include "Point.h"
#include "Sphere.h"
#include "Vec3d.h"
#include "Plane.h"
#include "Box.h"

#include <iostream>
#include <bekci/Pose.h>
#include <bekci/JointPose.h>
#include <bekci/SpaceSafetyStatus.h>
#include <map>
#include <string>
#include <vector>

#include <ros/package.h>
#include <boost/algorithm/string.hpp>
#include <bekci/JointVelocity.h>

#include <stdlib.h>
using namespace std;


#ifndef zero
#define zero 0.05
#endif

#ifndef shrink_value
#define shrink_value 10
#endif

ros::Publisher* pub; 
string current_goal;
vector<Sphere> sphere_holder;
vector<Box> box_holder;
double margin;
double divide;
double glob_wait;
void robotVelocityReceiver(const bekci::JointVelocity & in_msg) {                       // Checks for sphere shrink
    int count = 0;
    for(int i=0;i<in_msg.DOF;i++) 
    {
        if (fabs(in_msg.velocities[i])>zero) {                                          // if velocity is larger than dont shrink
            count++;

        } 
        
    }
    if (count >0 && glob_wait>5) {
        divide = 1;
    } else if (count == 0){
        divide = shrink_value;
        glob_wait = 0;
    }
    glob_wait++;
    cout<<glob_wait<<"         ---------            "<<divide<<endl;
}




// gets the values of the joints positions from ForwardCalculator node
void robotPoseReceiver(const bekci::JointPose & in_msg) {
    bekci::SpaceSafetyStatus out_msg;                                                   //  output message
    for(int i=0;i<in_msg.DOF;i++) {                                                     // updates joint positions and radiuses based on the output of Forward
        sphere_holder[i].setValues ((in_msg.radiuses[i]/divide),in_msg.poses[i]);       // uses the sphere class function
//        sphere_holder[i].print();
    }

    int sphere_status;                                                                  // sphere status for each box
    int box_status;                                                                     // sphere status is updated for each sphere but box_status kept for each box
    int sp;                                                                             // sphere count
    for(int i=0;i<box_holder.size();i++) {                                              // for each box in the system
        box_status = 0;                                                                 
        sp = 0;
        for(int k=1;k<sphere_holder.size();k++) {                                       // check every sphere

            sphere_status = box_holder[i].checkSphereStatus(sphere_holder[k],margin);  // checks the status of the sphere compared to specific box
            if(sphere_holder[k].status<sphere_status) {                                // if current status is larger than previous known status update that
                sphere_holder[k].status = sphere_status;   
            }
            if(sphere_status> box_status) {
                box_status = sphere_status;
                sp = k;
            }
            // cout<<sphere_status<<endl;
            //cout<<"For plane "<<i<< " Sphere "<<k<<"in the status of "<<status<<endl;
        }
        // if(box_status>0) {
        //     ROS_INFO_STREAM("For Box "<<i<<" higshest danger from sphere "<<sp<<"with status "<<box_status );    
        // }
        
    }
    int max = 0;                                                                        // getting the highest valued state between spheres
    for(int i=0;i<sphere_holder.size();i++) {
        if(max<sphere_holder[i].status) {
            max  = sphere_holder[i].status;
        }
        // out_msg.sphere_status[i] = sphere_holder[i].status;
    }
    out_msg.zone = max;                                                                 // publishes the highest value
    pub->publish(out_msg);                                                              // 2 = stop, 1 = shared region warning, 0 = do nothing

}


int main(int argc,char** argv) {
    ros::init(argc, argv, "space_restriction");                                         
    ros::NodeHandle nh;
    string line;        
    glob_wait = 0;                                                                    
    double n_x;
    double n_y;
    double n_z;
    double p_x;
    double p_y;
    double p_z;
    int p_count;
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

    pugi::xml_parse_result result = doc.load_file(argv[1]);

    
    margin = doc.child("Boxes").attribute("WarningM").as_float();
    for (pugi::xml_node box = doc.child("Boxes").child("Box"); box; box = box.next_sibling("Box"))
    {
        vector<Plane> plane_holder;
        p_count = box.attribute("PlaneCount").as_int();
        bool s = box.attribute("Shared").as_bool();
        for(pugi::xml_node plane = box.child("Plane"); plane; plane = plane.next_sibling("Plane") ) {
            n_x = plane.child("Normal").attribute("x").as_double();
            n_y = plane.child("Normal").attribute("y").as_double();
            n_z = plane.child("Normal").attribute("z").as_double();

            p_x = plane.child("Point").attribute("x").as_double();
            p_y = plane.child("Point").attribute("y").as_double();
            p_z = plane.child("Point").attribute("z").as_double();
            Plane temp(n_x, n_y, n_z, p_x, p_y, p_z);
            temp.normal.normalize();
            plane_holder.push_back(temp);
        }
        
        Box temp_b(plane_holder,s);
        box_holder.push_back(temp_b);

        
    }

    

    for(int i = 0;i<box_holder.size();i++) {
        box_holder[i].print();
    }
    
    ros::Rate rate(10);
    ros::Subscriber sub_state   = nh.subscribe("/robot_joint_pose", 100, &robotPoseReceiver);
    ros::Subscriber sub_vel     = nh.subscribe("/joint_velocity",1, &robotVelocityReceiver);
    
    pub= new ros::Publisher(nh.advertise<bekci::SpaceSafetyStatus>("/space_safety",10));

    while(ros::ok()) {

        ros::spinOnce();
        rate.sleep();
    }

    delete pub;
}