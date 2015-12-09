#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPoint>
#include <QPixmap>
#include <QBitmap>
#include <QMouseEvent>


class widget : public QWidget
{
    Q_OBJECT
public:
    widget(QWidget *parent = 0);
    ~widget();

    //重载鼠标按下和鼠标移动两个事件
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

    //重画函数完成在窗体上绘制图片的工作
    void paintEvent(QPaintEvent *);

private:
    //保存鼠标点相对窗体左上角的偏移值
    QPoint dragPosition;

};


#endif


