//
// Created by JinNan on 2024/10/8.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "../Headers/mainwindow.h"
#include "ui_MainWindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    openGLWidget = new AXBOpenGLWidget(parent);
    setCentralWidget(openGLWidget);
}

MainWindow::~MainWindow() {
    delete ui;
}
