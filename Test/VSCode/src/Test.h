#pragma once
#include "ui_Test.h"
#include <QMainWindow>

class Test : public QMainWindow {
    Q_OBJECT
    
public:
    Test(QWidget* parent = nullptr);
    ~Test();

private:
    Ui_Test* ui;
};