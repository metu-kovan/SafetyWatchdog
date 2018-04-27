#include "Box.h"
#include <iostream>


Box::Box(std::vector<Plane>& _pl) {
    this->planes = _pl;
}


void Box::add_plane(Plane & _add) {
    this->planes.push_back(_add);
}

Box & Box::operator=(const Box& other) {
    this->planes = other.planes;
    return *this;
}
void Box::print() {
    std::cout<<"Box have "<<this->planes.size()<<" many planes"<<std::endl;
    for(int i=0;i<this->planes.size();i++) {
        this->planes[i].print();
    }
}

int Box::checkSphereStatus(Sphere & sp,double mar)  {
    int two_count = 0;
    int one_count = 0;
    int three_count = 0;
    for(int i=0;i<this->planes.size();i++) {
        int temp;
        temp = this->planes[i].checkSphereStatus(sp,mar);
        std::cout<<"danger for plane "<<i<< " is "<<temp<<std::endl;
        if(temp == 3)
            three_count++;
        else if(temp == 2)
            two_count++;
        else if(temp == 2)
            one_count++;
    }
    if ((three_count + two_count )== this->planes.size()) {
        return 2;
    }
    else if(three_count>0 || two_count>0) {
        return 1;
    }
    return 0;

}