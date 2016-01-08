#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QWidget>
#include <QPen>
#include <QBrush>

class PaintArea : public QWidget
{
    Q_OBJECT
public:
    explicit PaintArea(QWidget *parent = 0);

    //声明一个枚举类型,列举了所有本实例可能用到的形状
    enum Shape{Line, Rectangle, RoundRect, Ellipse, Polygon, Polyline, Points,
               Arc, Path, Text, Pixmap};

    //声明setShape()函数用于设置形状
    void setShape(Shape);

    //声明setPen()函数用于设置画笔
    void setPen(QPen);

    //声明setBrush()函数用于设置画刷
    void setBrush(QBrush);

    //声明setFillRule()函数用于设置填充模式
    void setFillRule(Qt::FillRule);

    //重载重画事件paintEvent()函数
    void paintEvent(QPaintEvent *);

private:
    //声明表示各种属性的私有变量
    Shape shape;                //对应上面的枚举类型，也即相应的形状说明
    QPen pen;
    QBrush brush;
    Qt::FillRule fillRule;       //枚举类型，包括Qt::OddEvenFill和Qt::WindingFill两个枚举值

};

#endif
