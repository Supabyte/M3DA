#include "curve.h"
#include <iostream>
using namespace std;

Curve::Curve()
{
    curvePoints = new vector<Point2> ();
}

void Curve::addPoint(Point2 &p){
    points.push_back(p);
    referencePoints.push_back(p);
    this->update();
}

vector<Point2> Curve::getPoints(){
    return points;
}


vector<Point2> Curve::getReferencePoints(){
    return referencePoints;
}

vector<Point2> *Curve::getCurvePoints(){
    return curvePoints;
}

void Curve::update(){
    this->eval();
}

void Curve::subdivide(){
    referencePoints.clear();
    referencePoints.reserve(curvePoints->size());
    copy(curvePoints->begin(),curvePoints->end(),back_inserter(referencePoints));
    this->eval();
}

Curve::~Curve(){
    delete curvePoints;
}

void Curve::eval() {

    vector<Point2> *qvec = this->getCurvePoints();
    vector<Point2> refPts = this->getReferencePoints();
    vector<Point2> pts = this->getReferencePoints();

    qvec->clear();

    //TODO size is an unsigned int...
    if(refPts.size() > 0){
        for(int i = 0;  i < refPts.size()-1; i++){
            Point2 q1 = this->evalQ2i(i);
            Point2 q2 = this->evalQ2iPlus1(i);

            qvec->push_back(q1);
            qvec->push_back(q2);

        }
    }
}
