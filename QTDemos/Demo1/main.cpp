
#include <QApplication>

#include "Headers/exwidget.h"
#include "Headers/mainwindow.h"
#include "Headers/ifmetwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    ExWidget w;
    w.show();
    return QApplication::exec();
}
