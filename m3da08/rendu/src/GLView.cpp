/**

  @author F. Aubert
  **/


#include "GLView.h"
#include <iostream>
#include <QPushButton>
#include "chaikin.h"
#include "fourpoint.h"

using namespace std;
using namespace prog3d;


/// ctor
GLView::GLView(QWidget *parent) : QGLWidget(parent) {

  setFocusPolicy(Qt::StrongFocus); // this widget can now catch the keyboard events

  _choice=1;
  closed = false;
}


/// dtor
GLView::~GLView() {
}

/**
 initialize GL context (with glew ou without glew) + common set up
 **/
void GLView::initializeGL() {

#ifdef WITH_GLEW
  // initialization of all available OpenGL functionalities
  if (glewInit()!=GLEW_OK) {
    throw ErrorD("cant initialize glew");
  }
#endif

  cout << "GL version :" << glGetString(GL_VERSION) << endl;
  cout << "Shading Language  : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;

  // common OpenGL set up
  glEnable(GL_DEPTH_TEST);  // hidden parts removal with depth buffer algorithm
  glClearColor(1,1,1,1); // color value when glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) is done
  glClearDepth(1.0);       // depth value when glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) is done

  glDisable(GL_STENCIL_TEST);
  glClearStencil(0);

  // polygon drawings set up
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

  glPixelStorei(GL_PACK_ALIGNMENT,4);
  glPixelStorei(GL_UNPACK_ALIGNMENT,4);

  ugl::initUtilGL(this);

  initData();

}


/** ***************************************************************************
resize
  **/


/// when the graphics window is sized/resized (including the first time the window is shown)
void GLView::resizeGL(int width, int height) {
  glViewport(0,0,width,height);
  panelWidth = width;
  panelHeight = height;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1,1,-1,1,-1,1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}



/** **********************************************************************
  Events
  **/
void GLView::mousePressEvent(QMouseEvent *event) {

    double x = event->x();
    double y = event->y();

    x = (x-panelWidth/2)/(panelWidth/2);
    y = -(y-panelHeight/2)/(panelHeight/2);

    if (event->button()==Qt::LeftButton) {

    Point2 *p = new Point2(x, y);
    curve->addPoint(*p);

  }
  if (event->button()==Qt::RightButton) {
    cout << "right mouse : " << event->x() << "," << event->y() << endl;
    Point2 *p = new Point2(x, y, true);
    curve->addPoint(*p);
  }
}

void GLView::mouseMoveEvent(QMouseEvent *event) {
  cout << "motion : " << event->x() << "," << event->y() << endl;
}

void GLView::mouseReleaseEvent(QMouseEvent *event) {
  switch(event->button()){
  case Qt::LeftButton:
      cout << "left mouse released" << endl;
    break;
  case Qt::RightButton:
    break;
  default:break;
  }
}

void GLView::wheelEvent(QWheelEvent *event) {
  cout << "mouse wheel :" << event->delta() << endl;
}


void GLView::keyPressEvent(QKeyEvent *event) {
  if (event->isAutoRepeat())
    QGLWidget::keyPressEvent(event);
  else
    switch(event->key()){
    case Qt::Key_C:
        cout << "Z pressed" << endl;
        closed = !closed;
      break;
    case Qt::Key_S:
        cout << "S pressed" << endl;
        curve->subdivide();
      break;
    case Qt::Key_Space:
        cout << "space pressed" << endl;
      break;
    default:
      QGLWidget::keyPressEvent(event); // dispatch the event to the parent
    }
}

void GLView::keyReleaseEvent(QKeyEvent *event) {
  if (event->isAutoRepeat())
    QGLWidget::keyReleaseEvent(event);
  else
    switch(event->key()){
      case Qt::Key_Space:
        cout << "space released" << endl;
      case Qt::Key_Z:
        break;
      case Qt::Key_S:
        break;
      default:
        QGLWidget::keyReleaseEvent(event); // dispatch the event to the parent
    }
}



/** ***************************************************************************
  init/update data
  **/
void GLView::initData() {
}

void GLView::updateData() {
  // update data :


  // update view :
  updateGL();
}


/** ******************************************************************* **/
/**
  Drawings
**/


void GLView::drawChoice0() {
  /// drawing example

  glColor3f(0,0.5,1);
  ugl::drawText("drawChoice0: "+_choiceText,0,0);

  glPushMatrix();

  glColor3f(1,0,0);

  vector<Point2> points = curve->getPoints();
  vector<Point2> refPoints = curve->getReferencePoints();
  vector<Point2> *curvePoints = curve->getCurvePoints();

  //User-defined polygon
  glLineWidth(1);
  glColor3f(1,0,0);
  glBegin(GL_LINE_STRIP);
  for(int i = 0; i < points.size(); i++){
      Point2 p = points.at(i);
      glVertex2f(p.getX(),p.getY());
  }
  if(closed){
      if(points.size() > 0){
          glVertex2f(points.at(0).getX(),points.at(0).getY());
      }
  }
  glEnd();

  //User-defined points
  glPointSize(5);
  glColor3f(1,0,0);
  glBegin(GL_POINTS);
  for(int i = 0; i < points.size(); i++){
      Point2 p = points.at(i);
      if(!p.isFixed()){
          glVertex2f(p.getX(),p.getY());
      }
  }
  glEnd();

  //Fixed points
  glPointSize(10);
  glColor3f(1,0,0);
  glBegin(GL_POINTS);
  for(int i = 0; i < points.size(); i++){
      Point2 p = points.at(i);
      if(p.isFixed()){
        glVertex2f(p.getX(),p.getY());
      }

  }
  glEnd();



  //Ref points
  glLineWidth(2);
  glColor3f(0,0,1);
  glBegin(GL_LINE_STRIP);
  for(int i = 0; i < refPoints.size(); i++){
      Point2 p = refPoints.at(i);
      glVertex2f(p.getX(), p.getY());
  }
  if(closed){
      if(refPoints.size() > 0){
          glVertex2f(refPoints.at(0).getX(),refPoints.at(0).getY());
      }
  }
  glEnd();



  //Curve
  glLineWidth(2);
  glColor3f(0,1,0);
  glBegin(GL_LINE_STRIP);
  for(int i = 0; i < curvePoints->size(); i++){
      Point2 p = curvePoints->at(i);
      glVertex2f(p.getX(), p.getY());
  }
  if(closed){
      if(curvePoints->size() > 0){
          glVertex2f(curvePoints->at(0).getX(),curvePoints->at(0).getY());
      }
  }
  glEnd();


  //Curve points
  glPointSize(5);
  glColor3f(0,1,0);
  glBegin(GL_POINTS);
  for(int i = 0; i < curvePoints->size(); i++){
      Point2 p = curvePoints->at(i);
      glVertex2f(p.getX(), p.getY());
      ugl::drawText(""+i,p.getX(),p.getY());
  }

  glEnd();

  glPopMatrix();
}

void GLView::drawChoice1() {

}

void GLView::paintGL() {
  /// clears the window
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


  /// choice example
  switch(_choice) {
    case 0:
      /// call the drawing method for the clicked button 0 ...
      drawChoice0();
      break;
    case 1:
      /// call the drawing method for the clicked button 1 ...
      drawChoice0();
      break;
  }

}

/** ********************************************************************** **/

void GLView::choice(int i,const string &s) {
  // i = button number, s = button text
  cout << "choice " << i << " " << s << endl;
  _choice=i;
  _choiceText=s;

  switch(_choice) {
    case 0:
      curve = new Chaikin();
      break;
    case 1:
      /// call the drawing method for the clicked button 1 ...
      curve = new FourPoint();

      break;
  }
}
