// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GENERAL DESCRIPTION


// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// HEADERS 
#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

#include <bekci/SpaceSafetyStatus.h>
#include <bekci/Action.h>

#include <pugi/pugixml.hpp>
// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GLOBAL VARIABLE DECLARATIONS
int zone 	= -1;
int action 	= -1;

// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SUBSCRIBER CALLBACKS
// description
void actionTracker(const bekci::Action& currentAction)
{
	action = currentAction.action;
}

// description
void zoneTracker(const bekci::SpaceSafetyStatus& currentZone)
{
	zone = currentZone.zone;
}


// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNCTION DECLARATIONS
// description
// void function1(void){}

// description
// void function1(void){}



// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{	
	// Variable Declarations    /////////////////////////////////////////////////////////////////////////////////////////////////
    visualization_msgs::Marker marker;
	int boundType		{-1}; 	// 0 is for human only space; 1 is for shared space 
	std::string markerLabel("");
	std::string textDisplay("");
	
	// Initializations     //////////////////////////////////////////////////////////////////////////////////////////////////////
	ros::init(argc, argv, "visualizer");
	ros::NodeHandle nh;
	ros::Rate rate(10);

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(argv[1]);

	// Set the frame ID and timestamp.  See the TF tutorials for information on these.
    // marker.header.frame_id = "/world"; 	// CONSIDER getting the actual frame id through /tf
    marker.header.frame_id = "/base"; 	// CONSIDER getting the actual frame id through /tf
    marker.header.stamp = ros::Time::now();
	// Set the namespace and id for this marker.  This serves to create a unique ID
	// Any marker sent with the same namespace and id will overwrite the old one
	marker.ns = "default";
	marker.id = 0;
	// Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
	marker.type = visualization_msgs::Marker::CUBE;
	// Set the scale of the marker -- 1x1x1 here means 1m on a side
	// the normal of the default plane is <0,0,1>
	marker.scale.x = 2.0;
	marker.scale.y = 2.0;
	marker.scale.z = 2.0;
	// Set the color -- be sure to set alpha to something non-zero! Initialized as RED
	marker.color.r = 1.0f;
	marker.color.g = 0.0f;
	marker.color.b = 0.0f;
	marker.color.a = 0.5;
	// Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    marker.pose.position.x = 0;
    marker.pose.position.y = 0;
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;
	// Set the lifetime
	marker.lifetime = ros::Duration();
	
	// Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
	// marker.action = visualization_msgs::Marker::DELETEALL;
	// pubMarker.publish(marker);
	// CONSIDER deleting all before spawning anything
	marker.action = visualization_msgs::Marker::ADD;

	// Subscriber/publisher Declarations   //////////////////////////////////////////////////////////////////////////////////////
	ros::Publisher pubMarker = nh.advertise<visualization_msgs::Marker>("/visualization_marker", 100); // DO NOT use
	// the relative name for the marker (visualization_marker) but the global name /visualization_marker for this
	// with the slash is the default name for the RVIZ 
	ros::Subscriber subsAction 	= nh.subscribe("/robot_action"	,1000,actionTracker);
    ros::Subscriber subsZone 	= nh.subscribe("/space_safety"	,1000,zoneTracker);
            





	// Wait for a subscriber to the /visualization_marker topic. The subscriber is to be the RVIZ in this case  /////////////////////
	while (pubMarker.getNumSubscribers() < 1)
	{
		if (!ros::ok())
		{
			return 0;
		}
			ROS_WARN_STREAM("Please create a subscriber to the marker");
		rate.sleep();
	}
	ROS_INFO_STREAM("Marker subscriber detected");


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Roll on
	// char dummy {' '};
	// Get the planes/boxes of the watchdog from the .xml input file  ///////////////////////////////////////////////////////////////
	markerLabel.clear();
	for (pugi::xml_node box = doc.child("Boxes").child("Box"); box; box = box.next_sibling("Box"))
	{
		// start constructing the label
		markerLabel.append(box.attribute("id").as_string());

		// set the color to red or yellow
		boundType = box.attribute("Shared").as_bool();
		if(boundType == 1)	marker.color.g = 1.0f;
		else				marker.color.g = 0.0f;
		
		for(pugi::xml_node plane = box.child("Plane"); plane; plane = plane.next_sibling("Plane") ) 
		{
			
			// complete constructing the label
			markerLabel.append(plane.attribute("id").as_string());
			marker.ns = markerLabel;
			
			marker.pose.position.x = plane.child("Point").attribute("x").as_double();
			marker.pose.position.y = plane.child("Point").attribute("y").as_double();
			marker.pose.position.z = plane.child("Point").attribute("z").as_double();
			
			if(plane.child("Normal").attribute("x").as_double()!=0)
			{
				// marker.pose.orientation.x = 0.0;
			 //    marker.pose.orientation.y = 0.0;
			 //    marker.pose.orientation.z = 0.707;
			 //    marker.pose.orientation.w = 0.707;
				marker.scale.x = 0.01;


			    // ROS_INFO_STREAM("section1");
			}
			else if(plane.child("Normal").attribute("y").as_double()!=0)
			{
				// marker.pose.orientation.x = 0.707;
			 //    marker.pose.orientation.y = 0.0;
			 //    marker.pose.orientation.z = 0.0;
			 //    marker.pose.orientation.w = 0.707;
				marker.scale.y = 0.01;
			    // ROS_INFO_STREAM("section2");
			}
			else if(plane.child("Normal").attribute("z").as_double()!=0)
			{
				// marker.pose.orientation.x = 0.0;
			 //    marker.pose.orientation.y = 0.707;
			 //    marker.pose.orientation.z = 0.0;
			 //    marker.pose.orientation.w = 0.707;
			    marker.scale.z = 0.01;
			    // ROS_INFO_STREAM("section3");
			}
			// n_x = plane.child("Normal").attribute("x").as_double();
			// n_y = plane.child("Normal").attribute("y").as_double();
			// n_z = plane.child("Normal").attribute("z").as_double();

			// ROS_INFO_STREAM(boundType<<":"<<marker.ns<<":"<<marker.pose.position.x<<":"<<marker.pose.position.y<<":"<<marker.pose.position.z);

			pubMarker.publish(marker);

			// std::cin>>dummy;

			// marker.action = visualization_msgs::Marker::DELETE;
			// pubMarker.publish(marker);
			// sleep(1);
			// marker.action = visualization_msgs::Marker::ADD;

			markerLabel.pop_back();
			marker.scale.x = 2.0;
			marker.scale.y = 2.0;
			marker.scale.z = 2.0;
		}
		markerLabel.clear();
	}

	// Spawn planes/boxes as specified in the input file ////////////////////////////////////////////////////////////////////////////

	// while(ros::ok()) keep refreshing the action text display on the screen  //////////////////////////////////////////////////////
	
	marker.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
	marker.text = "default text";
	marker.ns = "safetyStatusDisplay";
	marker.scale.x = 0.1;
	marker.scale.y = 0.1;
	marker.scale.z = 0.1;
	// Set the color -- be sure to set alpha to something non-zero! Initialized as RED
	marker.color.r = 1.0f;
	marker.color.g = 1.0f;
	marker.color.b = 1.0f;
	marker.color.a = 1.0;
	marker.pose.position.x = 0;
    marker.pose.position.y = 0;
    marker.pose.position.z = 1;

  while (ros::ok())
  {
  	textDisplay = "Zone\t : ";
  	switch(zone)
	{
		case 0:
  			textDisplay.append("Free");
		break;
		
		case 1:
  			textDisplay.append("Shared");
		break;

		case 2:
  			textDisplay.append("Red");
		break;
		default:
			textDisplay.append("Unknown");
		break;
	}

  	textDisplay.append("\nAction\t: ");
  	switch(action)
	{
		case 0:
  			textDisplay.append("Idle");
			break;
		case 1:
  			textDisplay.append("Slow Down");
			break;
		case 2:
  			textDisplay.append("Halt");
			break;
		case 3:
  			textDisplay.append("Speed up");
			break;
		default:
			textDisplay.append("Unknown");
			break;
	}

  	marker.text = textDisplay;
  	// ROS_INFO_STREAM(zone<<" "<<action);

	pubMarker.publish(marker);
	ros::spinOnce();
    rate.sleep();
  }

	ros::shutdown();
	return 0;
}