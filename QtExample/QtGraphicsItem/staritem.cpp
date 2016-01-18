#include "staritem.h"

StarItem::StarItem()
{
    //构造函数仅完成读取图片信息的工作
    pix.load("star.png");
}

//定义图元的边界函数boundingRect(),这个是所有自定义的图元都必须实现的函数
QRectF StarItem::boundingRect() const
{
    return QRectF(-pix.width()/3, -pix.height()/3, pix.width(), pix.height());
}

//自定义图元的重绘函数
void StarItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *widget)
{
    painter->drawPixmap(boundingRect().topLeft(), pix);
}

