//
// Created by JinNan on 2024/9/25.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ExWidget.h" resolved

#include "Headers/exwidget.h"
#include "Forms/ui_ExWidget.h"
#include <QMessageBox>
#include <QMetaProperty>
#include <QDebug>

ExWidget::ExWidget(QWidget *parent) : QWidget(parent), ui(new Ui::ExWidget) {
    ui->setupUi(this);

    m_boy = new ExPerson("Allen");
    m_boy->setProperty("score", 90);
    m_boy->setProperty("age", 20);
    m_boy->setProperty("sex", "boy");
    auto connection = connect(m_boy, &ExPerson::ageChanged, this, &ExWidget::onAgeChanged);

    m_girl = new ExPerson("MissBlue");
    m_girl->setProperty("score", 100);
    m_girl->setProperty("age", 20);
    m_girl->setProperty("sex", "girl");
    auto connection1 = connect(m_girl, &ExPerson::ageChanged, this, &ExWidget::onAgeChanged);

    ui->spinBoy->setProperty("isBoy", true);
    ui->spinGirl->setProperty("isGirl", true);

    auto connection2 = connect(ui->spinBoy, &QSpinBox::valueChanged, this, &ExWidget::onSpinValChanged);
    auto connection3 = connect(ui->spinGirl, &QSpinBox::valueChanged, this, &ExWidget::onSpinValChanged);

    auto connection4 = connect(ui->btnBoyAdd, &QPushButton::clicked, this, &ExWidget::onBtnBoyAdd);
    auto connection5 = connect(ui->btnGrilAdd, &QPushButton::clicked, this, &ExWidget::onBtnGirlAdd);
    auto connection6 = connect(ui->btnMetaObject, &QPushButton::clicked, this, &ExWidget::onClassInfo);
    auto connection7 = connect(ui->btnClear, &QPushButton::clicked, this, &ExWidget::onBtnClear);

    setWindowTitle(QObject::tr("元对象MetaObject和(含动态)属性Property的用法"));
}

ExWidget::~ExWidget() {
    delete ui;
}

void ExWidget::onAgeChanged(int val) {
    Q_UNUSED(val);

    auto *person = qobject_cast<ExPerson *>(sender());
    auto name = person->property("name").toString();
    auto sex = person->property("sex").toString();
    auto age = person->getAge();

    ui->textEdit->appendPlainText(name + "," + sex + QString::number(age));
}

void ExWidget::onSpinValChanged(int val) {
    Q_UNUSED(val);
    auto *spin = qobject_cast<QSpinBox *>(sender());
    if (spin->property("isBoy") == true) {
        m_boy->setAge(ui->spinBoy->value());
    } else {
        m_girl->setAge(ui->spinGirl->value());
    }
    QMessageBox::information(this, "提示", "触发了onSpinValChanged事件");
}

void ExWidget::onBtnClear() {
    ui->textEdit->clear();
    QMessageBox::information(this, "提示", "点击了onBtnClear按钮");
}

void ExWidget::onBtnBoyAdd() {
    m_boy->addAge();
    QMessageBox::information(this, "提示", "点击了onBtnBoyAdd按钮");
}

void ExWidget::onBtnGirlAdd() {
    m_girl->addAge();
    QMessageBox::information(this, "提示", "点击了onBtnGirlAdd按钮");
}

void ExWidget::onClassInfo() {
    if (ui == nullptr || ui->textEdit == nullptr) {
        qDebug() << "UI或textEdit未初始化!";
    } else {
        qDebug() << "UI和textEdit正确初始化!";
        // ui->textEdit->appendPlainText("==元对象信息(Meta Object)===");
    }

    // const QMetaObject *meta = m_boy->metaObject();
    // ui->textEdit->clear();
    // ui->textEdit->appendPlainText("==元对象信息(Meta Object)===");
    // ui->textEdit->appendPlainText(QString("类名称：%1\n").arg(meta->className()));
    // ui->textEdit->appendPlainText("属性(property)");
    //
    // for (int i = meta->propertyOffset(); i < meta->propertyCount(); i++) {
    //     auto prop = meta->property(i);
    //     const char *propName = prop.name();
    //     auto propValue = m_boy->property(propName).toString();
    //     ui->textEdit->appendPlainText(QString("属性名称=%1\n, 属性值=%2").arg(propName).arg(propValue));
    // }
    //
    // ui->textEdit->appendPlainText("");
    // ui->textEdit->appendPlainText("ClassInfo:");
    // for (int i = meta->classInfoOffset(); i < meta->classInfoCount(); i++) {
    //     auto classInfo = meta->classInfo(i);
    //     ui->textEdit->appendPlainText(QString("Name=%1, Value=%2").arg(classInfo.name()).arg(classInfo.value()));
    // }
    //
    // QMessageBox::information(this, "提示", "点击了onClassInfo按钮");
}
