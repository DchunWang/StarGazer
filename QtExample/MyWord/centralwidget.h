#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>
#include <QImage>
#include <QTextEdit>
#include <QLabel>


class CentralWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CentralWidget(QWidget *parent = 0);

    //中央窗体中的主要元素
    QImage image;
    QLabel *imageLabel;     //用于放置图片
    QTextEdit *text;        //文本编辑框

    ~CentralWidget();

};


#endif





