#ifndef DRAWER_H
#define DRAWER_H

#include <QToolBox>
#include <QToolButton>
#include "widget.h"
#include  <QWidget>

/*主界面以一组带图片的按钮的形式在“抽屉盒”中列出，当然，
 * 这里的群成员都是事先确定的就是。单击抽屉盒里的某个
 * 按钮，弹出相应成员用户的聊天窗口
 */


class Drawer : public QToolBox
{
    Q_OBJECT
public:
    Drawer(QWidget *parent = 0, Qt::WindowFlags f = 0);

private:
    //定义了九个QToolButton控件，对应群里的九个成员用户
    QToolButton *toolBtn1;
    QToolButton *toolBtn2;
    QToolButton *toolBtn3;
    QToolButton *toolBtn4;
    QToolButton *toolBtn5;
    QToolButton *toolBtn6;
    QToolButton *toolBtn7;
    QToolButton *toolBtn8;
    //QToolButton *toolBtn9;

    //群里8个用户各自对应的聊天串口对象的指针，聊天窗对象为Widget类型
    Widget *chatWidget1;
    Widget *chatWidget2;
    Widget *chatWidget3;
    Widget *chatWidget4;
    Widget *chatWidget5;
    Widget *chatWidget6;
    Widget *chatWidget7;
    Widget *chatWidget8;


private slots:
    //显示各个用户聊天窗的函数
    void showChatWidget1();
    void showChatWidget2();
    void showChatWidget3();
    void showChatWidget4();
    void showChatWidget5();
    void showChatWidget6();
    void showChatWidget7();
    void showChatWidget8();


};

#endif
