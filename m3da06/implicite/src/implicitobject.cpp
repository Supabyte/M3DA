#include "implicitobject.h"

ImplicitObject::ImplicitObject()
{
}

ImplicitObject::ImplicitObject(Point2 c, double r)
{
    center = c;
    radius = r;
    speed = Point2(0.0, 0.0);
}

void ImplicitObject::setCenter(Point2 &c){
    center = c;
}

Point2 ImplicitObject::getCenter(){
    return center;
}

Point2 ImplicitObject::getSpeed(){
    return speed;
}

void ImplicitObject::setSpeed(Point2 &s){
    speed = s;
}

double ImplicitObject::getRadius(){
    return radius;
}
