#include <QtGui/QApplication>
#include "clientmain.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    clientMain w;
    w.show();
    return a.exec();
}
