#include "implicitcircle.h"

ImplicitCircle::ImplicitCircle()
{
}

const double ImplicitCircle::eval(double x, double y) {
    return -pow(x,2.0) - pow(y, 2.0) + 1;
}
