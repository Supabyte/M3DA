#ifndef BLOB_H
#define BLOB_H

#include <math.h>
#include <point2.h>
#include "implicitobject.h"

class Blob : public ImplicitObject
{
private:
    double a;
    double b;
public:
    Blob();
    Blob(Point2 _center, double _radius, double _a, double _b);

    /**
      * Evaluates the function at point (x,y)
      */
    virtual const double eval(double x, double y) ;
};

#endif // BLOB_H
