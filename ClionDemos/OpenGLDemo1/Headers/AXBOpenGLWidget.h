//
// Created by JinNan on 2024/10/8.
//

#ifndef AXBOPENGLWIDGET_H
#define AXBOPENGLWIDGET_H

#include  <QOpenGLWidget>
#include <qopenglfunctions_3_3_core.h>

class AXBOpenGLWidget : public QOpenGLWidget, QOpenGLFunctions_3_3_Core {
    Q_OBJECT

public:
    explicit AXBOpenGLWidget(QWidget *parent = nullptr);

protected:
    void initializeGL() override;

    void resizeGL(int w, int h) override;

    void paintGL() override;
};


#endif //AXBOPENGLWIDGET_H
