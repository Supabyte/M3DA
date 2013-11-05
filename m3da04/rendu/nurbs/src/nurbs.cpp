#include "nurbs.h"
#include <iostream>

using namespace std;


Nurbs::Nurbs()
{

}

//E1Q1
void Nurbs::initialize(int p, std::vector<Vector3> &points)
{
    double n = 0.0;
    this->degree = p;
    _knot.clear();
    //Nodes
    for(int i = 1; i <= points.size()+p+1; i++){
        _knot.push_back(n++);
    }
    //Control points
    controlPoints.clear();
    for(int i = 0; i < points.size(); i++){
        controlPoints.push_back(points.at(i));
    }
}

//E1Q2
double Nurbs::evaluate(int k, int p, double t){
    double result;
    double num1 = (t - _knot.at(k));
    double denom1 = (_knot.at(k+p) - _knot.at(k));
    double leftOperand = num1 / denom1;
    if(denom1 == 0){
        leftOperand = 0;
    }
    double num2 = (_knot.at(p+k+1) - t);
    double denom2 = (_knot.at(p+k+1) - _knot.at(k+1));
    double rightOperand = num2 / denom2;
    if(denom2 == 0){
        rightOperand = 0;
    }

    if(p > 0){
        result = leftOperand * this->evaluate(k, p-1, t)
                + rightOperand * this->evaluate(k+1, p-1, t);
    } else {
        if(this->isIn(t, k, k+1)){
            result = 1;
        } else {
            result = 0;
        }
    }


    return result;
}

//E1Q8
Vector2 Nurbs::evalBSpline(double t){
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


double Nurbs::getP(int k){
    return _knot.at(k);
}


std::vector<Vector3> Nurbs::getControlPoints(){
    return controlPoints;
}


Vector3 Nurbs::getControlP(int n){
    return controlPoints.at(n);
}


int Nurbs::getDegree(){
    return degree;
}


void Nurbs::setNodalVector(std::vector<double> v){
    _knot = v;
}

std::vector<Vector3> Nurbs::toNurbsCoords(std::vector<Vector3> points, int width, int height){
    std::vector<Vector3> transformedPoints;

    for(int i = 0;  i < points.size(); i++){
        Vector3 p = points.at(i);
        transformedPoints.push_back(Vector3( (p.getX()-width/2)/(width/2), (p.getY()-height/2)/-(height/2), p.getZ()));
    }

    return transformedPoints;
}

void Nurbs::addControlPoint(Vector3 &p){
    controlPoints.push_back(p);
}

void Nurbs::setWeight(int n, double w){
    Vector3 p = controlPoints.at(n);
    p.setZ(w);
}
