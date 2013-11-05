#ifndef GRID_H
#define GRID_H

#include <vector>
#include "implicit.h"
#include "implicitblob.h"
#include "implicitsoft.h"
#include "point2.h"

#include "GLView.h"
#include <iostream>
#include <stdio.h>
#include <cstdio>
#include <math.h>
#include "blob.h"
#include "softobject.h"
using namespace std;

class Grid
{

typedef void(Grid::*FunctionPointer)(Point2, Point2, Point2, Point2, const Implicit *);

private:
    //Grid width
    double width;
    //Grid height
    double height;

    Implicit *f;

    //The points of the grid
    vector< vector<Point2> > gridPoints;
    //The values of the implicit funcion
    vector< vector<double> > values;
    //The points of the circle
    vector<Point2> circlePoints;

    FunctionPointer drawMSCase[16];


public:
    Grid();
    Grid(double width, double height, Implicit *f);

    /**
      * Draws the grid
      */
    void draw();

    /**
      * Evaluates the function on each point of the grid
      */
    void eval(const Implicit *f);

    /**
      * Evaluates the function on a given point
      */
    double eval(const Implicit *f, Point2 &p);

    /**
      * Goes through all the edges to interpolate the point that belongs
      * to the border of the surface
      */
    void findSurfacePoints(const Implicit *f);


    Point2 interpolateAtZero(Point2 &a, Point2 &b, const Implicit *f);

    //Draw the edges of the surface
    void drawEdgeLT(Point2 p0, Point2 p1, Point2 p2, Point2 p3, const Implicit *f);
    void drawEdgeTR(Point2 p0, Point2 p1, Point2 p2, Point2 p3, const Implicit *f);
    void drawEdgeRB(Point2 p0, Point2 p1, Point2 p2, Point2 p3, const Implicit *f);
    void drawEdgeBL(Point2 p0, Point2 p1, Point2 p2, Point2 p3, const Implicit *f);
    void drawEdgeH(Point2 p0, Point2 p1, Point2 p2, Point2 p3, const Implicit *f);
    void drawEdgeV(Point2 p0, Point2 p1, Point2 p2, Point2 p3, const Implicit *f);
    void drawSurfaceLine(Point2 a, Point2 b, const Implicit *f);
    void drawNothing(Point2, Point2, Point2, Point2, const Implicit *f);

    void drawEdgeBRLT(Point2 p0, Point2 p1, Point2 p2, Point2 p3, const Implicit *f);
    void drawEdgeBLTR(Point2 p0, Point2 p1, Point2 p2, Point2 p3, const Implicit *f);


    void fillCell(int x, int y, const Implicit *f);



};

#endif // GRID_H
