#include "paintarea.h"
#include <QPalette>
#include <QPainter>

PaintArea::PaintArea(QWidget *parent)
    : QWidget(parent)
{
    //构造函数主要是玩成初始化工作，设置图形显示区域的背景色
    //及最小尺寸

    //新建一个QPalette对象
    QPalette p;
    //设置该QPalette对象的背景色为白色
    p.setColor(QPalette::Window, Qt::white);
    //将此QPalette对象设置本窗体PaintArea类的主面板
    setPalette(p);

    /*上面的三条语句其实可以用一条语句替代
     * setPalette(QPalette(Qt::white));
     * 只是为了更好地显示其具体功能及创建方式而特意写成
     * 了三条语句的形式，方便理解
     */


    //设置自动填充背景
    setAutoFillBackground(true);

    //设置窗体的最小尺寸大小
    setMinimumSize(400, 400);
}

/*下面这些函数通过改变画图区域的私有变量，
 * 再通过update()函数触发重画事件paintEvent(),
 * 使得其设置能够及时显现出来.
 * 而主窗体也是通过在其槽函数中直接调用PaintArea->setShape()等函数
 * 而达到对画图区图形的设置。
 * */
void PaintArea::setShape(Shape s)
{
    shape = s;
    update();
}

void PaintArea::setPen(QPen p)
{
    pen = p;
    update();
}

void PaintArea::setBrush(QBrush b)
{
    brush = b;
    update();
}

void PaintArea::setFillRule(Qt::FillRule rule)
{
    fillRule = rule;
    update();
}

//重画事件paintEvent()函数
void PaintArea::paintEvent(QPaintEvent *)
{
    //新建一个 QPinter对象
    QPainter p(this);
    //设置QPainter对象的画笔
    p.setPen(pen);
    //设置该QPainter对象的画刷
    p.setBrush(brush);

    //新建一个QRect对象，设定一个长方形区域，
    //为画长方形、圆角矩形、椭圆等做准备
    QRect rect(50, 100, 300, 200);

    //创建一个QPoint的数组，包含四个点，
    //为画多边形、多边线及点等做准备
    static const QPoint points[4] =
    {
        QPoint(150, 100),QPoint(300, 150), QPoint(350, 250), QPoint(100,300)

    };

    //设置画弧形的起始角和跨度角
    //注意用QPainter画弧形时，其所用的角度值是以1/16度为单位的，所以画弧时，1度用16来表示
    //也即要乘以16
    int startAngle = 30 * 16;
    int spanAngle = 120 * 16;

    //新建一个QPaintPath对象，为画路径做准备
    QPainterPath path;
    //给该QPainterPath加入一个方形
    path.addRect(150, 150, 100, 100);
    //给该QPainterPath对象的当前点移动到下一部分图形的起点
    path.moveTo(100, 100);
    //让该QPainterPath对象绘制贝塞尔曲线
    path.cubicTo(300, 100, 200, 200, 300, 300);
    path.cubicTo(100, 300, 200, 200, 100, 100);

    path.setFillRule(fillRule);

    /*利用switch语句，对所要画的形状进行判断，调用QPainter的各个相应的draw()函数
     * 完成对图形的绘制。
     * 另外，绘制图形有两种方式，
     * 一种是利用QPainter绘制图形
     * 另一种是利用QPainterPath绘制简单图形
     * */

    switch(shape)
    {
    case Line :                         //绘制直线
        p.drawLine(rect.topLeft(), rect.bottomRight()); break;
    case Rectangle:                     //绘制长方形
        p.drawRect(rect); break;
    case RoundRect:                     //绘制圆角矩形
        p.drawRoundRect(rect); break;
    case Ellipse:                       //绘制椭圆形
        p.drawEllipse(rect); break;
    case Polygon:                       //绘制多边形
        p.drawPolygon(points, 4); break;
    case Polyline:                      //绘制多边线
        p.drawPolyline(points, 4); break;
    case Points:                        //绘制点
        p.drawPoints(points, 4); break;
    case Arc:                           //绘制弧
        p.drawArc(rect, startAngle, spanAngle); break;
    case Path:                          //绘制路径
        p.drawPath(path); break;
    case Text:                          //绘制文字
        p.drawText(rect, Qt::AlignCenter, tr("Hello Qt!")); break;
    case Pixmap:                        //绘制图片
        p.drawPixmap(150, 150, QPixmap("myPic.png")); break;
    default:
        break;

    }

}
