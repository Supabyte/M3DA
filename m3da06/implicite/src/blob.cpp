#include "blob.h"

Blob::Blob()
{
}

Blob::Blob(Point2 _center, double _radius, double _a, double _b){
    center = _center;
    radius = _radius;
    a = _a;
    b = _b;
}

const double Blob::eval(double x, double y) const{
    Point2 p = Point2(x,y);
    return a * exp(-b*(center.distance(p) / radius));
}


