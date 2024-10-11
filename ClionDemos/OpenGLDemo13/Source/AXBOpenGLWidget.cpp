//
// Created by JinNan on 2024/10/8.
//

#include "../Header/AXBOpenGLWidget.h"
#include <QTime>
#include <QKeyEvent>
#include <cmath>

unsigned int VBO, VAO, EBO;
float mixValue = 0.5f;
float fov = 45;
QMatrix4x4 model, view, projection;
float vertices[] = {
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

    -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
};

QVector cubePositions = {
    QVector3D(0.0f, 0.0f, 0.0f),
    QVector3D(2.0f, 5.0f, -15.0f),
    QVector3D(-1.5f, -2.2f, -2.5f),
    QVector3D(-3.8f, -2.0f, -12.3f),
    QVector3D(2.4f, -0.4f, -3.5f),
    QVector3D(-1.7f, 3.0f, -7.5f),
    QVector3D(1.3f, -2.0f, -2.5f),
    QVector3D(1.5f, 2.0f, -2.5f),
    QVector3D(1.5f, 0.2f, -1.5f),
    QVector3D(-1.3f, 1.0f, -1.5f)
};

QVector3D cameraPos(0.0f, 0.0f, 3.0f);
QVector3D cameraFront(0.0f, 0.0f, -1.0f);

AXBOpenGLWidget::AXBOpenGLWidget(QWidget *parent) : QOpenGLWidget(parent) {
    setFocusPolicy(Qt::StrongFocus);
    timer.setInterval(200);
    timer.start();
    elapsedTimer.start();
    auto connection = connect(&timer, &QTimer::timeout, [this] {
        update();
    });
}

AXBOpenGLWidget::~AXBOpenGLWidget() {
    delete texture0;
    delete texture1;
    makeCurrent();
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    doneCurrent();
}

void AXBOpenGLWidget::drawRectangle() {
    shapeType = GL_TRIANGLES;
    isDraw = true;
    update();
}

void AXBOpenGLWidget::clearPaint() {
    isDraw = false;
    update();
}

void AXBOpenGLWidget::setPolygonMode(const bool isPolygon) {
    makeCurrent();
    if (isPolygon) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    doneCurrent();
    update();
}

float deltaTime;
float lastTime;

void AXBOpenGLWidget::keyPressEvent(QKeyEvent *event) {
    const auto currentTime = static_cast<float>(elapsedTimer.elapsed());
    deltaTime = currentTime - lastTime;
    deltaTime = deltaTime <= 50 ? deltaTime : 50;
    lastTime = currentTime;
    const float cameraSpeed = 0.002f * deltaTime;

    QVector3D up(0.0f, 1.0f, 0.0f);
    QVector3D cameraRight = QVector3D::crossProduct(cameraFront, up);
    switch (event->key()) {
        case Qt::Key_Up:
            if (mixValue + 0.1f > 1.0f)
                mixValue = 1.0f;
            else
                mixValue = 0.1f + mixValue;
            break;
        case Qt::Key_Down:
            if (mixValue - 0.1f < 0.0f)
                mixValue = 0.0f;
            else
                mixValue = mixValue - 0.1f;
            break;
        case Qt::Key_W:
            cameraPos += cameraSpeed * cameraFront;
            break;
        case Qt::Key_S:
            cameraPos -= cameraSpeed * cameraFront;
            break;
        case Qt::Key_A:
            cameraPos += cameraSpeed * cameraRight;
            break;
        case Qt::Key_D:
            cameraPos -= cameraSpeed * cameraRight;
            break;
        default: ;
    }
    makeCurrent();
    bool bind = shaderProgram.bind();
    shaderProgram.setUniformValue("mixValue", mixValue);
    doneCurrent();
    update();
}

void AXBOpenGLWidget::mouseMoveEvent(QMouseEvent *event) {
    static QPoint deltaPos;
    static QPoint lastPos;
    static float yaw = -90;
    static float pitch = 0;
    const auto currentPos = event->pos();
    deltaPos = currentPos - lastPos;
    if (abs(deltaPos.x()) > 50 || abs(deltaPos.y()) > 50) deltaPos = QPoint(0, 0);
    lastPos = currentPos;
    constexpr float sensitivity = 0.1f;
    deltaPos *= sensitivity;
    yaw += static_cast<float>(deltaPos.x());
    pitch -= static_cast<float>(deltaPos.y());
    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;
    cameraFront.setX(static_cast<float>(cos(yaw * M_PI / 180) * cos(pitch * M_PI / 180)));
    cameraFront.setY(static_cast<float>(sin(pitch * M_PI / 180)));
    cameraFront.setZ(static_cast<float>(sin(yaw * M_PI / 180) * cos(pitch * M_PI / 180)));
    cameraFront.normalize();
    update();
}

void AXBOpenGLWidget::wheelEvent(QWheelEvent *event) {
    fov -= static_cast<float>(event->angleDelta().y()) / 120;
    if (fov <= 1.0f) fov = 1.0f;
    if (fov >= 75.0f) fov = 75.0f;
    makeCurrent();
    projection.setToIdentity();
    projection.perspective(fov, static_cast<float>(width() / height()), 0.1f, 100.0f);
    shaderProgram.setUniformValue("Projection", projection);
    doneCurrent();
    update();
}

void AXBOpenGLWidget::initializeGL() {
    this->initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);

    // 着色器
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/shaders.vert");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/shaders.frag");
    shaderProgram.link();
    if (const bool success = shaderProgram.bind(); !success) {
        qDebug() << shaderProgram.log();
    }
    texture0 = new QOpenGLTexture(QImage(":/Images/container.jpg"));
    texture1 = new QOpenGLTexture(QImage(":/Images/awesomeface.png"));
    shaderProgram.setUniformValue("texture0", 0);
    shaderProgram.setUniformValue("texture1", 1);
    shaderProgram.setUniformValue("mixValue", mixValue);

    projection.perspective(fov, static_cast<float>(width()) / static_cast<float>(height()), 0.1f, 100.0f
    );
    shaderProgram.setUniformValue("Projection", projection);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 将数据传入显存
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 告知显卡如何解析
    // 告知属性aPos是如何布局
    const int posLocation = shaderProgram.attributeLocation("aPos");
    glVertexAttribPointer(posLocation, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          nullptr);
    // 告知属性aTextCoord纹理坐标
    const int textCoordLocation = shaderProgram.attributeLocation("aTextCoord");
    glVertexAttribPointer(textCoordLocation, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          reinterpret_cast<GLvoid *>(3 * sizeof(float)));
    // 开启VAO属性
    glEnableVertexAttribArray(posLocation);
    glEnableVertexAttribArray(textCoordLocation);


    texture0->bind(0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    texture1->bind(1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // 解绑  使用EBO时放在这里
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void AXBOpenGLWidget::resizeGL(int w, int h) {
    QOpenGLWidget::resizeGL(w, h);
}

void AXBOpenGLWidget::paintGL() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (!isDraw) return;
    glBindVertexArray(VAO);

    if (const bool success = shaderProgram.bind(); !success) {
        qDebug() << shaderProgram.log();
    }
    texture0->bind(0);
    texture1->bind(1);

    view.setToIdentity();
    view.lookAt(cameraPos, cameraPos + cameraFront, QVector3D(0.0f, 1.0f, 0.0f));
    shaderProgram.setUniformValue("View", view);


    for (auto i = 0; i < cubePositions.count(); i++) {
        auto position = cubePositions[i];
        model.setToIdentity();
        model.translate(position);
        model.rotate(45, 1.0f, 0.2f, 5.0f);
        shaderProgram.setUniformValue("Model", model);
        glDrawArrays(shapeType, 0, 36);
    }

    glBindVertexArray(0);
}
