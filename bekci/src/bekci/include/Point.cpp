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