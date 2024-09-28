//
// Created by JinNan on 2024/9/25.
//

#ifndef EXWIDGET_H
#define EXWIDGET_H

#include <QWidget>
#include "ExPerson.h"

QT_BEGIN_NAMESPACE

namespace Ui {
    class ExWidget;
}

QT_END_NAMESPACE

class ExWidget : public QWidget {
    Q_OBJECT

public:
    explicit ExWidget(QWidget *parent = nullptr);

    ~ExWidget() override;

private slots:
    void onAgeChanged(int val);

    void onSpinValChanged(int val);

    void onBtnClear();

    void onBtnBoyAdd();

    void onBtnGirlAdd();

    void onClassInfo();

private:
    Ui::ExWidget *ui;

    ExPerson *m_boy;
    ExPerson *m_girl;
};


#endif //EXWIDGET_H
