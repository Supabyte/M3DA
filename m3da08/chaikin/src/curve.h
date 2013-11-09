#ifndef CURVE_H
#define CURVE_H

#include <vector>
#include "point2.h"
using namespace std;

class Curve
{
private:
    vector<Point2*> points;
    vector<Point2>* curvePoints;
public:
    Curve();
    ~Curve();
    vector<Point2*> getPoints();
    vector<Point2>* getCurvePoints();
    void addPoint(Point2 &);
    void update();
    virtual void eval() = 0;

};

#endif // CURVE_H
