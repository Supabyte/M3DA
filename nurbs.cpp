#include "nurbs.h"

Nurbs::Nurbs()
{

}

void Nurbs::initialize(int p, std::vector<Vector3> &points)
{
    double n = 0.0;
    this->degree = p;
    _knot.clear();
    for(int i = 1; i <= points.size()+p+1; i++){
        _knot.push_back(n++);
    }
    controlPoints.clear();
    for(int i = 0; i < points.size(); i++){
        controlPoints.push_back(points.at(i));
    }
}

double Nurbs::evaluate(int k, int p, double t){
    double result;
    double num1 = (t - _knot.at(k));
    double denom1 = (_knot.at(k+p) - _knot.at(k));
    double left = num1 / denom1;
    if(denom1 == 0){
        left = 0;
    }
    double num2 = (_knot.at(p+k+1) - t);
    double denom2 = (_knot.at(p+k+1) - _knot.at(k+1));
    double right = num2 / denom2;
    if(denom2 == 0){
        right = 0;
    }

    if(p > 0){
        result = left * this->evaluate(k, p-1, t)
                + right * this->evaluate(k+1, p-1, t);
    } else {
        if(this->isIn(t, k, k+1)){
            result = 1;
        } else {
            result = 0;
        }
    }

    return result;
}

Vector2 Nurbs::eval(double t){
    Vector2 result = Vector2(0,0);
    for(int k = 0; k < controlPoints.size(); k++){
        Vector3 weighted = controlPoints.at(k);
        weighted.setX(weighted.getX()*weighted.getZ());
        weighted.setY(weighted.getY()*weighted.getZ());
        Vector3 newVec3 = weighted * this->evaluate(k, degree, t);
        Vector2 newVec = Vector2(newVec3.getX(), newVec3.getY());
        result = result + newVec;
    }

    return result;
}

bool Nurbs::isIn(int t, int a, int b){
    return t >= _knot.at(a) && t < _knot.at(b);
}

