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
        double shared_speed_limit;
		JointLimits(){}
		JointLimits(std::string _name, double _s_limit);
        JointLimits(std::string _name, double _s_limit, double _ss_limit);
		void setValues(std::string _name, double _s_limit);
        void setValues(std::string _name, double _s_limit, double __ss_limit);
		bool isSmaller(double other);
        bool isSharedSmaller(double other);
		void print();


};

#endif