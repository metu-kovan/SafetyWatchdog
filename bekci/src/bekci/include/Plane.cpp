#include "Plane.h"

Plane::Plane(double & n_x, double & n_y, double & n_z, double & p_x, double & p_y, double & p_z) {
    normal.setValues(n_x,n_y,n_z);

    p.setValues(p_x,p_y,p_z);
}
Plane::Plane(double & n_x, double & n_y, double & n_z, Point & _p) {
    normal.setValues(n_x,n_y,n_z);

    this->p = _p;
}
Plane::Plane(Vec3d & _n , double & p_x, double & p_y, double & p_z) {
    this->normal = _n;

    p.setValues(p_x,p_y,p_z);
}
Plane::Plane(Vec3d & _n, Point & _p) {
    this->normal = _n;
    this->p = _p;
}
void Plane::setValues(double & n_x, double & n_y, double & n_z, double & p_x, double & p_y, double & p_z) {
    normal.setValues(n_x,n_y,n_z);

    p.setValues(p_x,p_y,p_z);
}

void Plane::setValues(double & n_x, double & n_y, double & n_z, Point & _p) {
    normal.setValues(n_x,n_y,n_z);

    this->p = _p;
}
void Plane::setValues(Vec3d & _n , double & p_x, double & p_y, double & p_z) {
    this->normal = _n;

    p.setValues(p_x,p_y,p_z);
}
void Plane::setValues(Vec3d & _n, Point & _p) {
    this->normal = _n;
    this->p = _p;
}

Plane& Plane::operator=(const Plane& other) {
    this->normal = other.normal;

    this->p = other.p;

    return *this;
}
void Plane::print() {
    std::cout<<"Normal of plane ";
    normal.print();
    std::cout<<" Point on plane ";
    p.print();
}

/*
 returns 0 if not even close, 
 returns 1 if sphere is in warning margin 
 returns 2 if sphere is touching the boundary, 
 returns 3 if sphere passed the boundary 

*/

int Plane::checkSphereStatus(Sphere & sp,double mar) { 
    int status = 0;
    Vec3d s_to_p = p-sp.p;
    //s_to_p.print();
    //normal.print();
    double dot_res = s_to_p.dot(normal);
    //std::cout<<"fabs "<<fabs(dot_res)<<" r+m "<<sp.r+mar<<std::endl;
    if (dot_res>0) {
        status = 2;
    }
    else if(fabs(dot_res)<=sp.r) {
        status = 2;
    }
    else if(fabs(dot_res)>sp.r && fabs(dot_res)<=sp.r+mar) {
        status = 0;
    }    
    return status;
}
