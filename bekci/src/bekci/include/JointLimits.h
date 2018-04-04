#ifndef CLASS_BEKCI_JOINT_LIMITS
#define CLASS_BEKCI_JOINT_LIMITS

#include <iostream>
#include <string>
#include <math.h> 
class JointLimits {
	private:
	public:
		std::string joint_name;
		double speed_limit;
		JointLimits(){}
		JointLimits(std::string _name, double _s_limit);
		void setValues(std::string _name, double _s_limit);
		bool isSmaller(double other);
		void print();


};

#endif