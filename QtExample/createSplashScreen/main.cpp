#include "mainwindow.h"
#include <QApplication>
#include  <QPixmap>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    //创建一个QApplication对象
    QApplication a(argc, argv);

    //创建一个QPixmap对象，设置启动图片
    QPixmap pic("myPic.png");
    //利用QPixmap对象创建一个QSplashScreen对象
    QSplashScreen screen(pic);
    //显示启动图片
    screen.show();
    //使程序在显示启动画面的同时仍能响应鼠标等其它事件
    a.processEvents();
    //正常创建主窗体对象，并调用show()函数将其显示
    MainWindow w;
    w.show();

    //主窗体对象初始化完成后，结束启动画面
    screen.finish(&w);

    return a.exec();
}
