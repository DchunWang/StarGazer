#include "widget.h"


widget::widget(QWidget *parent)
    : QWidget(parent)
{
    //新建一个QPixmap对象
    QPixmap pix;

    //调用QPixmap的load函数为QPixmap对象填入图像值
    pix.load("mypic.png", 0, Qt::AvoidDither | Qt::ThresholdDither | Qt::ThresholdAlphaDither);

    //重设主窗体的尺寸为所读取的图片的大小
    resize(pix.size());

    //为调用它的控件增加一个遮罩，遮住所选区域以外的部分使之看起来是透明的
    setMask(QBitmap(pix.mask()));
}

widget::~widget()
{

}

//重载鼠标按下事件
void widget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
    if(event->button() == Qt::RightButton)
    {
        close();
    }
}

//重载鼠标移动事件
void widget::mouseMoveEvent(QMouseEvent  *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        move(event->globalPos() - dragPosition);
        event->accept();
    }
}

void widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap("mypic.png"));
}


//主函数
#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    widget w;
    w.show();

    return a.exec();
}
