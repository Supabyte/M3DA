#include "chaikin.h"
#include <iostream>
using namespace std;
Chaikin::Chaikin()
{
}

void Chaikin::eval() {

    vector<Point2> *qvec = this->getCurvePoints();
    vector<Point2> refPts = this->getReferencePoints();


    qvec->clear();

    //TODO size is an unsigned int...
    if(refPts.size() > 0){
        for(int i = 0;  i < refPts.size()-1; i++){
            if(refPts.at(i).isFixed()){
                qvec->push_back(refPts.at(i));
            }
            Point2 p = refPts.at(i);
            Point2 p2 = refPts.at(i+1);
            Point2 q1;
            Point2 q2;
            if(!p.isFixed()){
                q1 = this->evalQ2i(i);
            } else {
                q1 = p;
            }

            if(!p2.isFixed()){
                q2 = this->evalQ2iPlus1(i);
            } else {
                q2 = p2;
            }
            qvec->push_back(q1);
            qvec->push_back(q2);

        }
        //Add last point if it's fixed
        if(refPts.at(refPts.size()-1).isFixed()){
            qvec->push_back(refPts.at(refPts.size()-1));
        }

    }
}

Point2 Chaikin::evalQ2i(int i){
    vector<Point2> pts = this->getReferencePoints();
    Point2 p1 = pts.at(i);
    Point2 p2 = pts.at(i+1);
    Point2 q1 = Point2(p1.getX()*0.75 + p2.getX()*0.25, p1.getY()*0.75+p2.getY()*0.25);
    return q1;
}

Point2 Chaikin::evalQ2iPlus1(int i){
    vector<Point2> pts = this->getReferencePoints();
    Point2 p1 = pts.at(i);
    Point2 p2 = pts.at(i+1);
    Point2 q2 = Point2(p1.getX()*0.25 + p2.getX()*0.75, p1.getY()*0.25+p2.getY()*0.75);
    return q2;
}
