
/**

  @author F. Aubert
  **/


#include "GLView.h"
#include <iostream>
#include <QPushButton>
#include "blob.h"
#include "softobject.h"
#include "implicitcircle.h"


using namespace std;
using namespace prog3d;


/// ctor
GLView::GLView(QWidget *parent) : QGLWidget(parent) {

  setFocusPolicy(Qt::StrongFocus); // this widget can now catch the keyboard events

  _choice=1;
  xResolution = 10.0;
  yResolution = 10.0;
}


/// dtor
GLView::~GLView() {
    delete implicit;
    delete grid;
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
  if (event->button()==Qt::LeftButton) {
    cout << "left mouse : " << event->x() << "," << event->y() << endl;
  }
  if (event->button()==Qt::RightButton) {
    cout << "right mouse : " << event->x() << "," << event->y() << endl;
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
    case Qt::Key_F:
        cout << "Toggle fill surface" << endl;
        grid->toggleFillSurface();
      break;
    case Qt::Key_V:
        cout << "Toggle show values" << endl;
        grid->toggleDrawValues();
      break;
    case Qt::Key_P:
        cout << "Toggle show surface points" << endl;
        grid->toggleDrawSurfacePoints();
      break;
    case Qt::Key_Plus:
        cout << "Increase resolution" << endl;
        xResolution+=1.0;
        yResolution+=1.0;
        grid->setResolution(xResolution, yResolution);
      break;
    case Qt::Key_Minus:
        cout << "Decrease resolution" << endl;
        xResolution-=1.0;
        yResolution-=1.0;
        grid->setResolution(xResolution, yResolution);
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

  glColor3f(0,0.5,1);

  glPushMatrix();

  grid->draw();

  glPopMatrix();
}


//Blob animation
void GLView::drawChoice1() {
    glColor3f(0,0.5,1);

    glPushMatrix();

    double k = 1.0;
    Point2 force = Point2(0.0, 0.0);
    double l0 = 0.4;

    for(int i = 0; i < implicit->getObjects().size(); i++){
        ImplicitObject *iObject = implicit->getObject(i);

        for(int j = 0; j < implicit->getObjects().size(); j++){
            if(i != j){
                ImplicitObject *jObject = implicit->getObject(j);
                Point2 jCenter = jObject->getCenter();
                Point2 iCenter = iObject->getCenter();
                double module = iCenter.distance(jCenter);
                Point2 ventre = iCenter-jCenter;
                Point2 vem = ventre / module;
                double fac = -k*(module-l0);
                Point2 vf = vem*fac;
                force = force+vf;
            }
        }
        Point2 speed = iObject->getSpeed();
        Point2 newSpeed = speed+force;
        iObject->setSpeed(newSpeed);
        Point2 center = iObject->getCenter();
        Point2 speedStep = speed*0.01;
        Point2 newCenter = center+speedStep;
        iObject->setCenter(newCenter);
    }

    grid->draw();

    glPopMatrix();
}

void GLView::drawChoice2() {
    glColor3f(0,0.5,1);

    glPushMatrix();

    ImplicitObject *b = implicit->getObject(0);
    Point2 center = b->getCenter();
    Point2 c = Point2(center.getX()*1.01, center.getY()*1.01);
    b->setCenter(c);

    grid->draw();

    glPopMatrix();
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
      drawChoice1();
      break;
    case 2:
      drawChoice2();
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
        implicit = new ImplicitCircle();

        break;
    case 1:{
        implicit = new Implicit();
        Blob *blob = new Blob (Point2(0.3,0.3), 1.0, 2.5, 4.0);
        implicit->addObject(*blob);
        Blob *blob2 = new Blob (Point2(-0.3,-0.3), 1.0, 2.5, 4.0);
        implicit->addObject(*blob2);

        break;
    }
    case 2 :{
        implicit = new Implicit();
        SoftObject *b = new SoftObject (Point2(0.3,0.3), 1.0);
        implicit->addObject(*b);
        SoftObject *b2 = new SoftObject (Point2(-0.3,-0.3), 1.0);
        implicit->addObject(*b2);
        SoftObject *b3 = new SoftObject (Point2(-0.3,0.3), 1.0);
        implicit->addObject(*b3);

        break;
}
    default:
        break;
    }

    grid = new Grid(xResolution, yResolution, implicit);

}

