#include <ros/ros.h>
#include <control_msgs/FollowJointTrajectoryActionGoal.h>
#include <actionlib_msgs/GoalID.h>
#include <bekci/SpaceSafetyStatus.h>
#include <bekci/QuantativeSafetyStatus.h>
#include <bekci/Action.h>

#include <iostream>
#include <map>
#include <string>
#include <vector>



using namespace std;
int zone;
int vlimit;
int ZTF; // zone transition flag

bekci::QuantativeSafetyStatus current_quantative;
bekci::SpaceSafetyStatus current_space;



void spaceCallback(const bekci::SpaceSafetyStatus & in_msg) {
    if(zone < in_msg.zone)
        zone = in_msg.zone;
	// actionlib_msgs::GoalID cancel;
 //    current_space = in_msg;
    // for(int i=0;i<in_msg.sphere_status.size();i++) {
    // 	if(in_msg.sphere_status[i]==2) {
    // 		ROS_INFO_STREAM("BOY you are too close to border "<<i);
    // 		cancel.id = current_goal.id;
    // 		pub->publish(cancel);
    // 	}
    // }
}
void quantativeCallback(const bekci::QuantativeSafetyStatus & in_msg) {
    if(vlimit< in_msg.vlimit)
        vlimit = in_msg.vlimit;
	// actionlib_msgs::GoalID cancel;
 //    current_quantative = in_msg;
 //    for(int i=0;i<in_msg.joint_status.size();i++) {
 //    	if(in_msg.joint_status[i]==2) {
 //    		ROS_INFO_STREAM("BOY you are too fast "<< i);
 //    		cancel.id = current_goal.id;
 //    		pub->publish(cancel);
 //    	}
 //    }
}


int main(int argc,char** argv) {
    ros::init(argc, argv, "SafetyStatusDecider");
    ros::NodeHandle nh;
	zone = 0;
    vlimit = 0;
    ZTF = 0;
    ros::Subscriber space_sub = nh.subscribe("/space_safety",1000,spaceCallback);
    ros::Subscriber quantative_sub = nh.subscribe("/quantative_safety",1000,quantativeCallback);
    ros::Publisher act_pub = nh.advertise<bekci::Action>("/robot_action",10);
	ros::Subscriber goal_sub;
 



    ros::Rate rate(10);

    while(ros::ok()) {
    	ros::spinOnce();
        bekci::Action out_msg;
        out_msg.action = 0;
        if(zone == 2) {
            ROS_INFO_STREAM("ROBOT IS IN THE RED ZONE---STOPING THE ROBOT");
            out_msg.action = 2;
        } else if(vlimit == 2) {
            ROS_INFO_STREAM("ROBOT IS TOO FAST---STOPING THE ROBOT");
            out_msg.action = 2;
        } else if(zone == 1 && vlimit == 0) {
            ROS_INFO_STREAM("ROBOT IS IN THE SHARED SPACE---DOING NOTHING");
            out_msg.action = 0;
        } else if(zone == 1 && vlimit == 1) {
            ROS_INFO_STREAM("ROBOT IS IN THE SHARED SPACE SLOW DOWN INITIATED");
            out_msg.action = 1;
            ZTF = 1;
        } else if(zone == 0 && ZTF == 1) {
            ROS_INFO_STREAM("ROBOT IS OUT OF SHARE SPACE SPEED NORMALIZATION INITIATED");
            out_msg.action = 3;
            ZTF = 0;
        }
        act_pub.publish(out_msg);
        zone = 0;
        vlimit = 0;
    	rate.sleep();
    }
    



}