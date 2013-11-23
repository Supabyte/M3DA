#ifndef POINT2_H
#define POINT2_H

#include <math.h>

class Point2
{
private:
    double x;
    double y;
    bool fixed; //TODO OO?
public:
    Point2();
    Point2(double x, double y);
    Point2(double x, double y, bool fix);

    double distance(Point2 &p) const;

    double getX();
    double getY();
    bool isFixed();

    Point2 operator*(double);
    Point2 operator+(Point2 &);

};

#endif // POINT2_H
