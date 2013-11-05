#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


/*!
*
* @file
*
* @brief
* @author F. Aubert
*
*/

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  explicit MainWindow();
  

  void keyPressEvent(QKeyEvent *e);

  QSize sizeHint() const {return QSize(1000,1000);}

signals:
  
public slots:

};

#endif // MAINWINDOW_H
