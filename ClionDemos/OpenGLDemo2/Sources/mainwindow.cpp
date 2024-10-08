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

    auto _ = connect(ui->actionDraw, &QAction::triggered, this, &drawTriggered);
    _ = connect(ui->actionClear, &QAction::triggered, this, &clearTriggered);
    _ = connect(ui->actionSetPolygonMode, &QAction::toggled, this, &polygonModeToggled);
}


MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::drawTriggered() const {
    openGLWidget->drawRectangle();
}

void MainWindow::clearTriggered() const {
    openGLWidget->clearPaint();
}

void MainWindow::polygonModeToggled(bool isToggled) const {
    if (isToggled) {
        openGLWidget->setPolygonMode(true);
    } else {
        openGLWidget->setPolygonMode(false);
    }
}
