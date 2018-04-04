#include <ros/ros.h>
#include <control_msgs/FollowJointTrajectoryActionGoal.h>
#include <actionlib_msgs/GoalID.h>
#include <bekci/SpaceSafetyStatus.h>
#include <bekci/QuantativeSafetyStatus.h>

#include <iostream>
#include <map>
#include <string>
#include <vector>



using namespace std;

actionlib_msgs::GoalID current_goal;
bekci::QuantativeSafetyStatus current_quantative;
bekci::SpaceSafetyStatus current_space;
ros::Publisher* pub;


void spaceCallback(const bekci::SpaceSafetyStatus & in_msg) {
	actionlib_msgs::GoalID cancel;
    current_space = in_msg;
    for(int i=0;i<in_msg.sphere_status.size();i++) {
    	if(in_msg.sphere_status[i]==2) {
    		ROS_INFO_STREAM("BOY you are too close to border "<<i);
    		cancel.id = current_goal.id;
    		pub->publish(cancel);
    	}
    }
}
void quantativeCallback(const bekci::QuantativeSafetyStatus & in_msg) {
	actionlib_msgs::GoalID cancel;
    current_quantative = in_msg;
    for(int i=0;i<in_msg.joint_status.size();i++) {
    	if(in_msg.joint_status[i]==2) {
    		ROS_INFO_STREAM("BOY you are too fast "<<i);
    		cancel.id = current_goal.id;
    		pub->publish(cancel);
    	}
    }
}

void goalIDKeeper(const control_msgs::FollowJointTrajectoryActionGoal & msg) {
    current_goal.id = msg.goal_id.id;
}

int main(int argc,char** argv) {
    ros::init(argc, argv, "SafetyStatusDecider");
    ros::NodeHandle nh;
	
    ros::Subscriber space_sub = nh.subscribe("/space_safety",1000,spaceCallback);
    ros::Subscriber quantative_sub = nh.subscribe("/quantative_safety",1000,quantativeCallback);
	ros::Subscriber goal_sub;
    if(argc<2) {
    	ROS_INFO_STREAM("It is a sim then");
    	goal_sub = nh.subscribe("/arm_controller/follow_joint_trajectory/goal",1000,goalIDKeeper);
    	pub= new ros::Publisher(nh.advertise<actionlib_msgs::GoalID>("/arm_controller/follow_joint_trajectory/cancel",10));
    }
    else if (string(argv[1]).compare(string("sim"))==0)
    {
    	ROS_INFO_STREAM("It is a sim then");
    	goal_sub = nh.subscribe("/arm_controller/follow_joint_trajectory/goal",1000,goalIDKeeper);
    	pub= new ros::Publisher(nh.advertise<actionlib_msgs::GoalID>("/arm_controller/follow_joint_trajectory/cancel",10));
    } else if (string(argv[1]).compare(string("real"))==0)
    {
    	ROS_INFO_STREAM("It is a real then");
    	goal_sub = nh.subscribe("/follow_joint_trajectory/goal",1000,goalIDKeeper);
    	pub= new ros::Publisher(nh.advertise<actionlib_msgs::GoalID>("/follow_joint_trajectory/cancel",10));
    }



    ros::Rate rate(10);

    while(ros::ok()) {
    	ros::spinOnce();
    	rate.sleep();
    }
    


    delete pub;
}