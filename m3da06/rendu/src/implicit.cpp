#include "implicit.h"
#include <math.h>
#include <iostream>
using namespace std;

Implicit::Implicit()
{
}

const double Implicit::eval(double x, double y) {

    vector<ImplicitObject*> objects = this->getObjects();
    double sum = 0.0;
    double n = objects.size();
    for(int i = 0; i < n; i++){
        double v = objects[i]->eval(x, y);
        sum += v;

    }
    return 1-sum;
}

void Implicit::addObject(ImplicitObject &object){
    objects.push_back(&object);
}

ImplicitObject* Implicit::getObject(int n){
    return objects.at(n);
}

vector<ImplicitObject*> Implicit::getObjects(){
    return objects;
}
