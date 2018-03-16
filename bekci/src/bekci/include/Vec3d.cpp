#include "Vec3d.h"

Vec3d::Vec3d() {
	x=0;
	y=0;
	z=0;
}

Vec3d::Vec3d( double _x, double _y, double _z){
    x = _x;
    y = _y;
    z = _z;
}

void Vec3d::setValues(double _x, double _y, double _z) {
    x = _x;
    y = _y;
    z = _z;
}

void Vec3d::print() {
	std::cout<<" x: "<<x<<" y: "<<y<<" z: "<<z<<std::endl;
}

Vec3d& Vec3d::operator=(const Vec3d & other){
	if(&other == this)
		return *this;
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
	return *this;
}

Vec3d Vec3d::operator/(double  num){
	Vec3d ret;
	ret.x = this->x/num;
	ret.y = this->y/num;
	ret.z = this->z/num;

	return ret;
}

void Vec3d::normalize(){
	double len = sqrt(pow(x,2)+ pow(y,2) + pow(z,2));
	(*this)= (*this)/len;

}
double Vec3d::dot(const Vec3d& other) {
	double sum = 0;
	sum += this->x*other.x;
	sum += this->y*other.y;
	sum += this->z*other.z;
	return sum;
}