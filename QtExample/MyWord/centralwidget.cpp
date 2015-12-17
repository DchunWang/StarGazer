#include "CentralWidget.h"
#include <QHBoxLayout>

CentralWidget::CentralWidget(QWidget *parent) : QWidget(parent)
{
    //新建一个QLabel对象
    imageLabel = new QLabel;

    //下面这啥？
    imageLabel->setScaledContents(true);

    //新建一个QTextEdit对象
    text = new QTextEdit;

    //对中央窗体进行布局设置
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(imageLabel);
    mainLayout->addWidget(text);

}

CentralWidget::~CentralWidget()
{

}
