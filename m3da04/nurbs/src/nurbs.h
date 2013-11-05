#ifndef NURBS_H
#define NURBS_H
#include <vector>
#include "vector2.h"
#include "vector3.h"

class Nurbs
{
    std::vector<double> _knot;
    std::vector<Vector3> controlPoints;
    int degree;
public:
    Nurbs();
    /**
        Initializes a nurbs curve with the specified degree and control points
        @param p The degree of the curve
        @param points The control points
    */
    void initialize(int p, std::vector<Vector3> & points);


    /**
        Evaluates the Cox de Boor function for k and p at point t
    */
    double evaluate(int k, int p, double t);


    //E1Q8
    /**
        Calculates the point of the curve at t
    */
    Vector2 evalBSpline(double t);


    /**
        @return True if t is in the interval [ knot(a),knot(b) ). False otherwise
    */
    bool isIn(int t, int a, int b);


    /**
        Transforms window coordinates (between window width and height) to
        the area being used (glOrtho(-1,1,-1,1,-1,1))
        3D vectors have been used for immediacy, although only the x and y
        coordinates are taken into account.
        @param v The window coordinates
        @param width The draw area width
        @param height The draw area height
        @return A transformed Vector3

    */
    std::vector<Vector3> toNurbsCoords(std::vector<Vector3> v, int width, int height);


    //****************************
    //Getters, setters and adders
    //****************************
    /**
        @return The degree of the curve
    */
    int getDegree();

    /**
        Adds a control point
        @param point The control point to be added
    */
    void addControlPoint(Vector3& point);

    /**
        Sets the weight of the specified control point
        @param n The index of the point to be modified
        @param w The new weight
    */
    void setWeight(int n, double w);

    /**
        Sets the nodal vector
        @param v
    */
    void setNodalVector(std::vector<double> v);

    /**
        @return The knot with index k
    */
    double getP(int k);

    /**
        @return The control point vector
    */
    std::vector<Vector3> getControlPoints();

    /**
        @return The control point with index n
    */
    Vector3 getControlP(int n);
};

#endif // NURBS_H
