#include "Sphere.h"

Sphere::Sphere(double & _r, double & _x, double & _y, double & _z) {
    r = _r;
    p.setValues(_x,_y,_z);
    status = 0;
}
Sphere::Sphere(double  _r, Point &  _p) {
    r = _r;
    p = _p;
    status = 0;
}

void Sphere::setValues(double & _r, double & _x, double & _y, double & _z) {
    r = _r;
    p.setValues(_x,_y,_z);
    status = 0;
}
void Sphere::setValues(double  _r, Point & _p) {
    r = _r;
    p = _p;
    status = 0;
}
void Sphere::setValues(double  _r, const bekci::Pose & _p) {
    r = _r;
    p.setValues(_p);
    status = 0;
}
void Sphere::print() {
    std::cout<<"R of Sphere is : "<<r<<" statu is "<<status<<" center of Sphere is ";
    p.print();
}
Sphere& Sphere::operator=(const Sphere& other) {
    this->r = other.r;
    this->p = other.p;
    return *this;
}