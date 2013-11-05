#include "implicitsoft.h"
#include <iostream>
using namespace std;

ImplicitSoft::ImplicitSoft()
{

}

const double ImplicitSoft::eval(double x, double y) const {

    double sum = 0.0;
    double n = objects.size();
    for(int i = 0; i < n; i++){
        double v = objects[i].eval(x, y);
        sum += v;

    }
    return sum;
}

void ImplicitSoft::addObject(SoftObject &object){
    objects.push_back(object);
}



