#ifndef BLOB_H
#define BLOB_H

#include <math.h>
#include <point2.h>

class Blob
{
private:
    Point2 center;
    double radius;
    double a;
    double b;
public:
    Blob();
    Blob(Point2 _center, double _radius, double _a, double _b);

    /**
      * Evaluates the function at point (x,y)
      */
    const double eval(double x, double y) const;
};

#endif // BLOB_H
