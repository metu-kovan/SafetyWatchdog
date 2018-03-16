#include "Point.h"

Point::Point() {
	x=0;
	y=0;
	z=0;
}

Point::Point( double _x, double _y, double _z){
    x = _x;
    y = _y;
    z = _z;
}

void Point::setValues(double _x, double _y, double _z) {
    x = _x;
    y = _y;
    z = _z;
}

void Point::print() {
	std::cout<<" x: "<<x<<" y: "<<y<<" z: "<<z<<std::endl;
}

Point& Point::operator=(const Point & other){
	if(&other == this)
		return *this;
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
	return *this;
}

Vec3d Point::operator-(const Point& other){
	Vec3d ret;
	ret.x = this->x-other.x;
	ret.y = this->y-other.y;
	ret.z = this->z-other.z;
	return ret;
}

Point::Point(bekci::Pose & _p) {
	x= _p.x;
	y= _p.y;
	z= _p.z;
}
void Point::setValues(const bekci::Pose& _p) {
	x= _p.x;
	y= _p.y;
	z= _p.z;
}