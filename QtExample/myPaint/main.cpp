#include "mainwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFont font("ZYSong18030", 14);
    a.setFont(font);

    MainWidget w;
    w.show();

    return a.exec();
}
