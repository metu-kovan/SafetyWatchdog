#include "JointLimits.h"

JointLimits::JointLimits(std::string _name, double _s_limit) {
	joint_name = _name;
	speed_limit = _s_limit;
}
void JointLimits::setValues(std::string _name, double _s_limit) {
	joint_name = _name;
	speed_limit = _s_limit;
}
void JointLimits::print() {
	std::cout<<"Joints' name is "<<joint_name<<" and its speed limit: "<<speed_limit<<std::endl;
}

bool JointLimits::isSmaller(double other) {
	if(fabs(speed_limit)<fabs(other)) 
		return true;
	return false;
}