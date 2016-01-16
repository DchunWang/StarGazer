#include "drawer.h"
#include <QGroupBox>
#include <QVBoxLayout>

Drawer::Drawer(QWidget *parent, Qt::WindowFlags f)
    : QToolBox(parent, f)
{
    //设置主窗体标题
    setWindowTitle(tr("QtQQ 2016"));
    //设置主窗体标题栏图标
    setWindowIcon(QPixmap(":/images/NO1.png"));

    //创建一个QToolButton类实例，对应抽屉中的一个按钮
    toolBtn1 = new QToolButton;
    //设置按钮的文字
    toolBtn1->setText(tr("张惠康"));
    //设置按钮图标
    toolBtn1->setIcon(QPixmap(":/images/NO2.png"));
    //设置按钮的大小与图标的大小相同
    toolBtn1->setIconSize(QPixmap(":images/NO2.png").size());
    //设置当鼠标离开时，按钮自动恢复成弹起状态
    toolBtn1->setAutoRaise(true);
    //设置按钮的文字显示在图标旁边
    toolBtn1->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    toolBtn2 = new QToolButton;
    toolBtn2->setText(tr("徐爽"));
    toolBtn2->setIcon(QPixmap(":/images/NO3.png"));
    toolBtn2->setIconSize(QPixmap(":/images/NO3.png").size());
    toolBtn2->setAutoRaise(true);
    toolBtn2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    toolBtn3 = new QToolButton;
    toolBtn3->setText(tr("张泽鹏"));
    toolBtn3->setIcon(QPixmap(":/images/NO4.png"));
    toolBtn3->setIconSize(QPixmap(":/images/NO4.png").size());
    toolBtn3->setAutoRaise(true);
    toolBtn3->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    toolBtn4 = new QToolButton;
    toolBtn4->setText(tr("陈记臣"));
    toolBtn4->setIcon(QPixmap(":/images/NO5.png"));
    toolBtn4->setIconSize(QPixmap(":/images/NO5.png").size());
    toolBtn4->setAutoRaise(true);
    toolBtn4->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    toolBtn5 = new QToolButton;
    toolBtn5->setText(tr("黄庆忠"));
    toolBtn5->setIcon(QPixmap(":/images/NO6.png"));
    toolBtn5->setIconSize(QPixmap(":/images/NO6.png").size());
    toolBtn5->setAutoRaise(true);
    toolBtn5->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    toolBtn6 = new QToolButton;
    toolBtn6->setText(tr("wangdch"));
    toolBtn6->setIcon(QPixmap(":/images/NO7.png"));
    toolBtn6->setIconSize(QPixmap(":/images/NO7.png").size());
    toolBtn6->setAutoRaise(true);
    toolBtn6->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    toolBtn7 = new QToolButton;
    toolBtn7->setText(tr("肖秀荣"));
    toolBtn7->setIcon(QPixmap(":/images/NO8.png"));
    toolBtn7->setIconSize(QPixmap(":/images/NO8.png").size());
    toolBtn7->setAutoRaise(true);
    toolBtn7->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    toolBtn8 = new QToolButton;
    toolBtn8->setText(tr("藏楚晓"));
    toolBtn8->setIcon(QPixmap(":/images/NO9.png"));
    toolBtn8->setIconSize(QPixmap(":/images/NO9.png").size());
    toolBtn8->setAutoRaise(true);
    toolBtn8->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    //将聊天窗口显示函数与相对应的用户按钮绑定
    connect(toolBtn1, SIGNAL(clicked()), this, SLOT(showChatWidget1()));
    connect(toolBtn2, SIGNAL(clicked()), this, SLOT(showChatWidget2()));
    connect(toolBtn3, SIGNAL(clicked()), this, SLOT(showChatWidget3()));
    connect(toolBtn4, SIGNAL(clicked()), this, SLOT(showChatWidget4()));
    connect(toolBtn5, SIGNAL(clicked()), this, SLOT(showChatWidget5()));
    connect(toolBtn6, SIGNAL(clicked()), this, SLOT(showChatWidget6()));
    connect(toolBtn7, SIGNAL(clicked()), this, SLOT(showChatWidget7()));
    connect(toolBtn8, SIGNAL(clicked()), this, SLOT(showChatWidget8()));


    //创建一个QGroupBox类实例，对应抽屉“群成员"
    QGroupBox *groupBox = new QGroupBox;

    //创建一个QVBoxLayout类实例，用来设置抽屉内个按钮的布局
    QVBoxLayout *layout = new QVBoxLayout(groupBox);
    //设置布局中各窗体的显示间距
    layout->setMargin(20);
    //设置布局中各窗体的显示位置
    layout->setAlignment(Qt::AlignLeft);

    //将个按钮加入抽屉内
    layout->addWidget(toolBtn1);
    layout->addWidget(toolBtn2);
    layout->addWidget(toolBtn3);
    layout->addWidget(toolBtn4);
    layout->addWidget(toolBtn5);
    layout->addWidget(toolBtn6);
    layout->addWidget(toolBtn7);
    layout->addWidget(toolBtn8);

    //插入一个占位符
    layout->addStretch();

    this->addItem((QWidget *) groupBox, tr("宿舍"));
}

void Drawer::showChatWidget1()
{
    //以按钮toolBtn1的文本为用户名创建一个Widget类的实例，对应于一个聊天窗口
    chatWidget1 = new Widget(0,toolBtn1->text());
    //设置聊天窗的标题文字（为对应用户图片按钮的文本
    chatWidget1->setWindowTitle(toolBtn1->text());
    //设置聊天窗的窗口图标（为对应用户按钮上的图片，即用户头像
    chatWidget1->setWindowIcon(toolBtn1->icon());
    //显示聊天窗口
    chatWidget1->show();
}

void Drawer::showChatWidget2()
{
    chatWidget2 = new Widget(0,toolBtn2->text());
    chatWidget2->setWindowTitle(toolBtn2->text());
    chatWidget2->setWindowIcon(toolBtn2->icon());
    chatWidget2->show();
}

void Drawer::showChatWidget3()
{
    chatWidget3 = new Widget(0,toolBtn3->text());
    chatWidget3->setWindowTitle(toolBtn3->text());
    chatWidget3->setWindowIcon(toolBtn3->icon());
    chatWidget3->show();
}

void Drawer::showChatWidget4()
{
    chatWidget4 = new Widget(0,toolBtn4->text());
    chatWidget4->setWindowTitle(toolBtn4->text());
    chatWidget4->setWindowIcon(toolBtn4->icon());
    chatWidget4->show();
}

void Drawer::showChatWidget5()
{
    chatWidget5 = new Widget(0, toolBtn5->text());
    chatWidget5->setWindowTitle(toolBtn5->text());
    chatWidget5->setWindowIcon(toolBtn5->icon());
    chatWidget5->show();
}

void Drawer::showChatWidget6()
{
    chatWidget6 = new Widget(0, toolBtn6->text());
    chatWidget6->setWindowTitle(toolBtn6->text());
    chatWidget6->setWindowIcon(toolBtn6->icon());
    chatWidget6->show();
}

void Drawer::showChatWidget7()
{
    chatWidget7 = new Widget(0, toolBtn7->text());
    chatWidget7->setWindowTitle(toolBtn7->text());
    chatWidget7->setWindowIcon(toolBtn7->icon());
    chatWidget7->show();
}

void Drawer::showChatWidget8()
{
    chatWidget8 = new Widget(0, toolBtn8->text());
    chatWidget8->setWindowTitle(toolBtn8->text());
    chatWidget8->setWindowIcon(toolBtn8->icon());
    chatWidget8->show();
}



