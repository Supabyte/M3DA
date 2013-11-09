#include "blob.h"


Blob::Blob(Point2 _center, double _radius, double _a, double _b) : ImplicitObject(_center, _radius){
    a = _a;
    b = _b;
}

const double Blob::eval(double x, double y) {
    Point2 p = Point2(x,y);
    Point2 center = this->getCenter();
    double radius = this->getRadius();
    return a * exp(-b*(center.distance(p) / radius));
}

