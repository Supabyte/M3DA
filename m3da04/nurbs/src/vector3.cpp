#include "vector3.h"
#include <math.h>

Vector3::Vector3(double _x, double _y, double _z){
    x = _x;
    y = _y;
    z = _z;
}

Vector3 Vector3::operator *(double v){
    return Vector3(x*v, y*v, z*v);
}

Vector3 Vector3::operator +(Vector3 &v){
    return Vector3(v.getX()+x, v.getY()+y, v.getZ()+z);
}

double Vector3::getX(){
    return x;
}

double Vector3::getY(){
    return y;
}

double Vector3::getZ(){
    return z;
}

void Vector3::setX(double _x){
    x = _x;
}

void Vector3::setY(double _y){
    y = _y;
}

void Vector3::setZ(double _z){
    z = _z;
}

double Vector3::distance(Vector2 &v){    
    return sqrt(pow(v.getX()-x,2) + pow(v.getY()-y,2));
}

double Vector3::distance(Vector3 &v){

}

