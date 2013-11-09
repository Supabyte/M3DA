#ifndef CHAIKIN_H
#define CHAIKIN_H

#include "curve.h"

class Chaikin : public Curve
{
private:
    vector<Point2*> qVector;

public:
    Chaikin();
    virtual void eval();



};

#endif // CHAIKIN_H
