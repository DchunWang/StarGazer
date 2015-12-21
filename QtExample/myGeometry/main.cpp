#include "mygeomegry.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    myGeomegry w;
    w.show();

    return a.exec();
}
