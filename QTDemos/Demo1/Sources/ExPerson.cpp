//
// Created by JinNan on 2024/9/25.
//
#include "Headers/ExPerson.h"

ExPerson::ExPerson(const QString &name, QObject *parent) : QObject(parent) {
    m_name = name;
}

int ExPerson::getAge() {
    return m_age;
}

void ExPerson::setAge(const int age) {
    m_age = age;
    emit ageChanged(m_age);
}

void ExPerson::addAge() {
    m_age++;
    emit ageChanged(m_age);
}
