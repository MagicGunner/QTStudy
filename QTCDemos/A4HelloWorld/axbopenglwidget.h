#ifndef AXBOPENGLWIDGET_H
#define AXBOPENGLWIDGET_H

#include <qopenglfunctions_3_3_core.h>

#include <QOpenGLWidget>

class AXBOpenGLWidget : public QOpenGLWidget, QOpenGLFunctions_3_3_Core {
  Q_OBJECT
 public:
  explicit AXBOpenGLWidget(QWidget* parent = nullptr);

 protected:
  virtual void initializeGL();
  virtual void resizeGL(int w, int h);
  virtual void paintGL();
};

#endif  // AXBOPENGLWIDGET_H
