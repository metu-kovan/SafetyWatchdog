cmake_minimum_required(VERSION 2.8.3)
project(bekci)

## Compile as C++11, supported in ROS Kinetic and newer


## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS genmsg std_msgs message_generation sensor_msgs control_msgs  roscpp rospack roslib geometric_shapes)
#rosbuild_add_boost_directories()
## System dependencies are found with CMake's conventions
find_package(Boost REQUIRED COMPONENTS system )
add_compile_options(-std=c++11)
add_message_files(FILES SpaceSafetyStatus.msg JointValue.msg JointPose.msg Pose.msg )
generate_messages(DEPENDENCIES std_msgs)





###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
 include
 ${catkin_INCLUDE_DIRS}
 ${Boost_INCLUDE_DIRS}
)

add_library(pugi include/pugi/pugixml.cpp)

catkin_package(
	
	CATKIN_DEPENDS roscpp std_msgs actionlib_msgs control_msgs actionlib message_runtime
   	
    INCLUDE_DIRS include
    LIBRARIES pugi
)

add_executable(QuantativeController QuantativeController.cpp)
add_executable(RobotJointAngle RobotJointAngle.cpp)
add_executable(SpaceController SpaceController.cpp include/Point.cpp include/Sphere.cpp include/Vec3d.cpp include/Plane.cpp)
add_executable(SafetyStatusDecider SafetyStatusDecider.cpp)
add_executable(ForwardCalculator ForwardCalculator.cpp)
add_executable(RobotJointVelocity RobotJointVelocity.cpp)

link_directories(${catkin_LIBRARY_DIRS})
target_link_libraries(QuantativeController ${catkin_LIBRARIES} ${boost_LIBRARIES})
target_link_libraries(RobotJointAngle ${catkin_LIBRARIES})
target_link_libraries(SpaceController ${catkin_LIBRARIES} ${boost_LIBRARIES} pugi)
target_link_libraries(RobotJointVelocity ${catkin_LIBRARIES})
target_link_libraries(SafetyStatusDecider ${catkin_LIBRARIES} ${boost_LIBRARIES})
target_link_libraries(ForwardCalculator ${catkin_LIBRARIES})
## Declare a C++ library
# add_library(${PROJECT_NAME}
#   src/${PROJECT_NAME}/bekci.cpp
# )

## Add cmake target dependencies of the library
## as an example, code may need to be generated before libraries
## either from message generation or dynamic reconfigure
# add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Declare a C++ executable
## With catkin_make all packages are built within a single CMake context
## The recommended prefix ensures that target names across packages don't collide
# add_executable(${PROJECT_NAME}_node src/bekci_node.cpp)

## Rename C++ executable without prefix
## The above recommended prefix causes long target names, the following renames the
## target back to the shorter version for ease of user use
## e.g. "rosrun someones_pkg node" instead of "rosrun someones_pkg someones_pkg_node"
# set_target_properties(${PROJECT_NAME}_node PROPERTIES OUTPUT_NAME node PREFIX "")

## Add cmake target dependencies of the executable
## same as for the library above
# add_dependencies(${PROJECT_NAME}_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
# target_link_libraries(${PROJECT_NAME}_node
#   ${catkin_LIBRARIES}
# )

#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# install(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark executables and/or libraries for installation
# install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}_node
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark cpp header files for installation
# install(DIRECTORY include/${PROJECT_NAME}/
#   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#   FILES_MATCHING PATTERN "*.h"
#   PATTERN ".svn" EXCLUDE
# )

## Mark other files for installation (e.g. launch and bag files, etc.)
# install(FILES
#   # myfile1
#   # myfile2
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
# )

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_bekci.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)
