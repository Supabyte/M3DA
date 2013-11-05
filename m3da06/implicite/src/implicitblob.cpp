#include "implicitblob.h"
#include <iostream>
using namespace std;

ImplicitBlob::ImplicitBlob()
{
}

const double ImplicitBlob::eval(double x, double y) const{
    double sum = 0.0;
    double n = blobs.size();
    for(int i = 0; i < n; i++){
        double v = blobs[i].eval(x, y);
        sum += v;

    }
    return 1-sum;
}

void ImplicitBlob::addBlob(Blob &blob){
    blobs.push_back(blob);
}
