#ifndef CLASS_BEKCI_VEC3D
#define CLASS_BEKCI_VEC3D


#include <iostream>
#include <math.h>  

class Vec3d {
    public:
        double x;
        double y;
        double z;

        Vec3d();
        Vec3d( double _x, double _y, double _z);
        void setValues(double _x, double _y, double _z);
        void print();
        Vec3d& operator=(const Vec3d& other);
        Vec3d operator/(double  num);
        void normalize();
        double dot(const Vec3d& other);

    private:
        
        
};


#endif