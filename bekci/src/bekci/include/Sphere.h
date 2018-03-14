#ifndef CLASS_BEKCI_SPHERE
#define CLASS_BEKCI_SPHERE
#include <iostream>
#include "Point.h"
class Sphere {
    public:
        double r;
        Point p;
        Sphere();
        Sphere(double & _r, double & _x, double & _y, double & _z);
        Sphere(double & _r, Point &  _p);
        ~Sphere();
        void setValues(double & _r, double & _x, double & _y, double & _z);
        void setValues(double & _r, Point & _p);
        void print();
        Sphere& operator=(const Sphere& b);
    private:
        
};
#endif //CLASS_BEKCI_SPHERE