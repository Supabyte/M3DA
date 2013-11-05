/**

  @author F. Aubert
  **/


#include "GLView.h"
#include <iostream>
#include "nurbs.cpp"

using namespace std;
using namespace prog3d;

/// ctor
GLView::GLView(QWidget *parent) : QGLWidget(parent) {

  setFocusPolicy(Qt::StrongFocus); // this widget can now catch the keyboard events
  degree = 2;
  points.clear();
  choice = 0;
  animStep = 0;
  weight = 1;
  highlighThreshold = 25;
  highlighted = -1;

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
  this->width = width;
  this->height = height;
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
    double x = event->x();
    double y = event->y();


    //Point selection
    Vector2 v = Vector2(event->x(), event->y());
    double min = 999; //TODO real max value
    double current = 0.0;
    //We check all points to see which one is closest to the click
    //TODO check this algo is not too heavy
    for(int i = 0; i < points.size(); i++){
        Vector3 p = points.at(i);
        current = p.distance(v);
        if(current < min){
            min = current;
            highlighted = i;
        }
    }
    //If the closest one is close enough, it is selected
    if(min > highlighThreshold){
        highlighted = -1;
        //If we are showing the non-uniform the nodal vector is fixed,
        //so more than 4 points will cause an overflow
        if(!( (choice == 5 || choice == 4) && points.size() >= 4)){
            points.push_back(Vector3( x, y, weight));
        }
    }

    //Grab point mode ON
    grabbing = true;

  }
  if (event->button()==Qt::RightButton) {
    cout << "right mouse : " << event->x() << "," << event->y() << endl;
  }
}

void GLView::mouseMoveEvent(QMouseEvent *event) {
  cout << "motion : " << event->x() << "," << event->y() << endl;
  if(grabbing && highlighted != -1){
      Vector3 *p = &(points.at(highlighted));
      p->setX(event->x());
      p->setY(event->y());
  }
}

void GLView::mouseReleaseEvent(QMouseEvent *event) {
  switch(event->button()){
  case Qt::LeftButton:
      cout << "left mouse released" << endl;
      //Grab point mode OFF
      grabbing = false;
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
    case Qt::Key_Z:
        cout << "Z pressed" << endl;
        degree++;
      break;
    case Qt::Key_S:
        cout << "S pressed" << endl;
        degree--;
        if(degree < 1)
            degree = 1;
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



void GLView::paintGL() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        Nurbs *nurbs = this->generateNurbs();
    switch (choice){
    case 1:
        glColor3f(0,0,0);
        ugl::drawText("Draw NKP",0.05,0.02);
        ugl::drawText("Click to add points",0.05,0.08);
        this->drawNKP(nurbs);
        break;
    case 2:
        glColor3f(0,0,0);
        ugl::drawText("Draw Spline",0.05,0.02);
        ugl::drawText("Click to add, select or grab points",0.05,0.08);
        this->drawSpline(nurbs);
        break;
    case 3:
        this->drawAnimation(nurbs);
        break;
    case 4:
        if(points.size() > 4){
            points.clear();
            degree = 2;
            nurbs = this->generateNurbs();
        }

        glColor3f(0,0,0);
        ugl::drawText("Non-uniform with hard-coded vector [0,1,2,4,7,8,9]",0.05,0.02);
        ugl::drawText("(degree cannot be changed, 4 control points needed)",0.05,0.08);
        this->drawNonUniform(nurbs);
        break;
    case 5:
        if(points.size() > 4){
            points.clear();
            degree = 2;
            nurbs = this->generateNurbs();
        }
        glColor3f(0,0,0);
        ugl::drawText("Open non-uniform with hard-coded vector [0,0,0,1,2,2,2]",0.05,0.02);
        ugl::drawText("(degree cannot be changed, 4 control points needed)",0.05,0.08);
        this->drawOpenUniform(nurbs);
        break;
    case 6:
        points.clear();
        choice = -1;
        break;
    default:
        glColor3f(0,0,0);
        ugl::drawText("Choose an option",0.05,0.02);
        break;
    }    

}

/** ********************************************************************** **/

void GLView::choice1() {
  cout << "choice 1 " << endl;
  choice = 1;

}
void GLView::choice2() {
  cout << "choice 2 " << endl;
  choice = 2;

}
void GLView::choice3() {
  cout << "choice 3 " << endl;
  choice = 3;
  animStep = degree;
}
void GLView::choice4() {
  cout << "choice 4 " << endl;
  choice = 4;
}
void GLView::choice5() {
  cout << "choice 5 " << endl;
  choice = 5;
}
void GLView::choice6() {
  cout << "Clear! " << endl;
  choice = 6;
}
void GLView::choice7(QWidget *e) {
  double w = ((QLineEdit*)e)->text().toDouble();
  cout << "Weight: " << w << endl;
  if(highlighted != -1){
      Vector3 *p = &(points.at(highlighted));
      p->setZ(w);
  }
}
void GLView::choice8(QWidget *e) {
    if(choice != 4 && choice != 5){
        degree = ((QLineEdit*)e)->text().toInt();
        cout << "Degree: " << degree << endl;
    }
}

//E1Q3
void GLView::drawN(int k, int p, Nurbs *nurbs){

    glPushMatrix();

    glColor3f(1,0,0);


    glColor3f(0,1,0);
    glBegin(GL_LINE_STRIP);

    double x = 0.0;
    for(double i = 0; i < 6; i += .1){
        double y = nurbs->evaluate(k,p,i);
        glVertex2f(x, y);
        x += .01;
    }

    glEnd();

    glPopMatrix();
}

//E1Q4
void GLView::drawNKP(Nurbs *nurbs){

    glOrtho(-1,1,-1,1,-1,1);

    glPointSize(10);
    glColor3f(0,0,1);
    glBegin(GL_POINTS);

    double x = 0.0;
    for(int i = 0; i < nurbs->getControlPoints().size()+degree; i++){
        glVertex2f(x, 0);
        x += .1;
    }
    glEnd();

    for(int i = 0; i < points.size(); i++){
        drawN(i, degree, nurbs);
    }

    this->drawControlPolygon(nurbs);

}

//E1Q9
void GLView::drawSpline(Nurbs *nurbs){

    glOrtho(-1,1,-1,1,-1,1);

    glPointSize(10);
    glColor3f(0,0,1);
    glBegin(GL_LINE_STRIP);

    for(double i = nurbs->getP(nurbs->getDegree()); i <= nurbs->getP(nurbs->getControlPoints().size()); i += .1){
        Vector2 v = nurbs->evalBSpline(i);
        glVertex2f(v.getX(), v.getY());
    }

    glEnd();

    //Control polygon
    this->drawControlPolygon(nurbs);

}

//E1Q10
void GLView::drawAnimation(Nurbs *nurbs){

    this->drawSpline(nurbs);
    this->drawNKP(nurbs);

    glColor3f(1,0,1);
    //Animated point
    glBegin(GL_POINTS);
    Vector2 anim = nurbs->evalBSpline(animStep);
    glVertex2f(anim.getX(), anim.getY());
    glVertex2f(animStep/10 , 0.0);

    animStep += 0.01;
    if(animStep > nurbs->getControlPoints().size()){
        animStep = nurbs->getDegree();
    }


    glEnd();


}
//E1Q11
void GLView::drawNonUniform(Nurbs *nurbs){

    glOrtho(-1,1,-1,1,-1,1);

    std::vector<double> vec;
    vec.push_back(0);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(4);
    vec.push_back(7);
    vec.push_back(8);
    vec.push_back(9);
    nurbs->setNodalVector(vec);

    glColor3f(0,0,1);
    glBegin(GL_LINE_STRIP);

    double x = 0.0;
    for(double i = nurbs->getP(nurbs->getDegree()); i <= nurbs->getP(nurbs->getControlPoints().size()); i += .1){
        Vector2 v = nurbs->evalBSpline(i);
        glVertex2f(v.getX(), v.getY());
    }

    glEnd();

    //Control polygon
    this->drawControlPolygon(nurbs);

}


//E1Q12
void GLView::drawOpenUniform(Nurbs *nurbs){

    glOrtho(-1,1,-1,1,-1,1);

    std::vector<double> vec;
    vec.push_back(0);
    vec.push_back(0);
    vec.push_back(0);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(2);
    vec.push_back(2);
    nurbs->setNodalVector(vec);


    glColor3f(0,0,1);
    glBegin(GL_LINE_STRIP);

    for(double i = nurbs->getP(nurbs->getDegree()); i <= nurbs->getP(nurbs->getControlPoints().size()); i += .1){
        Vector2 v = nurbs->evalBSpline(i);
        glVertex2f(v.getX(), v.getY());
    }

    glEnd();

    //Control polygon
    this->drawControlPolygon(nurbs);

}

Nurbs* GLView::generateNurbs(){
    Nurbs *nurbs = new Nurbs();

    std::vector<Vector3> pts = nurbs->toNurbsCoords(points, width, height);
    nurbs->initialize(degree, pts);

    return nurbs;
}

void GLView::drawControlPolygon(Nurbs *n){

    glColor3f(1,0,0);
    glBegin(GL_LINE_STRIP);

    for(int i = 0; i < n->getControlPoints().size(); i++){
        Vector3 v = n->getControlP(i);
        glVertex2f(v.getX(), v.getY());
    }
    glEnd();

    this->drawPoints(n->getControlPoints());
}

void GLView::drawPoints(std::vector<Vector3> pts){
    glPointSize(10);
    glColor3f(0,1,0);
    glBegin(GL_POINTS);

    for(int i = 0; i < pts.size(); i++){

        if(i == highlighted){
            glColor3f(0,0,1);
        }
        Vector3 v = pts.at(i);
        glVertex2f(v.getX(), v.getY());
        glColor3f(0,1,0);
    }
    glEnd();
}
