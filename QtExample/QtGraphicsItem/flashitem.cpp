#include "flashitem.h"

FlashItem::FlashItem(QObject *parent) : QObject(parent)
{
    //为颜色切换标识赋初值
    flash = true;
    //设置图元的属性，ItemIsMovable表示此图元是可移动的，可用鼠标进行拖曳操作
    setFlag(ItemIsMovable);
    //启动一个定时器，以1000毫秒为时间间隔
    startTimer(1000);
}

//自定义图元重绘函数
void FlashItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                      QWidget *widget)
{
    //闪烁图元的阴影区不绘制边线
    painter->setPen(Qt::NoPen);
    //闪烁图元的阴影区的阴影画刷颜色为深灰色
    painter->setBrush(Qt::darkGray);
    //绘制阴影区
    painter->drawEllipse(-7, -7, 40, 40);
    //闪烁区的椭圆边线颜色为黑色、线宽为0
    painter->setPen(QPen(Qt::black, 0));
    //设置闪烁区的椭圆画刷颜色根据颜色切换标识flash来决定在椭圆中填充哪种颜色，
    //颜色在红色和黄色之间选择
    painter->setBrush(flash?(Qt::red) : (Qt::yellow));
    //绘制与阴影区同样形状和大小的椭圆，并错开一定的距离实现立体的效果
    painter->drawEllipse(-10, -10, 40, 40);
}

//定时器响应函数timeEvent()完成颜色切换标识的反置，并在每次反置
//后调用update()函数重绘图元以实现闪烁的效果
void FlashItem::timerEvent(QTimerEvent *)
{
    flash = !flash;
    update();
}

QRectF FlashItem::boundingRect() const
{
    qreal adjust = 2;
    return QRectF(-10-adjust, -10-adjust, 43+adjust, 43+adjust);
}

