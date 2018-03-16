#include <ros/ros.h>
#include <control_msgs/FollowJointTrajectoryActionGoal.h>
#include <actionlib_msgs/GoalID.h>
#include <bekci/SpaceSafetyStatus.h>

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <stdlib.h>


using namespace std;

actionlib_msgs::GoalID current_goal;

int current_space_status;

void spaceCallback(const bekci::SpaceSafetyStatus & in_msg) {
    current_space_status = in_msg.state;
}


void goalIDKeeper(const control_msgs::FollowJointTrajectoryActionGoal & msg) {
    current_goal.id = msg.goal_id.id;
}

int main(int argc,char** argv) {
    ros::init(argc, argv, "quantative_limiter");
    ros::NodeHandle nh;
 
}