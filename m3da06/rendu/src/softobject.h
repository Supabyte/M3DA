#ifndef SOFTOBJECT_H
#define SOFTOBJECT_H

#include "point2.h"
#include "implicitobject.h"

class SoftObject : public ImplicitObject
{
private:
public:
    SoftObject();
    SoftObject(Point2 _center, double _radius);

    /**
      * Evaluates the function at point (x,y)
      */
    virtual const double eval(double x, double y) ;

};

#endif // SOFTOBJECT_H
