#ifndef CLASS_BEKCI_BOX
#define CLASS_BEKCI_BOX

#include "Point.h"
#include "Vec3d.h"
#include "Sphere.h"
#include "Plane.h"
#include "vector"

// Box is created by a couple of planes
class Box {
    public:
        std::vector<Plane> planes;
        bool shared;
        Box();

        Box(std::vector<Plane>& _pl,bool _shared);
        

        void add_plane(Plane & _add);
        
        Box & operator=(const Box& other);
        void print();
        
        int checkSphereStatus(Sphere & sp,double mar);
    private:
        

};

#endif