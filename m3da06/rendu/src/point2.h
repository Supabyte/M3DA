#ifndef POINT2_H
#define POINT2_H

#include <math.h>

class Point2
{
private:
    double x;
    double y;

public:
    Point2();
    Point2(double x, double y);

    double distance(Point2 &p) const;

    double getX();
    double getY();

    Point2 operator - (Point2&);
    Point2 operator + (Point2&);
    Point2 operator += (Point2&);
    Point2 operator * (double);
    Point2 operator / (double);


};

#endif // POINT2_H
