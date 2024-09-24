//
// Created by 29016 on 2024/9/24.
//

#ifndef IFMETWINDOW_H
#define IFMETWINDOW_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class IFmetWindow; }
QT_END_NAMESPACE

class IFmetWindow : public QMainWindow {
Q_OBJECT

public:
    explicit IFmetWindow(QWidget *parent = nullptr);
    ~IFmetWindow() override;

private:
    Ui::IFmetWindow *ui;
};


#endif //IFMETWINDOW_H
