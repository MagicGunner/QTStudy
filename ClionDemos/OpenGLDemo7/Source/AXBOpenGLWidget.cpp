//
// Created by JinNan on 2024/10/8.
//

#include "../Header/AXBOpenGLWidget.h"
#include <QTime>

unsigned int VBO, VAO, EBO;

float vertices[] = {
    // positions          // colors           // texture coords
    0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 2.0f, // top right
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 2.0f, -1.0f, // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, -1.0f, -1.0f, // bottom left
    -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, -1.0f, 2.0f // top left
};
unsigned int indices[] = {
    0, 1, 3, // 第一个三角形
    1, 2, 3 // 第二个三角形
};

AXBOpenGLWidget::AXBOpenGLWidget(QWidget *parent) : QOpenGLWidget(parent) {
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

void AXBOpenGLWidget::initializeGL() {
    this->initializeOpenGLFunctions();

    // 着色器
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/shaders.vert");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/shaders.frag");
    shaderProgram.link();
    if (const bool success = shaderProgram.bind(); !success) {
        qDebug() << shaderProgram.log();
    }
    texture0 = new QOpenGLTexture(QImage(":/Images/brickwall.jpg"));
    texture1 = new QOpenGLTexture(QImage(":/Images/awesomeface.png"));
    shaderProgram.setUniformValue("texture0", 0);
    shaderProgram.setUniformValue("texture1", 1);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 将数据传入显存
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 告知显卡如何解析
    // 告知属性aPos是如何布局
    const int posLocation = shaderProgram.attributeLocation("aPos");
    glVertexAttribPointer(posLocation, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          nullptr);
    // 告知属性aColor是如何布局
    const int colorLocation = shaderProgram.attributeLocation("aColor");
    glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          reinterpret_cast<GLvoid *>(3 * sizeof(float)));
    // 告知属性aTextCoord纹理坐标
    const int textCoordLocation = shaderProgram.attributeLocation("aTextCoord");
    glVertexAttribPointer(textCoordLocation, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          reinterpret_cast<GLvoid *>(6 * sizeof(float)));
    // 开启VAO属性
    glEnableVertexAttribArray(posLocation);
    glEnableVertexAttribArray(colorLocation);
    glEnableVertexAttribArray(textCoordLocation);

    // EBO
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                 GL_STATIC_DRAW);


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
    glClear(GL_COLOR_BUFFER_BIT);

    if (!isDraw) return;
    glBindVertexArray(VAO);

    if (const bool success = shaderProgram.bind(); !success) {
        qDebug() << shaderProgram.log();
    }
    texture0->bind(0);
    texture1->bind(1);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    float borderColor[] = {1.0f, 1.0f, 0.0f, 1.0f};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glDrawElements(shapeType, 6, GL_UNSIGNED_INT, nullptr); // 使用EBO
    glBindVertexArray(0);
}
