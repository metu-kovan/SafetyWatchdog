#ifndef CLASS_BEKCI_PLANE
#define CLASS_BEKCI_PLANE

#include "Point.h"
#include "Vec3d.h"
#include "Sphere.h"

// Plane is created by a point and a vector
class Plane {
    public:
        Vec3d normal;

        Point p;

        Plane();

        Plane(double & n_x, double & n_y, double & n_z, double & p_x, double & p_y, double & p_z) ;
        Plane(double & n_x, double & n_y, double & n_z, Point & _p);
        Plane(Vec3d & _n , double & p_x, double & p_y, double & p_z);
        Plane(Vec3d & _n, Point & _p);

        void setValues(double & n_x, double & n_y, double & n_z, double & p_x, double & p_y, double & p_z);
        void setValues(double & n_x, double & n_y, double & n_z, Point & _p);
        void setValues(Vec3d & _n , double & p_x, double & p_y, double & p_z);
        void setValues(Vec3d & _n, Point & _p);
        
        Plane & operator=(const Plane& other);
        void print();
        
        int checkSphereStatus(Sphere & sp,double mar);
    private:
        

};

#endif