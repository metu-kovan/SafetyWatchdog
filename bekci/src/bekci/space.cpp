#include <ros/ros.h>
#include <iostream>
#include <map>
#include <string>
#include <sensor_msgs/JointState.h>
#include <fstream>
#include <vector>
#include <ros/package.h>
#include <boost/algorithm/string.hpp>
#include <control_msgs/FollowJointTrajectoryActionGoal.h>
#include <actionlib_msgs/GoalID.h>
#include <stdlib.h>
using namespace std;
struct pose
{
    double x;
    double y;
    double z;
};


//#define UR5_PARAMS

const double d1 =  0.089159;
const double a2 = -0.42500;
const double a3 = -0.39225;
const double d4 =  0.10915;
const double d5 =  0.09465;
const double d6 =  0.0823;

double* T1 ;
double* T2 ;
double* T3 ;
double* T4 ;
double* T5 ;
double* T6 ;
double* Tend ;

bool fault = false;
ros::Publisher* pub; 
map<string,float> ordered_q;
string current_goal;
struct pose max_pose;
struct pose min_pose;
vector<pose> holder;
/*a smaller than b*/
int smaller(pose & a,pose & b) {
    if(a.x<=b.x && a.y<=b.y && a.z<=b.z)
        return 1;
    return 0;
}
/*a larger than b*/
int larger(pose & a,pose & b) {
    if(a.x>=b.x && a.y>=b.y && a.z>=b.z)
        return 1;
    return 0;
}
void pose_print(pose & a) {
    ROS_INFO_STREAM("x:"<<a.x<<" y:"<<a.y<<" z:"<<a.z);
}


void forward(const double* q, double* T) {
    double s1 = sin(*q), c1 = cos(*q); q++;
    double q234 = *q, s2 = sin(*q), c2 = cos(*q); q++;
    double s3 = sin(*q), c3 = cos(*q); q234 += *q; q++;
    q234 += *q; q++;
    double s5 = sin(*q), c5 = cos(*q); q++;
    double s6 = sin(*q), c6 = cos(*q); 
    double s234 = sin(q234), c234 = cos(q234);
    *T = ((c1*c234-s1*s234)*s5)/2.0 - c5*s1 + ((c1*c234+s1*s234)*s5)/2.0; T++;
    *T = (c6*(s1*s5 + ((c1*c234-s1*s234)*c5)/2.0 + ((c1*c234+s1*s234)*c5)/2.0) - 
          (s6*((s1*c234+c1*s234) - (s1*c234-c1*s234)))/2.0); T++;
    *T = (-(c6*((s1*c234+c1*s234) - (s1*c234-c1*s234)))/2.0 - 
          s6*(s1*s5 + ((c1*c234-s1*s234)*c5)/2.0 + ((c1*c234+s1*s234)*c5)/2.0)); T++;
    *T = ((d5*(s1*c234-c1*s234))/2.0 - (d5*(s1*c234+c1*s234))/2.0 - 
          d4*s1 + (d6*(c1*c234-s1*s234)*s5)/2.0 + (d6*(c1*c234+s1*s234)*s5)/2.0 - 
          a2*c1*c2 - d6*c5*s1 - a3*c1*c2*c3 + a3*c1*s2*s3); T++;
    *T = c1*c5 + ((s1*c234+c1*s234)*s5)/2.0 + ((s1*c234-c1*s234)*s5)/2.0; T++;
    *T = (c6*(((s1*c234+c1*s234)*c5)/2.0 - c1*s5 + ((s1*c234-c1*s234)*c5)/2.0) + 
          s6*((c1*c234-s1*s234)/2.0 - (c1*c234+s1*s234)/2.0)); T++;
    *T = (c6*((c1*c234-s1*s234)/2.0 - (c1*c234+s1*s234)/2.0) - 
          s6*(((s1*c234+c1*s234)*c5)/2.0 - c1*s5 + ((s1*c234-c1*s234)*c5)/2.0)); T++;
    *T = ((d5*(c1*c234-s1*s234))/2.0 - (d5*(c1*c234+s1*s234))/2.0 + d4*c1 + 
          (d6*(s1*c234+c1*s234)*s5)/2.0 + (d6*(s1*c234-c1*s234)*s5)/2.0 + d6*c1*c5 - 
          a2*c2*s1 - a3*c2*c3*s1 + a3*s1*s2*s3); T++;
    *T = ((c234*c5-s234*s5)/2.0 - (c234*c5+s234*s5)/2.0); T++;
    *T = ((s234*c6-c234*s6)/2.0 - (s234*c6+c234*s6)/2.0 - s234*c5*c6); T++;
    *T = (s234*c5*s6 - (c234*c6+s234*s6)/2.0 - (c234*c6-s234*s6)/2.0); T++;
    *T = (d1 + (d6*(c234*c5-s234*s5))/2.0 + a3*(s2*c3+c2*s3) + a2*s2 - 
         (d6*(c234*c5+s234*s5))/2.0 - d5*c234); T++;
    *T = 0.0; T++; *T = 0.0; T++; *T = 0.0; T++; *T = 1.0;
}

void forward_all(const double* q, double* T1, double* T2, double* T3, 
                                    double* T4, double* T5, double* T6) {
    double s1 = sin(*q), c1 = cos(*q); q++; // q1
    double q23 = *q, q234 = *q, s2 = sin(*q), c2 = cos(*q); q++; // q2
    double s3 = sin(*q), c3 = cos(*q); q23 += *q; q234 += *q; q++; // q3
    q234 += *q; q++; // q4
    double s5 = sin(*q), c5 = cos(*q); q++; // q5
    double s6 = sin(*q), c6 = cos(*q); // q6
    double s23 = sin(q23), c23 = cos(q23);
    double s234 = sin(q234), c234 = cos(q234);

    if(T1 != NULL) {
      *T1 = c1; T1++;
      *T1 = 0; T1++;
      *T1 = s1; T1++;
      *T1 = 0; T1++;
      *T1 = s1; T1++;
      *T1 = 0; T1++;
      *T1 = -c1; T1++;
      *T1 = 0; T1++;
      *T1 =       0; T1++;
      *T1 = 1; T1++;
      *T1 = 0; T1++;
      *T1 =d1; T1++;
      *T1 =       0; T1++;
      *T1 = 0; T1++;
      *T1 = 0; T1++;
      *T1 = 1; T1++;
    }

    if(T2 != NULL) {
      *T2 = c1*c2; T2++;
      *T2 = -c1*s2; T2++;
      *T2 = s1; T2++;
      *T2 =a2*c1*c2; T2++;
      *T2 = c2*s1; T2++;
      *T2 = -s1*s2; T2++;
      *T2 = -c1; T2++;
      *T2 =a2*c2*s1; T2++;
      *T2 =         s2; T2++;
      *T2 = c2; T2++;
      *T2 = 0; T2++;
      *T2 =   d1 + a2*s2; T2++;
      *T2 =               0; T2++;
      *T2 = 0; T2++;
      *T2 = 0; T2++;
      *T2 =                 1; T2++;
    }

    if(T3 != NULL) {
      *T3 = c23*c1; T3++;
      *T3 = -s23*c1; T3++;
      *T3 = s1; T3++;
      *T3 =c1*(a3*c23 + a2*c2); T3++;
      *T3 = c23*s1; T3++;
      *T3 = -s23*s1; T3++;
      *T3 = -c1; T3++;
      *T3 =s1*(a3*c23 + a2*c2); T3++;
      *T3 =         s23; T3++;
      *T3 = c23; T3++;
      *T3 = 0; T3++;
      *T3 =     d1 + a3*s23 + a2*s2; T3++;
      *T3 =                    0; T3++;
      *T3 = 0; T3++;
      *T3 = 0; T3++;
      *T3 =                                     1; T3++;
    }

    if(T4 != NULL) {
      *T4 = c234*c1; T4++;
      *T4 = s1; T4++;
      *T4 = s234*c1; T4++;
      *T4 =c1*(a3*c23 + a2*c2) + d4*s1; T4++;
      *T4 = c234*s1; T4++;
      *T4 = -c1; T4++;
      *T4 = s234*s1; T4++;
      *T4 =s1*(a3*c23 + a2*c2) - d4*c1; T4++;
      *T4 =         s234; T4++;
      *T4 = 0; T4++;
      *T4 = -c234; T4++;
      *T4 =                  d1 + a3*s23 + a2*s2; T4++;
      *T4 =                         0; T4++;
      *T4 = 0; T4++;
      *T4 = 0; T4++;
      *T4 =                                                  1; T4++;
    }

    if(T5 != NULL) {
      *T5 = s1*s5 + c234*c1*c5; T5++;
      *T5 = -s234*c1; T5++;
      *T5 = c5*s1 - c234*c1*s5; T5++;
      *T5 =c1*(a3*c23 + a2*c2) + d4*s1 + d5*s234*c1; T5++;
      *T5 = c234*c5*s1 - c1*s5; T5++;
      *T5 = -s234*s1; T5++;
      *T5 = - c1*c5 - c234*s1*s5; T5++;
      *T5 =s1*(a3*c23 + a2*c2) - d4*c1 + d5*s234*s1; T5++;
      *T5 =                           s234*c5; T5++;
      *T5 = c234; T5++;
      *T5 = -s234*s5; T5++;
      *T5 =                          d1 + a3*s23 + a2*s2 - d5*c234; T5++;
      *T5 =                                                   0; T5++;
      *T5 = 0; T5++;
      *T5 = 0; T5++;
      *T5 =                                                                                 1; T5++;
    }

    if(T6 != NULL) {
      *T6 = c6*(s1*s5 + c234*c1*c5) - s234*c1*s6; T6++;
      *T6 = - s6*(s1*s5 + c234*c1*c5) - s234*c1*c6; T6++;
      *T6 = c5*s1 - c234*c1*s5; T6++;
      *T6 =d6*(c5*s1 - c234*c1*s5) + c1*(a3*c23 + a2*c2) + d4*s1 + d5*s234*c1; T6++;
      *T6 = - c6*(c1*s5 - c234*c5*s1) - s234*s1*s6; T6++;
      *T6 = s6*(c1*s5 - c234*c5*s1) - s234*c6*s1; T6++;
      *T6 = - c1*c5 - c234*s1*s5; T6++;
      *T6 =s1*(a3*c23 + a2*c2) - d4*c1 - d6*(c1*c5 + c234*s1*s5) + d5*s234*s1; T6++;
      *T6 = c234*s6 + s234*c5*c6; T6++;
      *T6 = c234*c6 - s234*c5*s6; T6++;
      *T6 = -s234*s5; T6++;
      *T6 =  d1 + a3*s23 + a2*s2 - d5*c234 - d6*s234*s5; T6++;
      *T6 = 0; T6++;
      *T6 = 0; T6++;
      *T6 = 0; T6++;
      *T6 = 1; T6++;
    }
  }

void goalIDKeeper(const control_msgs::FollowJointTrajectoryActionGoal& msg) {
    current_goal=msg.goal_id.id;
}
void receiver(const sensor_msgs::JointState & msg) {
    double q[6] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    
    actionlib_msgs::GoalID cancel;
    
    for(int i=0;i<6;i++) {
        ordered_q[msg.name[i]] = msg.position[i];
    }
    q[0] = ordered_q["shoulder_pan_joint"];
    q[1] = ordered_q["shoulder_lift_joint"];
    q[2] = ordered_q["elbow_joint"];
    q[3] = ordered_q["wrist_1_joint"];
    q[4] = ordered_q["wrist_2_joint"];
    q[5] = ordered_q["wrist_3_joint"];
    forward(q,Tend);
    forward_all(q,T1,T2,T3,T4,T5,T6);
    holder[0].x = T1[3];
    holder[0].y = T1[7];
    holder[0].z = T1[11];
    holder[1].x = T2[3];
    holder[1].y = T2[7];
    holder[1].z = T2[11];
    holder[2].x = T3[3];
    holder[2].y = T3[7];
    holder[2].z = T3[11];
    holder[3].x = T4[3];
    holder[3].y = T4[7];
    holder[3].z = T4[11];
    holder[4].x = T5[3];
    holder[4].y = T5[7];
    holder[4].z = T5[11];
    holder[5].x = T6[3];
    holder[5].y = T6[7];
    holder[5].z = T6[11];
    struct pose end_pose;
    end_pose.x = Tend[3];
    end_pose.y = Tend[7];
    end_pose.z = Tend[11];
    ROS_INFO_STREAM("endeffector ");
    pose_print(end_pose);
    ROS_INFO_STREAM("max x:"<<max_pose.x<<" y:"<<max_pose.y<<" z:"<<max_pose.z);
    ROS_INFO_STREAM("min x:"<<min_pose.x<<" y:"<<min_pose.y<<" z:"<<min_pose.z);
    for(int i=2;i<6;i++) {
        ROS_INFO_STREAM("joint "<<i);
        pose_print(holder[i]);
       //ROS_INFO_STREAM(msg.name[i]<<" limit "<<given_limits[msg.name[i]]<<" message "<<msg.velocity[i]);
        if(!larger(max_pose,holder[i])) {
            ROS_INFO_STREAM("wow1");
            cancel.id=current_goal;
            pub->publish(cancel);
            fault=true;
            break;
        }
        if(!smaller(min_pose,holder[i])) {
            ROS_INFO_STREAM("wow2");
            cancel.id=current_goal;
            pub->publish(cancel);
            fault=true;
            break;
        }
        
    }
    
    
}



int main(int argc,char** argv) {
    ros::init(argc, argv, "space_restriction");
    ros::NodeHandle nh;
    string line;
    ifstream inFile("/home/fatih/bekci/src/bekci/space_limits.txt");
    T1 = new double[16];
    T2 = new double[16];
    T3 = new double[16];
    T4 = new double[16];
    T5 = new double[16];
    T6 = new double[16];
    Tend = new double[16];
    holder.resize(6);
    string::size_type sz;
    string pack("bekci");
    ordered_q["shoulder_pan_joint"] = 0;
    ordered_q["shoulder_lift_joint"] = 0;
    ordered_q["elbow_joint"] = 0;
    ordered_q["wrist_1_joint"] = 0;
    ordered_q["wrist_2_joint"] = 0;
    ordered_q["wrist_3_joint"] = 0;
    string  a= ros::package::getPath(pack);
    ROS_INFO_STREAM(a);
    if(inFile.is_open()) {
        ROS_INFO_STREAM("1");
        while( getline(inFile,line)) {
            ROS_INFO_STREAM(line);
            vector<string> temp;
            boost::split(temp, line, boost::is_any_of("="));
            if (temp[0].compare(string("max_x"))==0) {
                max_pose.x = stof(temp[1]);
            } else if (temp[0].compare(string("max_y"))==0) {
                max_pose.y = stof(temp[1]);
            } else if (temp[0].compare(string("max_z"))==0) {
                max_pose.z = stof(temp[1]);
            } else if (temp[0].compare(string("min_x"))==0) {
                min_pose.x = stof(temp[1]);
            } else if (temp[0].compare(string("min_y"))==0) {
                min_pose.y = stof(temp[1]);
            } else if (temp[0].compare(string("min_z"))==0) {
                min_pose.z = stof(temp[1]);
            }

            
        }
        inFile.close();
    }
    ROS_INFO_STREAM("2");
    ros::Rate rate(10);

    ros::Subscriber sub_state = nh.subscribe("/joint_states", 100, &receiver);
    ros::Subscriber sub_goal = nh.subscribe("/follow_joint_trajectory/goal",1000,&goalIDKeeper);
    
    pub= new ros::Publisher(nh.advertise<actionlib_msgs::GoalID>("/follow_joint_trajectory/cancel",10));
    while(ros::ok()) {
        if(fault) {
            return 1;
        }
        ros::spinOnce();
        rate.sleep();
    }
    delete[] T1;
    delete[] T2;
    delete[] T3;
    delete[] T4;
    delete[] T5;
    delete[] T6;
    delete[] Tend;
    delete pub;
}