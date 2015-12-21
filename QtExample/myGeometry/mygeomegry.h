#ifndef MYGEOMEGRY_H
#define MYGEOMEGRY_H

#include <QDialog>
#include <QLabel>
#include <QGridLayout>

class myGeomegry : public QDialog
{
    Q_OBJECT

public:
    myGeomegry(QWidget *parent = 0);
    ~myGeomegry();

    //完成获得各位置函数的信息并显示功能
    void updateLabel();

protected:
    //重载QWidget的moveEvent函数，响应对话框的移动事件，
    //使得窗体在被移动时能够同步更新各函数的显示结果
    void moveEvent(QMoveEvent *);
    //重载QWidget的resizeEvent()函数，响应对话框的大小调整事件,
    //使得在窗体大小发生改变时，也能够同步更新各函数的显示结果
    void resizeEvent(QResizeEvent *);

private:
    QLabel *xLabel;
    QLabel *xValueLabel;
    QLabel *yLabel;
    QLabel *yValueLabel;
    QLabel *posLabel;
    QLabel *posValueLabel;
    QLabel *frameLabel;
    QLabel *frameValueLabel;
    QLabel *geoLabel;
    QLabel *geoValueLabel;
    QLabel *widthLabel;
    QLabel *widthValueLabel;
    QLabel *heightLabel;
    QLabel *heightValueLabel;
    QLabel *rectLabel;
    QLabel *rectValueLabel;
    QLabel *sizeLabel;
    QLabel *sizeValueLabel;

    QGridLayout *mainLayout;

};

#endif // MYGEOMEGRY_H
