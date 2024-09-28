//
// Created by JinNan on 2024/9/25.
//

// You may need to build the project (run Qt uic code generator) to get "ui_IfmetWindow.h" resolved

#include "Headers/ifmetwindow.h"
#include "Forms/ui_IfmetWindow.h"


IfmetWindow::IfmetWindow(QWidget *parent) :
    QWidget(parent), ui(new Ui::IfmetWindow) {
    ui->setupUi(this);
}

IfmetWindow::~IfmetWindow() {
    delete ui;
}
