#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "paintarea.h"
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QSpinBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QGradient>

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();

private:
    //主窗口类继承自QWidget类，包含完成各种图形参数选择
    //的控制区的声明，一系列设置与画图相关参数的槽函数的
    //声明，以及一个绘图区PaintArea对象的声明
    PaintArea *paintArea;
    QLabel *shapeLabel;
    QComboBox *shapeComboBox;
    QLabel *penColorLabel;
    QFrame *penColorFrame;
    QPushButton *changeBtn;
    QLabel *penWidthLabel;
    QSpinBox *penWidthSpinBox;
    QLabel *penStyleLabel;
    QComboBox *penStyleComboBox;
    QLabel *penCapLabel;
    QComboBox *penCapComboBox;
    QLabel *penJoinLabel;
    QComboBox *penJoinComboBox;
    QLabel *fillStyleLabel;
    QComboBox *fillStyleComboBox;
    QLabel *spreadLabel;
    QComboBox *spreadComboBox;
    QGradient::Spread spread;
    QLabel *brushColorLabel;
    QFrame *brushColorFrame;
    QPushButton *changeBtn2;
    QLabel *brushStyleLabel;
    QComboBox *brushStyleComboBox;
    QGridLayout *rightLayout;
    QHBoxLayout *mainLayout;

private slots:
    void showShape(int);
    void showPenColor();
    void showPenWidth(int);
    void showPenStyle(int);
    void showPenCap(int);
    void showPenJoin(int);
    void showFillStyle();
    void showSpread();
    void showBrushColor();
    void showBrush(int);
};

#endif // MAINWIDGET_H
