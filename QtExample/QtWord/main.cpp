#include "qtword.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtWord w;
    w.show();

    return a.exec();
}
