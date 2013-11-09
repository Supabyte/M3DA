#include "chaikin.h"
#include <iostream>
using namespace std;
Chaikin::Chaikin()
{
}

void Chaikin::eval() {
    cout << "Chaikin" << endl;
    vector<Point2> *qvec = this->getCurvePoints();
    vector<Point2*> pts = this->getPoints();

    qvec->clear();

    //TODO size is an unsigned int...
    if(pts.size() > 0){
        cout << pts.size()-1 << endl;
        for(int i = 0;  i < pts.size()-1; i++){
            Point2* p1 = pts.at(i);
            Point2* p2 = pts.at(i+1);
//            Point2 *q1 = &(*p1 * (3.0/4.0) + *p2 * (1.0/4.0));
//            Point2 *q2 = &(*p1 * (1.0/4.0) + *p2 * (3.0/4.0));
//            Point2 q1 = Point2(1.0, 1.0);
            Point2 q1 = Point2(p1->getX()*0.75 + p2->getX()*0.25, p1->getY()*0.75+p2->getY()*0.25);
            Point2 q2 = Point2(p1->getX()*0.25 + p2->getX()*0.75, p1->getY()*0.25+p2->getY()*0.75);
            qvec->push_back(q1);
            qvec->push_back(q2);

        }
    }


}
