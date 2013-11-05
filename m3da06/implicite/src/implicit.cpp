#include "implicit.h"
#include <math.h>
#include <iostream>
using namespace std;

Implicit::Implicit()
{
}

const double Implicit::eval(double x, double y) const{
    return pow(x,2.0) + pow(y, 2.0) - 1;
}

