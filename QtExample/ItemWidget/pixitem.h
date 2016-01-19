#ifndef PIXITEM_H
#define PIXITEM_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>
#include <QWidget>

class PixItem : public QGraphicsItem
{
public:
    PixItem(QPixmap *pixmap);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);

private :
    //作为图元显示的图片
    QPixmap pix;
};

#endif // PIXITEM_H
