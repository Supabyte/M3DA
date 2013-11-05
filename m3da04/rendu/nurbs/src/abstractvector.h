#ifndef ABSTRACTVECTOR_H
#define ABSTRACTVECTOR_H

class AbstractVector
{
protected:
    double x;
    double y;
public:
    virtual Vector2 operator +(AbstractVector&);
    virtual Vector2 operator *(double);
    AbstractVector();

};

#endif // ABSTRACTVECTOR_H
