#ifndef FOURPOINT_H
#define FOURPOINT_H

#include "curve.h"

class FourPoint : public Curve
{
private :
    vector<Point2*> qVector;
public:
    FourPoint();

    typedef Curve super;

    virtual void eval();
    virtual Point2 evalQ2i(int i);
    virtual Point2 evalQ2iPlus1(int i);

};

#endif // FOURPOINT_H
