//
// Created by JinNan on 2024/10/8.
//

#ifndef AXBOPENGLWIDGET_H
#define AXBOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <qopenglfunctions_3_3_core.h>
#include <QOpenGLShaderProgram>
#include <QTimer>

class AXBOpenGLWidget : public QOpenGLWidget, QOpenGLFunctions_3_3_Core {
    Q_OBJECT

public:
    explicit AXBOpenGLWidget(QWidget *parent = nullptr);

    void drawRectangle();

    void clearPaint();

    void setPolygonMode(bool isPolygon);

protected:
    void initializeGL() override;

    void resizeGL(int w, int h) override;

    void paintGL() override;

private:
    bool isDraw = false;
    int shapeType = GL_TRIANGLES;
    QOpenGLShaderProgram shaderProgram;
    QTimer timer;
};


#endif //AXBOPENGLWIDGET_H
