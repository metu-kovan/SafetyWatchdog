#ifndef CLASS_BEKCI_POINT
#define CLASS_BEKCI_POINT

#include <iostream>
#include <string>

class JointLimits {
	private:
	public:
		std::string joint_name;
		double speed_limit;
		JointLimits(){}
		JointLimits(std::string _name, double _s_limit);
		void setValues(std::string _name, double _s_limit);
		void print();


};

#endif