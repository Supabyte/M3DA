#include "point2.h"

Point2::Point2()
{

}

Point2::Point2(double _x, double _y){
    x = _x;
    y = _y;
}

double Point2::distance(Point2 &p) const{
    return sqrt(pow(p.getX()-x, 2.0) + pow(p.getY()-y, 2.0));
}

double Point2::getX(){
    return x;
}

double Point2::getY(){
    return y;
}
