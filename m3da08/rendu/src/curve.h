#ifndef CURVE_H
#define CURVE_H

#include <vector>
#include "point2.h"
using namespace std;

class Curve
{
private:
    vector<Point2> points;
    vector<Point2> referencePoints;
    vector<Point2>* curvePoints;
public:
    Curve();
    ~Curve();
    vector<Point2> getPoints();
    vector<Point2> getReferencePoints();
    vector<Point2>* getCurvePoints();
    void addPoint(Point2 &);
    void update();
    virtual void eval();
    virtual Point2 evalQ2i(int i) = 0;
    virtual Point2 evalQ2iPlus1(int i) = 0;
    void subdivide();

};

#endif // CURVE_H
