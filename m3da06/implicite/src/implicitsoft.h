#ifndef IMPLICITSOFT_H
#define IMPLICITSOFT_H

#include "implicit.h"
#include <math.h>
#include "softobject.h"

class ImplicitSoft : public Implicit
{
private:
    vector<SoftObject> objects;
public:
    ImplicitSoft();

    /**
      * Evaluates the function at point (x,y)
      */
    virtual const double eval(double x, double y) const;

    /**
      * Adds an object
      */
    void addObject(SoftObject& object);
};

#endif // IMPLICITSOFT_H
