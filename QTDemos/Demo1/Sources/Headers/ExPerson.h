//
// Created by JinNan on 2024/9/25.
//

#ifndef EXPERSON_H
#define EXPERSON_H
#include <QObject>

class ExPerson : public QObject {
    Q_OBJECT

    // 类的附加信息
    Q_CLASSINFO("Author", "MissBlue")
    Q_CLASSINFO("Version", "1.0.0")
    Q_CLASSINFO("Info", "QT6 Meta Object and Property Example")

    // 属性定义
    Q_PROPERTY(int age READ getAge WRITE setAge NOTIFY ageChanged)
    Q_PROPERTY(QString name MEMBER m_name)
    Q_PROPERTY(int score MEMBER m_score)

public:
    explicit ExPerson(const QString &name, QObject *parent = nullptr);

    int getAge();

    void setAge(int age);

    void addAge();

signals:
    void ageChanged(int age);

private:
    int m_age = 5;
    QString m_name;
    int m_score = 50;
};
#endif //EXPERSON_H
