#ifndef MYWORD_H
#define MYWORD_H

#include <QMainWindow>
#include <QImage>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QComboBox>
#include <QSpinBox>
#include <QToolBar>
#include <QFontComboBox>
#include <QToolButton>
#include <QTextCharFormat>
#include "CentralWidget.h"
#include <QPrinter>
#include <QPrintDialog>
#include <QTextEdit>



class MyWord : public QMainWindow
{
    Q_OBJECT

public:
    MyWord(QWidget *parent = 0);
    ~MyWord();

    //创建动作的函数
    void createActions();
    //创建菜单的函数
    void createMenus();
    //创建工具栏的函数
    void createToolBars();

    //加载文件的函数
    void loadFile(QString filename);
    //合并文本的字符格式的函数，也即将新的格式应用到光标选取内的字符
    void mergeFormat(QTextCharFormat);

private:
    //拥有的四个菜单栏
    QMenu *fileMenu;        //文件菜单
    QMenu *editMenu;        //编辑菜单
    QMenu *rotateMenu;      //旋转菜单
    QMenu *mirrorMenu;      //镜像菜单

    QImage img;             //做啥用？？
    QString filename;       //做啥用？？

    //文件菜单下拉时所拥有的一系列动作命令
    QAction *openFileAction;        //打开文件
    QAction *newFileAction;         //新建文件
    QAction *printTextAction;       //打印文本
    QAction *printImageAction;      //打印图片
    QAction *exitAction;            //退出程序

    //编辑菜单下拉时所拥有的动作命令
    QAction *copyAction;            //复制
    QAction *cutAction;             //剪切
    QAction *pasteAction;           //粘贴
    QAction *aboutAction;           //关于
    QAction *zoomInAction;          //放大图片
    QAction *zoomOutAction;         //缩小图片

    //旋转菜单的动作命令
    QAction *rotate90Action;        //旋转90度
    QAction *rotate180Action;       //旋转180度
    QAction *rotate270Action;       //旋转270度

    //镜像菜单的动作命令
    QAction *mirrorVerticalAction;  //垂直镜像
    QAction *mirrorHorizontalAction;//水平镜像
    QAction *undoAction;            //撤回不做？
    QAction *redoAction;            //重做

    //工具栏
    QToolBar *fileTool;             //文件工具栏，对应文件菜单中的命令
    QToolBar *editTool;             //编辑工具栏，对应编辑菜单中的命令
    QToolBar *rotateTool;           //旋转工具栏
    QToolBar *mirrorTool;           //镜像工具栏
    QToolBar *doToolBar;            //


    //自己补充的内容
    CentralWidget *Cent;





    //添加一系列的槽函数，完成命令动作的相应功能
protected slots:
    void showNewFile();
    void showOpenFile();
    void showPrintText();
    void showPrintImage();

    void showZoomIn();
    void showZoomOut();

    void showRotate90();
    void showRotate180();
    void showRotate270();

    void showMirrorVertical();
    void showMirrorHorizontal();

    //////////////////////////////////////////////////////////////

    //实现文本编辑
private:

    //字体设置项
    QLabel *fontLabel1;
    QFontComboBox *fontComboBox;
    QLabel *fontLabel2;
    QComboBox *sizeComboBox;

    QToolButton *boldBtn;
    QToolButton *italicBtn;
    QToolButton *underlineBtn;
    QToolButton *colorBtn;

    //字体工具栏
    QToolBar *fontToolBar;

    /////////////////////////////////////////////////////////////////

    //实现排版功能

    //排序设置项
    QLabel *listLabel;
    QComboBox *listComboBox;
    QActionGroup *actionGroup;
    QAction *leftAction;
    QAction *rightAction;
    QAction *centerAction;
    QAction *justifyAction;

    //要添加排序工具栏
    QToolBar *listToolBar;


protected slots:
    //字体组合框
    void showFontComboBox(QString comboStr);
    //字体大小调整
    void showSizeSpinBox(QString spinValue);
    //字体加粗
    void showBoldBtn();
    //斜体
    void showItalicBtn();
    //下划线
    void showUnderlineBtn();
    //字体颜色
    void showColorBtn();
    //改变字体格式
    void showCurrentFormatChanged(const QTextCharFormat &);


    //////////////////////////////////////////////////////////////
    void showList(int);
    void showAlignment(QAction *);
    void showCursorPositionChanged();

};

#endif // MYWORD_H
