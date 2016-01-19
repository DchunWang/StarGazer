#include "pixitem.h"

PixItem::PixItem(QPixmap *pixmap)
{
    //只是初始化变量
    pix = *pixmap;
}

//定义图元边界函数，完成以图元坐标系为基础增加两个像素点的冗余的工作
QRectF PixItem::boundingRect() const
{
    return QRectF(-2-pix.width()/2, -2-pix.height()/2, pix.width() - 4, pix.height()+4);
}

void PixItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-pix.width()/2, -pix.height()/2, pix);
}



