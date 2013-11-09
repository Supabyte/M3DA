#include "softobject.h"


SoftObject::SoftObject(Point2 _center, double _radius) : ImplicitObject(_center, _radius)
{

}

const double SoftObject::eval(double x, double y) {
    double result = 0.0;

    Point2 p = Point2(x,y);
    Point2 center = this->getCenter();
    double radius = this->getRadius();
    double distance = center.distance(p);
    double r6 = pow(distance, 6.0);
    double r4 = pow(distance, 4.0);
    double r2 = pow(distance, 2.0);
    double ri6 = pow(radius, 6.0);
    double ri4 = pow(radius, 4.0);
    double ri2 = pow(radius, 2.0);
    if(distance < radius){
        result =  1 - ((4.0*r6)/(9.0*ri6)) + ((17.0*r4)/(9.0*ri4)) - ((22.0*r2)/(9.0*ri2));
    }

    return result;
}

