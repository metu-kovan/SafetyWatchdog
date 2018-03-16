#ifndef CLASS_BEKCI_POINT
#define CLASS_BEKCI_POINT


#include <iostream>
#include <bekci/Pose.h>
#include "Vec3d.h"
class Point {
    public:
        double x;
        double y;
        double z;

        Point();
        Point( double _x, double _y, double _z);
        Point(bekci::Pose & _p);
        void setValues(double _x, double _y, double _z);
        void setValues(const bekci::Pose& p);
        void print();
        Point& operator=(const Point& other);
        Vec3d operator-(const Point& other);

    private:
        
        
};


#endif