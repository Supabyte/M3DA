#ifndef GRID_H
#define GRID_H

#include <vector>
#include "implicit.h"
#include "point2.h"
#include "glsupport.h"

#include "UtilGL.h"
#include <iostream>
#include <stdio.h>
#include <cstdio>
#include <math.h>

using namespace std;

class Grid
{

// typedef for the function pointers
typedef void(Grid::*FunctionPointer)(Point2, Point2, Point2, Point2, Implicit *);

private:
    //Grid width
    double width;
    //Grid height
    double height;

    //The surface to be drawn
    Implicit *f;

    //The points of the grid
    vector< vector<Point2> > gridPoints;
    //The values of the implicit funcion
    vector< vector<double> > values;
    //The points of the surface
    vector<Point2> surfacePoints;

    //Array of function pointers.
    //This wil store the functions that draw the different possible cases
    //of the marching squares algorithm
    FunctionPointer drawMSCase[16];

    //These variables determine what will be drawn
    bool _drawSurfacePoints;
    bool _drawValues;
    bool _fillSurface;

public:
    Grid();
    Grid(double width, double height, Implicit *f);

    /**
      * Initializes the vector that represents the points of the grid
      */
    void initGridPoints();

    /**
      * Draws the grid
      */
    void draw();

    /**
      * Draws the value of the implicit surface
      * function at each point of the grid
      */
    void drawValues();

    /**
      * Draws the points of the implicit surface
      */
    void drawSurfacePoints();

    /**
      * Fills the implicit surface
      */
    void fillSurface();


    /**
      * Evaluates the function on each point of the grid
      */
    void eval(Implicit *f);

    /**
      * Evaluates the function on a given point
      */
    double eval(Implicit *f, Point2 &p);

    /**
      * Goes through all the edges to interpolate the point that belongs
      * to the border of the surface
      */
    void findSurfacePoints(Implicit *f);

    /**
      * Returns the point at which the function associated with f is 0
      */
    Point2 interpolateAtZero(Point2 &a, Point2 &b, Implicit *f);

    //Draw the edges of the surface
    //Each of these methods draws a line between the interpolated points at
    //the specified pair of edges (Left, Top, Right, Bottom)
    //LT = Left-Top, RB = Right-Bottom, etc
    void drawEdgeLT(Point2 p0, Point2 p1, Point2 p2, Point2 p3, Implicit *f);
    void drawEdgeTR(Point2 p0, Point2 p1, Point2 p2, Point2 p3, Implicit *f);
    void drawEdgeRB(Point2 p0, Point2 p1, Point2 p2, Point2 p3, Implicit *f);
    void drawEdgeBL(Point2 p0, Point2 p1, Point2 p2, Point2 p3, Implicit *f);
    void drawEdgeH(Point2 p0, Point2 p1, Point2 p2, Point2 p3, Implicit *f);
    void drawEdgeV(Point2 p0, Point2 p1, Point2 p2, Point2 p3, Implicit *f);
    void drawSurfaceLine(Point2 a, Point2 b, Implicit *f);
    void drawNothing(Point2, Point2, Point2, Point2, Implicit *f);
    void drawEdgeBRLT(Point2 p0, Point2 p1, Point2 p2, Point2 p3, Implicit *f);
    void drawEdgeBLTR(Point2 p0, Point2 p1, Point2 p2, Point2 p3, Implicit *f);


    /**
      * This function decides which MS case to draw
      */
    void fillCell(int x, int y, Implicit *f);

    void toggleDrawSurfacePoints();
    void toggleDrawValues();
    void toggleFillSurface();

    void setResolution(double x, double y);

};

#endif // GRID_H
