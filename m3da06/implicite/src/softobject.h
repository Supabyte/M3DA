#ifndef SOFTOBJECT_H
#define SOFTOBJECT_H

#include "point2.h"

class SoftObject
{
private:
    Point2 center;
    double radius;
public:
    SoftObject();
    SoftObject(Point2 _center, double _radius);

    /**
      * Evaluates the function at point (x,y)
      */
    const double eval(double x, double y) const;
};

#endif // SOFTOBJECT_H
