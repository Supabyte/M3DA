#ifndef HOMOVECTOR_H
#define HOMOVECTOR_H

#include <vector2.h>

class Vector3
{
private:
    double x;
    double y;
    double z;
public:
    Vector3();
    Vector3(double, double, double);
    Vector3 operator +(Vector3&);
    Vector3 operator *(double);
    double getX();
    double getY();
    double getZ();
    void setX(double);
    void setY(double);
    void setZ(double);
    double distance(Vector2&);
    double distance(Vector3&);
};

#endif // HOMOVECTOR_H
