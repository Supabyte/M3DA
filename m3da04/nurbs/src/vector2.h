#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2
{

private:
    double x;
    double y;
public:
    Vector2(double, double);
    Vector2 operator +(Vector2&);
    Vector2 operator *(double);
    double getX();
    double getY();
};

#endif // VECTOR2_H
