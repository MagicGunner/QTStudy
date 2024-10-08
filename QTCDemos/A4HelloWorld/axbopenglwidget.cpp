#include "axbopenglwidget.h"
unsigned int VBO, VAO, EBO;
unsigned int shaderProgram;
// float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};
// float vertices[] = {
//     // 第一个三角形
//     0.5f, 0.5f, 0.0f,   // 右上
//     0.5f, -0.5f, 0.0f,  // 右下
//     -0.5f, 0.5f, 0.0f,  // 左上
//     // 第二个三角形
//     0.5f, -0.5f, 0.0f,   // 右下
//     -0.5f, -0.5f, 0.0f,  // 左下
//     -0.5f, 0.5f, 0.0f    // 左上
// };

float vertices[] = {
    0.5f,  0.5f,  0.0f,  // 右上
    0.5f,  -0.5f, 0.0f,  // 右下
    -0.5f, 0.5f,  0.0f,  // 左上
    -0.5f, -0.5f, 0.0f,  // 左下
};
unsigned int indices[] = {
    0, 1, 2,  // 第一个三角形
    1, 2, 3   // 第二个三角形
};
const char *vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";
;
AXBOpenGLWidget::AXBOpenGLWidget(QWidget *parent) : QOpenGLWidget(parent) {}

void AXBOpenGLWidget::initializeGL() {
  this->initializeOpenGLFunctions();
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // 将数据传入显存
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  // 告知显卡如何解析
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                        (GLvoid *)0);
  // 开启VAO属性
  glEnableVertexAttribArray(0);

  // EBO
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);
  // 编译顶点着色器
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    qDebug() << "Error:\n" << infoLog;
  }
  // 编译片段着色器
  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    qDebug() << "Error:\n" << infoLog;
  }
  // link shaders
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    qDebug() << "Error:\n" << infoLog;
  }

  glUseProgram(shaderProgram);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  // 解绑
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // glDeleteShader(vertexShader);
  // glDeleteShader(fragmentShader);
}

void AXBOpenGLWidget::resizeGL(int w, int h) {}

void AXBOpenGLWidget::paintGL() {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glBindVertexArray(VAO);

  glUseProgram(shaderProgram);
  // glDrawArrays(GL_TRIANGLES, 0, 6);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 /*&indices*/);

  glBindVertexArray(0);
}
