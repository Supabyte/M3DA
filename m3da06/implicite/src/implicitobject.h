#ifndef IMPLICITOBJECT_H
#define IMPLICITOBJECT_H

#include "point2.h"

class ImplicitObject
{
private:
    Point2 center;
    Point2 speed; //TODO Vector2
    double radius;
public:
    ImplicitObject();
    ImplicitObject(Point2 c, double r);

    virtual const double eval(double x, double y)  = 0;

    //Getters and setters
    void setCenter(Point2 &c);
    Point2 getCenter();
    Point2 getSpeed();
    void setSpeed(Point2&);
    double getRadius();

};



#endif // IMPLICITOBJECT_H
