#include "mygeomegry.h"

myGeomegry::myGeomegry(QWidget *parent)
    : QDialog(parent)
{
    //构造函数中完成控件的创建及初始化工作
    //设置窗口的标题
    setWindowTitle(tr("myPositionFuction"));

    //各控件的创建
    xLabel = new QLabel(tr("x():"));
    xValueLabel = new QLabel;
    yLabel = new QLabel(tr("y():"));
    yValueLabel = new QLabel;
    posLabel = new QLabel(tr("pos():"));
    posValueLabel = new QLabel;
    frameLabel = new QLabel(tr("frame:"));
    frameValueLabel = new QLabel;
    geoLabel = new QLabel(tr("geometry():"));
    geoValueLabel = new QLabel;
    widthLabel = new QLabel(tr("width():"));
    widthValueLabel = new QLabel;
    heightLabel = new QLabel(tr("height():"));
    heightValueLabel = new QLabel;
    rectLabel = new QLabel(tr("rect():"));
    rectValueLabel = new QLabel;

    //完成对窗口界面的布局
    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(xLabel, 0, 0);
    mainLayout->addWidget(xValueLabel, 0, 1);
    mainLayout->addWidget(yLabel, 1, 0);
    mainLayout->addWidget(yValueLabel, 1, 1);
    mainLayout->addWidget(posLabel, 2, 0);
    mainLayout->addWidget(posValueLabel, 2, 1);
    mainLayout->addWidget(frameLabel, 3, 0);
    mainLayout->addWidget(frameValueLabel, 3, 1);
    mainLayout->addWidget(geoLabel, 4, 0);
    mainLayout->addWidget(geoValueLabel, 4, 1);
    mainLayout->addWidget(widthLabel, 5, 0);
    mainLayout->addWidget(widthValueLabel, 5, 1);
    mainLayout->addWidget(heightLabel, 6, 0);
    mainLayout->addWidget(heightValueLabel, 6, 1);
    mainLayout->addWidget(rectLabel, 7, 0);
    mainLayout->addWidget(rectValueLabel, 7, 1);
    mainLayout->addWidget(sizeLabel, 8, 0);
    mainLayout->addWidget(sizeValueLabel, 8, 1);

    //完成窗口控件布局的创建之后，再利用updateLabel()函数获得
    //各位置函数的信息并显示出来
    updateLabel();

}

myGeomegry::~myGeomegry()
{

}


void myGeomegry::updateLabel()
{
    //获得x()函数的结果并显示
    QString xStr;
    xValueLabel->setText(xStr.setNum(x()));

    //获得y()函数的结果并显示
    QString yStr;
    yValueLabel->setText(yStr.setNum(y()));

    //获得pos()函数的结果并显示
    QString posStr;
    QString p1, p2;
    posStr = p1.setNum(pos().x()) + "," + p2.setNum(pos().y());
    posValueLabel->setText(posStr);

    //获得frameGeometry()函数的结果并显示
    QString fStr;
    QString f1, f2, f3, f4;
    fStr = f1.setNum(frameGeometry().x()) + "," +
            f2.setNum(frameGeometry().y()) + "," +
            f3.setNum(frameGeometry().width()) + ","+
            f4.setNum(frameGeometry().height());
    frameValueLabel->setText(fStr);

    //获得geometry()函数的结果并显示
    QString geoStr;
    QString g1, g2, g3, g4;
    geoStr = g1.setNum(geometry().x()) + "," +
            g2.setNum(geometry().y()) + "," +
            g3.setNum(geometry().width()) + "," +
            g4.setNum(geometry().height());
    geoValueLabel->setText(geoStr);

    //获得width()函数的结果并显示
    QString wStr;
    widthValueLabel->setText(wStr.setNum(width()));

    //获得height()函数的结果并显示
    QString hStr;
    heightValueLabel->setText(hStr.setNum(height()));

    //获得rect()函数的结果并显示
    QString rStr;
    QString r1, r2, r3, r4;
    rStr = r1.setNum(rect().x()) + "," +
            r2.setNum(rect().y()) + "," +
            r3.setNum(rect().width()) + "," +
            r4.setNum(rect().height());
    rectValueLabel->setText(rStr);

    //获得size()函数的结果并显示
    QString sStr;
    QString s1, s2;
    sStr = s1.setNum(size().width()) + "," +
            s2.setNum(size().height());
    sizeValueLabel->setText(sStr);

}

//重载moveEvent函数，响应对话框的移动事件，
//使得窗体在被移动时能够同步更新各函数的显示结果

void myGeomegry::moveEvent(QMoveEvent *)
{
    updateLabel();
}


//重载resizeEvent()函数，响应对话框的调整事件，
//使得在窗体大小发生改变时，能够同步更新各函数的显示结果
void myGeomegry::resizeEvent(QResizeEvent *)
{
    updateLabel();
}
