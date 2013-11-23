#include "point2.h"

Point2::Point2()
{

}

Point2::Point2(double _x, double _y){
    x = _x;
    y = _y;
    fixed = false;
}

Point2::Point2(double _x, double _y, bool f){
    x = _x;
    y = _y;
    fixed = f;
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

bool Point2::isFixed(){
    return fixed;
}

Point2 Point2::operator * (double d)
{
    Point2 p = Point2(x*d, y*d);
  return p;
}

Point2 Point2::operator +(Point2& p){
    Point2 pt(x+p.getX(), y+p.getY());
    return pt;
}

