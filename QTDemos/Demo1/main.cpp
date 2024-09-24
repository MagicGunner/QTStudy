
#include <ui_IFmetWindow.h>
#include "ifmetwindow.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    IFmetWindow w;
    w.show();
    return QApplication::exec();
}
