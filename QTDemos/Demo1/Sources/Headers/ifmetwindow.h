//
// Created by JinNan on 2024/9/25.
//

#ifndef IFMETWINDOW_H
#define IFMETWINDOW_H

#include <QWidget>


QT_BEGIN_NAMESPACE

namespace Ui {
    class IfmetWindow;
}

QT_END_NAMESPACE

class IfmetWindow : public QWidget {
    Q_OBJECT

public:
    explicit IfmetWindow(QWidget *parent = nullptr);

    ~IfmetWindow() override;

private:
    Ui::IfmetWindow *ui;
};


#endif //IFMETWINDOW_H
