#ifndef CHAIKIN_H
#define CHAIKIN_H

#include "curve.h"

class Chaikin : public Curve
{
private:
    vector<Point2*> qVector;
    vector<int> fixedPoints;
public:
    Chaikin();
    virtual void eval();
    virtual Point2 evalQ2i(int i);
    virtual Point2 evalQ2iPlus1(int i);
};

#endif // CHAIKIN_H
