/**
*
*  @author F. Aubert
*  @file GLView
*
*/



#ifndef GLVIEW_H
#define GLVIEW_H

#include "glsupport.h"

#include "UtilGL.h"
#include <QtEvents>
#include "nurbs.h"
#include <vector>
#include "vector2.h"
#include "vector3.h"
#include <QLineEdit>


/**
  @class GLView

  The widget to draw with OpenGL.
  */
class GLView : public QGLWidget {
  Q_OBJECT
public:
  //! Ctor
  explicit GLView(QWidget *parent = 0);
  //! Dtor
  virtual ~GLView();

  //! initialize data application
  void initData();


  /**
    @return A Nurbs object with the current parameters
  */
  Nurbs* generateNurbs();

  //E1Q3
  void drawN(int k, int p, Nurbs *n);

  //E1Q4
  void drawNKP(Nurbs *n);

  //E1Q8
  void drawSpline(Nurbs* n);

  //E1Q10
  void drawAnimation(Nurbs* n);

  //E1Q11
  void drawNonUniform(Nurbs* n);
  //E1Q12
  void drawOpenUniform(Nurbs* n);

  /**
    Draws the control polygon of the specified Nurbs
    @params The Nurbs
   */
  void drawControlPolygon(Nurbs *nurbs);

  /**
    Draw the given set of points
   */
  void drawPoints(std::vector<Vector3>);


protected:
  // OpenGL drawing :
  //! initialize the OpenGL context
  void initializeGL();
  //! OpenGL drawing (called when updateGL() )
  void paintGL();
  //! should update projection (called when the widget is resized)
  void resizeGL(int width,int height);

  // events :
  //! called when a mouse button is pressed in the widget
  void mousePressEvent(QMouseEvent *event);
  //! called when the mouse is moved in the widget
  void mouseMoveEvent(QMouseEvent *event);
  //! called when a mouse button is released in the widget
  void mouseReleaseEvent(QMouseEvent *event);
  //! called when a key is pressed in the widget
  void keyPressEvent( QKeyEvent *event );
  //! called when a key is released in the widget
  void keyReleaseEvent( QKeyEvent *event );
  //! called when the mouse wheel is turned
  void wheelEvent(QWheelEvent *event);


private:

  //The points added by the user
  std::vector<Vector3> points;
  //The degree of the curves. This can be chosen by the user
  int degree;
  //The currently selected option
  int choice;
  //Step to draw the animation
  double animStep;
  //The to be set to the selected point
  double weight;
  //Determines the area around each point that is sensitive to
  //clicks
  double highlighThreshold;
  //Determines which point is highlighted
  int highlighted;
  //Determines if the user is currently grabbing a point
  bool grabbing;
  //Used for adapting screen coordinates
  int width;
  int height;


signals:

public slots:
  //! called every 20ms by the MainWindow
  void updateData();

  void choice1();
  void choice2();
  void choice3();
  void choice4();
  void choice5();
  void choice6();
  void choice7(QWidget*);
  void choice8(QWidget*);


};

#endif // GLVIEW_H
