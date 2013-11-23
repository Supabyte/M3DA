#include "fourpoint.h"
#include <iostream>
using namespace std;


FourPoint::FourPoint()
{
}

void FourPoint::eval() {

    vector<Point2> *qvec = this->getCurvePoints();
    vector<Point2> pts = this->getReferencePoints();    
    if(pts.size() > 2){
        qvec->clear();        
        //TODO size is an unsigned int...
        if(pts.size() > 2){
            for(int i = 0;  i < pts.size(); i++){
                Point2 q1 = this->evalQ2i(i);
                Point2 q2 = this->evalQ2iPlus1(i);
                qvec->push_back(q1);
                qvec->push_back(q2);
            }
            qvec->push_back(pts.at(0));
        }
    }
}

Point2 FourPoint::evalQ2i(int i){
    vector<Point2> pts = this->getReferencePoints();
    Point2 p1 = pts.at(i);
    return p1;
}

Point2 FourPoint::evalQ2iPlus1(int i){
    vector<Point2> pts = this->getReferencePoints();
    Point2 pi = pts.at(i);
    Point2 pi1 = pts.at((i+1)%pts.size());
    Point2 piMinus1 = pts.at((i-1)%pts.size());
    Point2 pi2 = pts.at((i+2)%pts.size());

    //First point sum
    Point2 fpsum = Point2(pi2.getX()+piMinus1.getX(), pi2.getY()+piMinus1.getY());
    //Second point sum
    Point2 spsum = Point2(pi1.getX()+pi.getX(), pi1.getY()+pi.getY());

    Point2 leftOperand = fpsum*(-1.0/16.0);
    Point2 rightOperand = spsum*(9.0/16.0);
    Point2 q = leftOperand + rightOperand;

    return q;
}
