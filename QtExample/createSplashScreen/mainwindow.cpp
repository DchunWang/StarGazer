#include "mainwindow.h"
#include <QTextEdit>
#include <windows.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //设置窗体标题
    setWindowTitle(tr("mySplashScreen"));
    //新建一个文本框对象
    QTextEdit *edit = new QTextEdit;
    edit->setText(tr("This is a example of Splash Screen"));

    //设置主窗体对象
    setCentralWidget(edit);

    //重设窗体的大小
    resize(600, 600);

    //使主窗体程序在初始化时休眠几分钟
    Sleep(2000);

}

MainWindow::~MainWindow()
{

}
