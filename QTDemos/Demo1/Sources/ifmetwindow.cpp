//
// Created by 29016 on 2024/9/24.
//

// You may need to build the project (run Qt uic code generator) to get "ui_IFmetWindow.h" resolved

#include "ifmetwindow.h"
#include "ui_IFmetWindow.h"


IFmetWindow::IFmetWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::IFmetWindow) {
    ui->setupUi(this);
}

IFmetWindow::~IFmetWindow() {
    delete ui;
}
