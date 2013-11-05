#ifndef IMPLICITBLOB_H
#define IMPLICITBLOB_H

#include "implicit.h"

class ImplicitBlob : public Implicit
{
private:
    vector<Blob> blobs;
public:
    ImplicitBlob();


    /**
      Evaluates the blobs at point (x,y)
      */
    virtual const double eval(double x, double y) const;

    /**
      * Adds a blob
      */
    void addBlob(Blob& blob);
};

#endif // IMPLICITBLOB_H
