#include "helpermainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    helperMainWindow w;
    w.show();
    return a.exec();
}
