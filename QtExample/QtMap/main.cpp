#include "mainwindow.h"
#include <QApplication>
#include <QFont>
#include "mapwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFont f("ARRL KaitiM GB", 14);
    f.setBold(true);
    a.setFont(f);
    MapWidget mapWdget;
    mapWdget.show();

    return a.exec();
}
