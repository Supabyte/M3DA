#ifndef IMPLICITCIRCLE_H
#define IMPLICITCIRCLE_H

#include "implicit.h"

class ImplicitCircle : public Implicit
{
public:
    ImplicitCircle();

    virtual const double eval(double x, double y) ;
};

#endif // IMPLICITCIRCLE_H
