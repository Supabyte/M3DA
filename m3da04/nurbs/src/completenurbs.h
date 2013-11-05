#ifndef COMPLETENURBS_H
#define COMPLETENURBS_H

class CompleteNurbs : public Nurbs
{
public:
    CompleteNurbs();
    Vector3 evalBSpline(double);
};

#endif // COMPLETENURBS_H
