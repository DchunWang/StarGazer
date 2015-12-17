
#include "myword.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //设置显示的字体格式
    QFont fon("ZYSong18030", 12);
    a.setFont(fon);
    MyWord w;
    w.show();

    return a.exec();
}
