#include <ros/ros.h>
#include <control_msgs/FollowJointTrajectoryActionGoal.h>
#include <actionlib_msgs/GoalID.h>
#include <bekci/Action.h>

#include <iostream>
#include <map>
#include <string>
#include <vector>



using namespace std;
actionlib_msgs::GoalID current_goal;
ros::Publisher* pub;

void goalIDKeeper(const control_msgs::FollowJointTrajectoryActionGoal & msg) {
    current_goal.id = msg.goal_id.id;
}

void robotActionCallback(const bekci::Action & in_msg) {
    if(in_msg.action == 2) {
        actionlib_msgs::GoalID cancel;
        pub->publish(cancel);
    }
}
int main(int argc,char** argv) {
    ros::init(argc, argv, "StopAction");
    ros::NodeHandle nh;
    
    ros::Subscriber act_sub = nh.subscribe("/robot_action",100,robotActionCallback);

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