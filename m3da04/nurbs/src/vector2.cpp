#include "vector2.h"

Vector2::Vector2(double _x, double _y){
    x = _x;
    y = _y;
}

Vector2 Vector2::operator *(double v){
    return Vector2(x*v, y*v);
}

Vector2 Vector2::operator +(Vector2 &v){
    return Vector2(v.getX()+x,v.getY()+y);
}

double Vector2::getX(){
    return x;
}

double Vector2::getY(){
    return y;
}
