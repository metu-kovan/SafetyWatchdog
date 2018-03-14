#ifndef CLASS_BEKCI_PLANE
#define CLASS_BEKCI_PLANE

#include "Point.h"
#include "Vec3d.h"

// Plane is created by a point and a vector
class Plane {
    public:
        Vec3d normal;

        Point p;

        Plane();
        ~Plane();
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
        /*
        int checkSphereStatus { // returns 0 if not even close, returns 1 if sphere is in warning margin returns 2 if sphere is touching the boundary
            int status = 0;

            return status;
        }*/

    private:
        

};

#endif