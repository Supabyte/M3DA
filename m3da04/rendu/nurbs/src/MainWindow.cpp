#include <iostream>

#include "GLView.h"

#include "MainWindow.h"

#include <QGLFormat>
#include <QGridLayout>
#include <QTimer>
#include <QKeyEvent>
#include <QPushButton>
#include <QLineEdit>
#include <QSignalMapper>

#include <QDebug>

#include "Error.h"

using namespace std;

/*!
*
* @file
*
* @brief
* @author F. Aubert
*
*/


MainWindow::MainWindow() :
  QMainWindow(NULL) {

  // build a GLWidget
  QGLFormat format=QGLFormat();
  //format.setVersion(2,1); // there's a bug somewhere for the compatibility profile on AMD driver
  format.setProfile(QGLFormat::CompatibilityProfile);
  format.setSwapInterval(1);
  format.setOption(QGL::DoubleBuffer | QGL::DepthBuffer | QGL::StencilBuffer | QGL::AlphaChannel);
//  QGLFormat::setDefaultFormat(format);

  GLView *glApplication=new GLView(this);

  // application buttons
  QPushButton *choice1=new QPushButton("draw Nkp Ex1-Q4 (choice1)");
  QPushButton *choice2=new QPushButton("draw Bspline Ex1-Q9 (choice2)");
  QPushButton *choice3=new QPushButton("animate Ex1-Q10 (choice3)");
  QPushButton *choice4=new QPushButton("non uniform Ex1-Q11 (choice4)");
  QPushButton *choice5=new QPushButton("open uniform Ex1-Q12 (choice5)");
  QPushButton *choice6=new QPushButton("Clear");
  QWidget *weightLE=new QLineEdit("1");
  weightLE->setMaximumWidth(100);
  QPushButton *choice7=new QPushButton("Set weight");
  QWidget *degreeLE=new QLineEdit("2");
  degreeLE->setMaximumWidth(100);
  QPushButton *choice8=new QPushButton("Set degree");

  // set up for the main window : set a central widget (main container), and set a gridLayout to this central widget
  QWidget *central=new QWidget(this);
  this->setCentralWidget(central);
  QGridLayout *layout=new QGridLayout(central);



  // add widgets in layout
  layout->addWidget(choice1,0,0);
  layout->addWidget(choice2,1,0);
  layout->addWidget(choice3,2,0);
  layout->addWidget(choice4,3,0);
  layout->addWidget(choice5,4,0);
  layout->addWidget(choice6,5,0);
  layout->addWidget(weightLE,6,0);
  layout->addWidget(choice7,7,0);
  layout->addWidget(degreeLE,8,0);
  layout->addWidget(choice8,9,0);
  layout->addWidget(glApplication,0,1,20,20);

  //Signal mapper to send an argument to the set weight and degree button listeners
  QSignalMapper* weightSignalMapper = new QSignalMapper (glApplication) ;
  QSignalMapper* degreeSignalMapper = new QSignalMapper (glApplication) ;

  // connect events
  connect(choice1,SIGNAL(clicked()),glApplication,SLOT(choice1()));
  connect(choice2,SIGNAL(clicked()),glApplication,SLOT(choice2()));
  connect(choice3,SIGNAL(clicked()),glApplication,SLOT(choice3()));
  connect(choice4,SIGNAL(clicked()),glApplication,SLOT(choice4()));
  connect(choice5,SIGNAL(clicked()),glApplication,SLOT(choice5()));
  connect(choice6,SIGNAL(clicked()),glApplication,SLOT(choice6()));
  connect(choice7,SIGNAL(clicked()),weightSignalMapper,SLOT(map()));
  connect(choice8,SIGNAL(clicked()),degreeSignalMapper,SLOT(map()));

  weightSignalMapper->setMapping(choice7,weightLE);
  degreeSignalMapper->setMapping(choice8,degreeLE);

  connect (weightSignalMapper, SIGNAL(mapped(QWidget*)), glApplication, SLOT(choice7(QWidget*))) ;
  connect (degreeSignalMapper, SIGNAL(mapped(QWidget*)), glApplication, SLOT(choice8(QWidget*))) ;

  // update GLWidget every 20ms
  QTimer *timer=new QTimer(this);
  connect(timer,SIGNAL(timeout()),glApplication,SLOT(updateData())); // call glApplication->update() (that will call paintGL() )
  timer->start(0);

}


// key events
void MainWindow::keyPressEvent(QKeyEvent *e) {
  if (e->key()==Qt::Key_Escape) {
    this->close();
  }
  else {
    QWidget::keyPressEvent(e); // send the event to the parent widget
  }
}

