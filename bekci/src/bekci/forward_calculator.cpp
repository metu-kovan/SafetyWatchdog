#include <ros/ros.h>
#include <bekci/JointValue.h>
#include <sensor_msgs/JointState.h>
#include <bekci/JointPose.h>
#include <bekci/Pose.h>
#include <map>
#include <math.h>
#include <vector>

using namespace std;


//#define UR5_PARAMS

const double d1 =  0.089159;
const double al1= 1.570796327;
const double a2 = -0.42500;
const double a3 = -0.39225;
const double d4 =  0.10915;
const double d5 =  0.09465;
const double d6 =  0.0823;


ros::Publisher *pubPtr;
map<string,float> ordered_q;
vector<float> q_values;
vector< bekci::Pose > pose_hold;



float c1;
float c2;
float c3;
float c4;
float c5;
float c6;

float s1 ;
float s2 ;
float s3 ;
float s4 ;
float s5 ;
float s6 ;

float c1d4 ;
float d4s1 ;
float a2s2 ;
float c2s3 ;
float c3s2 ;
float c2c3 ;
float s2s3 ;



float a2c1c2;
float a2c2s1;
float a3c2s3;
float a3c3s2;

float c1c2c3;
float c2c3s1;
float c1s2s3;
float s1s2s3;

float c1c3s2;
float c1c2s3;
float c2s1s3;
float c3s1s2;

float a3c1s2s3;
float a3c1c2c3;
float a3s1s2s3;
float a3c2c3s1;



void forward() {
    c1 = cos(q_values[0]);
    c2 = cos(q_values[1]);
    c3 = cos(q_values[2]);
    c4 = cos(q_values[3]);
    c5 = cos(q_values[4]);
    c6 = cos(q_values[5]);

    s1 = sin(q_values[0]);
    s2 = sin(q_values[1]);
    s3 = sin(q_values[2]);
    s4 = sin(q_values[3]);
    s5 = sin(q_values[4]);
    s6 = sin(q_values[5]);
    
    c1d4 = c1*d4;
    d4s1 = d4*s1;
    a2s2 = a2*s2;
    c2s3 = c2*s3;
    c3s2 = c3*s2;
    c2c3 = c2*c3;
    s2s3 = s2*s3;



    a2c1c2 = a2*c1*c2;
    a2c2s1 = a2*c2*s1;
    a3c2s3 = a3*c2s3;
    a3c3s2 = a3*c3s2;

    c1c2c3 = c1*c2c3;
    c2c3s1 = c2c3*s1;
    c1s2s3 = c1*s2s3;
    s1s2s3 = s1*s2s3;

    c1c3s2 = c1*c3s2;
    c1c2s3 = c1*c2s3;
    c2s1s3 = c2*s1*s3;
    c3s1s2 = c3*s1*s2;

    a3c1s2s3 = a3*c1s2s3;
    a3c1c2c3 = a3*c1c2c3;
    a3s1s2s3 = a3*s1s2s3;
    a3c2c3s1 = a3*c2c3s1;


    pose_hold[0].x = 0;
    pose_hold[0].y = 0;
    pose_hold[0].z = d1;

    pose_hold[1].x = a2c1c2;
    pose_hold[1].y = a2c2s1;
    pose_hold[1].z = d1 + a2s2;

    pose_hold[2].x = a2c1c2 - a3c1s2s3 + a3c1c2c3;
    pose_hold[2].y = a2c2s1 - a3s1s2s3 + a3c2c3s1;
    pose_hold[2].z = d1 + a2s2 + a3c2s3 + a3c3s2;

    pose_hold[3].x = d4s1 + a2c1c2 - a3c1s2s3 + a3c1c2c3;
    pose_hold[3].y = a2c2s1 - c1d4 - a3s1s2s3 + a3c2c3s1;
    pose_hold[3].z = d1 + a2s2 + a3c2s3 + a3c3s2;

    pose_hold[4].x = d4s1 + d5*(c4*(c1c2s3 + c1c3s2) + s4*(c1c2c3 - c1s2s3)) + a2c1c2 - a3c1s2s3 + a3c1c2c3;
    pose_hold[4].y = d5*(c4*(c2s1s3 + c3s1s2) + s4*(c2c3s1 - s1s2s3)) - c1d4 + a2c2s1 - a3s1s2s3 + a3c2c3s1;
    pose_hold[4].z = d1 + a2s2 - d5*(c4*(c2c3 - s2s3) - s4*(c2s3 + c3s2)) + a3c2s3 + a3c3s2;

    pose_hold[5].x = d4s1 + d6*(c5*s1 - s5*(c4*(c1c2c3 - c1s2s3) - s4*(c1c2s3 + c1c3s2))) + d5*(c4*(c1c2s3 + c1c3s2) + s4*(c1c2c3 - c1s2s3)) + a2c1c2 - a3c1s2s3 + a3c1c2c3;
    pose_hold[5].y = d5*(c4*(c2s1s3 + c3s1s2) + s4*(c2c3s1 - s1s2s3)) - c1d4 - d6*(c1*c5 + s5*(c4*(c2c3s1 - s1s2s3) - s4*(c2s1s3 + c3s1s2))) + a2c2s1 - a3s1s2s3 + a3c2c3s1;
    pose_hold[5].z = d1 + a2s2 - d5*(c4*(c2c3 - s2s3) - s4*(c2s3 + c3s2)) + a3c2s3 + a3c3s2 - d6*s5*(c4*(c2s3 + c3s2) + s4*(c2c3 - s2s3));
    
}



void receive_values(const bekci::JointValue & msg) {
    q_values[0] = msg.values[0];
    q_values[1] = msg.values[1];
    q_values[2] = msg.values[2];
    q_values[3] = msg.values[3];
    q_values[4] = msg.values[4];
    q_values[5] = msg.values[5];
    forward();
    bekci::JointPose send_msg;
    send_msg.DOF = 6;

    //Base is accepted as 0 0 0 so not included.

    send_msg.poses.push_back(pose_hold[0]);
    send_msg.poses.push_back(pose_hold[1]);
    send_msg.poses.push_back(pose_hold[2]);
    send_msg.poses.push_back(pose_hold[3]);
    send_msg.poses.push_back(pose_hold[4]);
    send_msg.poses.push_back(pose_hold[5]);

    pubPtr->publish(send_msg);

    
}


int main(int argc, char  *argv[])
{

    ros::init(argc,argv,"forward_calculator");

    ros::NodeHandle nh;
    pose_hold.resize(6);
    q_values.resize(6);
    ros::Subscriber sub_state = nh.subscribe("/converted_joint_values", 1000, &receive_values);
    pubPtr = new ros::Publisher(nh.advertise<bekci::JointPose>("/robot_pose_value",1000));
    while(ros::ok()) {
        ros::spinOnce();    
    }

    
    delete pubPtr;
    
    return 0;

}