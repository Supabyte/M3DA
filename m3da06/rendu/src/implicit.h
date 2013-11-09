#ifndef IMPLICIT_H
#define IMPLICIT_H

#include "implicitobject.h"
#include "blob.h"
#include <vector>
using namespace std;

class Implicit
{

private:
    vector<ImplicitObject*> objects;
public:
    Implicit();
    /**
      Evaluates the function at point (x,y)
      */
    virtual const double eval(double x, double y);

    /**
      * Adds an object
      */
    void addObject(ImplicitObject& object);

    /**
      * Returns nth implicit object
      */
    ImplicitObject* getObject(int n);

    /**
      * Returns the vector of objects
      */
    vector<ImplicitObject*> getObjects();

};

#endif // IMPLICIT_H
