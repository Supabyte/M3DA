#include "curve.h"
#include <iostream>
using namespace std;

Curve::Curve()
{
    curvePoints = new vector<Point2> ();
}

void Curve::addPoint(Point2 &p){
    points.push_back(&p);
    this->update();
}

vector<Point2*> Curve::getPoints(){
    return points;
}

vector<Point2> *Curve::getCurvePoints(){
    return curvePoints;
}

void Curve::update(){
    this->eval();

    //TODO
    //curvePoints = *vec;
}

Curve::~Curve(){
    delete curvePoints;
}


