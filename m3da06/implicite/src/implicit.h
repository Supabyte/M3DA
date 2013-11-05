#ifndef IMPLICIT_H
#define IMPLICIT_H

#include "blob.h"
#include <vector>
using namespace std;

class Implicit
{

private:

public:
    Implicit();
    /**
      Evaluates the function at point (x,y)
      */
    virtual const double eval(double x, double y) const;

};

#endif // IMPLICIT_H
