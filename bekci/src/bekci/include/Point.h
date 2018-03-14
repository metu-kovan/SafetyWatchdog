#ifndef CLASS_BEKCI_POINT
#define CLASS_BEKCI_POINT


#include <iostream>

class Point {
    public:
        double x;
        double y;
        double z;

        Point();
        Point( double _x, double _y, double _z);
        void setValues(double _x, double _y, double _z);
        void print();
        Point& operator=(const Point& other);

    private:
        
        
};


#endif