#include <ros/ros.h>
#include <control_msgs/FollowJointTrajectoryActionGoal.h>
#include <sensor_msgs/JointState.h>

#include <bekci/Action.h>
#include <actionlib_msgs/GoalID.h>

// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GLOBAL VARIABLE DECLARATIONS
ros::Publisher* pubGoal;

control_msgs::FollowJointTrajectoryActionGoal 	goalCurrent;	// Plan submitted by the experimental code
control_msgs::FollowJointTrajectoryActionGoal 	goalWatchDog;	// Manipulated experimental plan. WD: WatchDog
control_msgs::FollowJointTrajectoryActionGoal 	goalStorage;	// Stored plan for re-execution of the previous plan.

actionlib_msgs::GoalID 							cancelMsg;		// Cancel message to be published to cancel the currently active plan

sensor_msgs::JointState							robotJointState;		// Robot joint state register

unsigned int 									trajectoryLength {0};	// Length of the current plan in scope: goalCurrent

double  										speedDivisor {5.0};

unsigned int 									actionRequest {0};
const unsigned int 								slowDown	{1};
const unsigned int 								speedUp		{3};
const std::string watchDogSuffix("_WD");

char dummy {' '};

// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SUBSCRIBER CALLBACKS
// description
void actionTracker(const bekci::Action& currentAction)
{
	actionRequest = currentAction.action;
}
// description
void goalTracker(const control_msgs::FollowJointTrajectoryActionGoal& goalMsg) 
{
	goalCurrent = goalMsg;		// Register the incoming plan into the global varible.
	trajectoryLength = goalCurrent.goal.trajectory.points.size(); // Register the size of the plan.
}
// description
void JSTracker(const sensor_msgs::JointState& confMsg) 
{
	std::string dummyNam("");
	double dummyPos {0};
	double dummyVel {0};
	double dummyEff {0};

	robotJointState	= confMsg;		// NORMALLY this line is all this CB is supposed to do but
	// simulation and actual robots publish the joint states in different orders
	// in simulation it is 	0 1 2 3 4 5
	// in real it is 		2 1 0 3 4 5
	if(robotJointState.name[0].compare("elbow_joint") != 0)
	{
		dummyNam = robotJointState.name[0];
		dummyPos = robotJointState.position[0];
		dummyVel = robotJointState.velocity[0];
		dummyEff = robotJointState.effort[0];

		robotJointState.name[0]		= robotJointState.name[2];
		robotJointState.position[0] = robotJointState.position[2];
		robotJointState.velocity[0] = robotJointState.velocity[2];
		robotJointState.effort[0] 	= robotJointState.effort[2];

		robotJointState.name[2]		= dummyNam;
		robotJointState.position[2] = dummyPos;
		robotJointState.velocity[2] = dummyVel;
		robotJointState.effort[2] 	= dummyEff;
	}
	// cout<<robotJointState.position.size()<<"\t";
}

// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNCTION DECLARATIONS
int findConfIndex(control_msgs::FollowJointTrajectoryActionGoal plan, sensor_msgs::JointState jointState)
{
	//////////////////////////////////////////////////////////////////////////////////
	// find the index of the traj. point in the cancelled plan to the current ////////
	// robot configuration ///////////////////////////////////////////////////////////
	auto 	deviations = jointState.position;	// register to keep deviations between two 6DOF configurations
	double  minDev = 1000000;		// minimum of total deviations in 6 degrees stored in this using square root of sums of all 6 deviations
	double  tmpDev = 0;				// a temporary register for the deviation power
	int  	indDev = -1;			// index of the minimum deviation in the current plan

	// cout<<"deviations from the current robot configuration to the trajectory points: "<<"\n";
	int counter = 0;
	for(auto i:plan.goal.trajectory.points)
	{
		for(auto j=0; j<6; j++)		// calculate the power of j DoF deviations of the ith trajectory point from the current robot configuration
		{
			deviations[j] = jointState.position[j] - i.positions[j];
		}
		
		tmpDev = 0;		// reset the temporary deviation power register
		for(int j=0; j<6; j++)	// sum the squres of the deviations in the 6 degrees...
		{
			tmpDev = tmpDev+deviations[j]*deviations[j];
		}
		tmpDev = sqrt(tmpDev);	// ...and square root them to find the power

		// cout<<" Deviation power: "<<tmpDev<<"\n";
		if(tmpDev<=minDev)
		{
			if(tmpDev == minDev)ROS_WARN_STREAM("SAME DEVIATION POWER!! POSSIBLE ERRORS IN PLAN CHOPPING!!");
			minDev = tmpDev;
			indDev = counter;
		}
		counter++;
	}
	ROS_INFO_STREAM("Index for minimum deviation:  "<<indDev);
	return indDev;
}

void planRefurbisherV2(control_msgs::FollowJointTrajectoryActionGoal& targetPlan, bool slowDown)
{
    ros::Rate rate(100);									// initialize the rate (for sleep())

	int devIndex = findConfIndex(goalStorage, robotJointState);
	
	////////////////////////////////////////////////////////////////////////////////////
	// generate a new slowed plan(goalWatchDog) based on the original plan (goalCurrent)
	targetPlan = goalStorage;	// copy the plan into the new WatchDogged plan
	
	for(int i=0;i<devIndex-1;i++) 	// crop the beginning of the plan up to the minimum deviation point (current configuration)
	{								// BUT KEEP THE FIRST POINT TO BE REPLACED BY THE CURRENT POSE (AT THE MOMENT OF STOPPAGE) OF THE ROBOT
		targetPlan.goal.trajectory.points.erase(targetPlan.goal.trajectory.points.begin());
	}

	auto 	initialTime = targetPlan.goal.trajectory.points[0].time_from_start;	// the time offset induced after chopping the plan.
	double 	time 		= 0.0; //1.23456789=seconds+nanoSeconds.e-9

	for(int i=0; i<targetPlan.goal.trajectory.points.size(); i++)	// for each trajectory point...
	{
		targetPlan.goal.trajectory.points[i].time_from_start 		// ...remove the time offset...
			= (targetPlan.goal.trajectory.points[i].time_from_start-initialTime);
		
		if (slowDown)
		{
			// ROS_WARN_STREAM("YOURE HERE");
			time = double(targetPlan.goal.trajectory.points[i].time_from_start.sec) // ...register time in a double as a buffer for multiplication/division...
				+ double(targetPlan.goal.trajectory.points[i].time_from_start.nsec/double(1000000000));

			time = time*speedDivisor; 	// ...rescale the time using the divisor...

			targetPlan.goal.trajectory.points[i].time_from_start.sec = int(floor(time));
			targetPlan.goal.trajectory.points[i].time_from_start.nsec = (time-floor(time))*1000000000;

			for(int j=0;j<targetPlan.goal.trajectory.points[i].velocities.size();j++)	// ...rescale speed and accelerations...
			{
				targetPlan.goal.trajectory.points[i].velocities[j] 	= targetPlan.goal.trajectory.points[i].velocities[j]/speedDivisor;
				targetPlan.goal.trajectory.points[i].accelerations[j] = targetPlan.goal.trajectory.points[i].accelerations[j]/speedDivisor;
			}
		}
		
	}

	ros::spinOnce();
	sleep(1);
	ros::spinOnce();

	// ...set initial speed and acceleration exceptions to current state...
	targetPlan.goal.trajectory.points[0].positions = (robotJointState.position);
	targetPlan.goal.trajectory.points[0].velocities = (robotJointState.velocity);

	if (slowDown)
	{
		targetPlan.goal_id.id.append(watchDogSuffix);		// ...and finally append the _WD suffix to the ID of the new plan
	}
	else
	{
		targetPlan.goal_id.id.append("_wd");		// ...and finally append the _WD suffix to the ID of the new plan
	}

	ROS_WARN_STREAM("first pose in watchdog plan: " 
		<< targetPlan.goal.trajectory.points[0].positions[0]<<"**"
		<< targetPlan.goal.trajectory.points[0].positions[1]<<"**"
		<< targetPlan.goal.trajectory.points[0].positions[2]<<"**"
		<< targetPlan.goal.trajectory.points[0].positions[3]<<"**"
		<< targetPlan.goal.trajectory.points[0].positions[4]<<"**"
		<< targetPlan.goal.trajectory.points[0].positions[5]);
	ROS_WARN_STREAM("current robot pose : " 
		<< robotJointState.position[0]<<"**"
		<< robotJointState.position[1]<<"**"
		<< robotJointState.position[2]<<"**"
		<< robotJointState.position[3]<<"**"
		<< robotJointState.position[4]<<"**"
		<< robotJointState.position[5]<<"**");
}  


void planRefurbisher(void)
{
    ros::Rate rate(100);									// initialize the rate (for sleep())

    int devIndex {-1};

	// while(ros::ok() && robotJointState.position.size()!=6) 	// poll for the first valid subscription
	// {
	// 	ros::spinOnce();
	// 	rate.sleep();
	// }

	devIndex = findConfIndex(goalStorage, robotJointState);
	
	////////////////////////////////////////////////////////////////////////////////////
	// generate a new slowed plan(goalWatchDog) based on the original plan (goalCurrent)
	goalWatchDog = goalStorage;	// copy the plan into the new WatchDogged plan
	
	for(int i=0;i<devIndex-1;i++) 	// crop the beginning of the plan up to the minimum deviation point (current configuration)
	{								// BUT KEEP THE FIRST POINT TO BE REPLACED BY THE CURRENT POSE (AT THE MOMENT OF STOPPAGE) OF THE ROBOT
		goalWatchDog.goal.trajectory.points.erase(goalWatchDog.goal.trajectory.points.begin());
	}

	auto 	initialTime = goalWatchDog.goal.trajectory.points[0].time_from_start;	// the time offset induced after chopping the plan.
	double 	time 		= 0.0; //1.23456789=seconds+nanoSeconds.e-9

	for(int i=0; i<goalWatchDog.goal.trajectory.points.size(); i++)	// for each trajectory point...
	{
		goalWatchDog.goal.trajectory.points[i].time_from_start 		// ...remove the time offset...
			= (goalWatchDog.goal.trajectory.points[i].time_from_start-initialTime);

		time = double(goalWatchDog.goal.trajectory.points[i].time_from_start.sec) // ...register time in a double as a buffer for multiplication/division...
			+ double(goalWatchDog.goal.trajectory.points[i].time_from_start.nsec/double(1000000000));
		
		time = time*speedDivisor; 	// ...rescale the time using the divisor...
		
		goalWatchDog.goal.trajectory.points[i].time_from_start.sec = int(floor(time));
		goalWatchDog.goal.trajectory.points[i].time_from_start.nsec = (time-floor(time))*1000000000;
		
		for(int j=0;j<goalWatchDog.goal.trajectory.points[i].velocities.size();j++)	// ...rescale speed and accelerations...
		{
			goalWatchDog.goal.trajectory.points[i].velocities[j] 	= goalWatchDog.goal.trajectory.points[i].velocities[j]/speedDivisor;
			goalWatchDog.goal.trajectory.points[i].accelerations[j] = goalWatchDog.goal.trajectory.points[i].accelerations[j]/speedDivisor;
		}
	}

	ros::spinOnce();
	sleep(1);
	ros::spinOnce();

	// ...set initial speed and acceleration exceptions to current state...
	goalWatchDog.goal.trajectory.points[0].positions = (robotJointState.position);
	goalWatchDog.goal.trajectory.points[0].velocities = (robotJointState.velocity);

	goalWatchDog.goal_id.id.append(watchDogSuffix);		// ...and finally append the _WD suffix to the ID of the new plan

	ROS_WARN_STREAM("first pose in watchdog plan: " 
		<< goalWatchDog.goal.trajectory.points[0].positions[0]<<"**"
		<< goalWatchDog.goal.trajectory.points[0].positions[1]<<"**"
		<< goalWatchDog.goal.trajectory.points[0].positions[2]<<"**"
		<< goalWatchDog.goal.trajectory.points[0].positions[3]<<"**"
		<< goalWatchDog.goal.trajectory.points[0].positions[4]<<"**"
		<< goalWatchDog.goal.trajectory.points[0].positions[5]);
	ROS_WARN_STREAM("current robot pose : " 
		<< robotJointState.position[0]<<"**"
		<< robotJointState.position[1]<<"**"
		<< robotJointState.position[2]<<"**"
		<< robotJointState.position[3]<<"**"
		<< robotJointState.position[4]<<"**"
		<< robotJointState.position[5]<<"**");
}  

void displayPlan(control_msgs::FollowJointTrajectoryActionGoal plan)
{
	std::cout<<"ID:"<<plan.goal_id.id<<"\n";

	for(int i =0; i<plan.goal.trajectory.points.size();i++)
	{
		std::cout<<std::setw(3)<<i<<": ";
		for(int j = 0; j<plan.goal.trajectory.points[i].positions.size(); j++)
		{
			std::cout<<std::setw(8)<<plan.goal.trajectory.points[i].positions[j]<<" ";
		}
		std::cout<<"\n";
	}
}
// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
	// Initializations
	ros::init(argc, argv, "velocityScaler");	// initialize the node
	ros::NodeHandle nh;							// node handled by the handle 'nh'
    ros::Rate rate(100);						// initialize the rate (for sleep())
	// ros::AsyncSpinner spinner(1);				// initialize asyncronous spinner
	
	// Variable Declarations
    // int index {-1};

	// Subscriber/publisher Declarations
	ros::Subscriber subsAction	= nh.subscribe("/robot_action",1,actionTracker);		// Subscribe to the commanding topic of the watchdog
	ros::Subscriber subJS 	= nh.subscribe("/joint_states", 1, &JSTracker);
	ros::Subscriber subsGoal;
	ros::Publisher pubCancel;
	ros::Publisher pubNewGoal;

	if (std::string(argv[1]).compare(std::string("sim"))==0)		// If the environment is tagged as 'simulation' in the launch file...
    {
        subsGoal 	= nh.subscribe("/arm_controller/follow_joint_trajectory/goal",1000,goalTracker);
        pubGoal 	= new ros::Publisher(nh.advertise<actionlib_msgs::GoalID>("/arm_controller/follow_joint_trajectory/cancel",10));
        pubCancel	= nh.advertise<actionlib_msgs::GoalID>("/arm_controller/follow_joint_trajectory/cancel",1);
        pubNewGoal	= nh.advertise<control_msgs::FollowJointTrajectoryActionGoal>("/arm_controller/follow_joint_trajectory/goal",10);
    } 
    else if (std::string(argv[1]).compare(std::string("real"))==0)	// ...else if it is tagged as 'simulation' in the launch file...
    {
    	subsGoal 	= nh.subscribe("/follow_joint_trajectory/goal",1000,goalTracker);
        pubGoal 	= new ros::Publisher(nh.advertise<actionlib_msgs::GoalID>("/follow_joint_trajectory/cancel",10));
        pubCancel	= nh.advertise<actionlib_msgs::GoalID>("/follow_joint_trajectory/cancel",1);
        pubNewGoal	= nh.advertise<control_msgs::FollowJointTrajectoryActionGoal>("/follow_joint_trajectory/goal",10);
    }
    else													// ...if something else return error.
    {
    	ROS_FATAL_STREAM("Cannot decide if the environment is real or simulated!");
    	return 0;
    }
	

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Roll on
	// spinner.start();							//
	while(ros::ok() && robotJointState.position.size()!=6) 	// poll for the first valid subscription
	{
		ros::spinOnce();
		rate.sleep();
	}

	while(ros::ok())
	{
		switch(actionRequest)
	    {
	      case slowDown:	// if a slowDown request arrives and...
	      	
	      	if((goalStorage.goal_id.id + watchDogSuffix).compare(goalCurrent.goal_id.id) != 0) //...if the current goal is not the slowed down plan...
			{	
				ROS_WARN_STREAM("Slowing down");		// ...then slow down the plan.
				ros::spinOnce();

				goalStorage 	= goalCurrent;	// Store the plan to be slowed down
				
				// ROS_WARN_STREAM("Slowing down");		// ...then slow down.
				// ROS_WARN_STREAM(goalStorage.goal_id.id + watchDogSuffix);
				// ROS_WARN_STREAM(goalCurrent.goal_id.id);

				cancelMsg.id = goalStorage.goal_id.id;
	    		pubCancel.publish(cancelMsg);
	    		ros::spinOnce();
	    		
				// planRefurbisher(); 				// Refurbish the currently stored plan (goalStorage)
				planRefurbisherV2(goalWatchDog,1);

				// displayPlan(goalStorage);
				// displayPlan(goalWatchDog);

				// ROS_WARN_STREAM("waiting for trigger to publish slowed plan");
				// std::cin >> dummy;

				pubNewGoal.publish(goalWatchDog);
			}
			else
			{
				// ROS_ERROR_STREAM("Cannot slow down the plan");
			}
	        break;

	      case speedUp:

	      	displayPlan(goalStorage);
			displayPlan(goalCurrent);
	      	sleep(1);
	      	if((goalStorage.goal_id.id + watchDogSuffix).compare(goalCurrent.goal_id.id) == 0) //...if the current goal IS the slowed down plan...
			{	
				ROS_WARN_STREAM("Speeding up");		// ...then slow down the plan.
				ros::spinOnce();

				// index = findConfIndex(goalStorage, robotJointState);

				// goalStorage 	= goalCurrent;	// Store the plan to be slowed down
				
				// ROS_WARN_STREAM("Slowing down");		// ...then slow down.
				// ROS_WARN_STREAM(goalStorage.goal_id.id + watchDogSuffix);
				// ROS_WARN_STREAM(goalCurrent.goal_id.id);

				cancelMsg.id = goalCurrent.goal_id.id;
	    		pubCancel.publish(cancelMsg);
	    		ros::spinOnce();

				// displayPlan(goalStorage);
				planRefurbisherV2(goalStorage,0); 				// Refurbish the currently stored plan (goalStorage)
				// displayPlan(goalStorage);

				// displayPlan(goalStorage);
				// displayPlan(goalWatchDog);

				// ROS_WARN_STREAM("waiting for trigger to publish slowed plan");
				// std::cin >> dummy;

				pubNewGoal.publish(goalStorage);
				// sleep(1);

				// pubNewGoal.publish(goalStorage);
				// std::cin;
				// pubNewGoal.publish(goalStorage);
			}
			else
			{
				// ROS_ERROR_STREAM("Cannot speed up the plan");
			}
	        break;

	      default:
	        
	        break;
	    }
		ros::spinOnce();
	    rate.sleep();
	}

	// spinner.stop();
	ros::shutdown();
	return 0;
}