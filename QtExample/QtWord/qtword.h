#ifndef QTWORD_H
#define QTWORD_H

#include <QMainWindow>
class QMdiArea;
class QAction;
class QMenu;
#include "mychild.h"
#include <QComboBox>
#include <QFontComboBox>
#include <QMdiSubWindow>
#include <QSignalMapper>
#include <QPrintDialog>
#include <QPrinter>
#include <QPrintPreviewDialog>
#include <QColor>
#include <QColorDialog>

class QtWord : public QMainWindow
{
    Q_OBJECT
public:
    QtWord(QWidget *parent = 0);
    ~QtWord();

    //活动窗口
    MyChild *activeMyChild();
    //信号映射器
    QSignalMapper *windowMapper;

private slots:
    void textAlign(QAction *a);
    void about();

    //新建文件操作
    void fileNew();
    //创建子窗口
    MyChild *createMyChild();
    //更新菜单
    void updateMenus();
    //更新窗口菜单
    void updateWindowMenu();

    //打开文件
    void fileOpen();

    //保存文件
    void fileSave();
    void fileSaveAs();

    //剪切复制粘贴等操作
    void undo();
    void redo();
    void cut();
    void copy();
    void paste();

    //字体格式设置
    void textBold();
    void textItalic();
    void textUnderline();

    void textFamily(const QString &f);
    void textSize(const QString &p);

    void textColor();

    void textStyle(int styleIndex);

    //文件打印功能
    void filePrint();
    void filePrintPreview();
    void printPreview(QPrinter *);

    //自己补充
    void setActiveSubWindow(QWidget *);

private:
    QMdiArea *mdiArea;

    //”文件“菜单
    QMenu *fileMenu;
    //“编辑”菜单
    QMenu *editMenu;
    //“格式”菜单
    QMenu *formatMenu;
    //“格式”的子菜单
    QMenu *fontMenu;
    QMenu *alignMenu;
    //“窗口”菜单
    QMenu *windowMenu;
    //“帮助”菜单
    QMenu *helpMenu;


    //“文件”菜单各功能项
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *printAct;
    QAction *printPreviewAct;
    QAction *exitAct;

    //“编辑”菜单各功能项
    QAction *undoAct;
    QAction *redoAct;
    QAction *cutAct;
    QAction *copyAct;
    QAction *pasteAct;

    //“格式”菜单各功能项
    QAction *boldAct;
    QAction *italicAct;
    QAction *underlineAct;
    QAction *leftAlignAct;
    QAction *centerAct;
    QAction *rightAlignAct;
    QAction *justifyAct;
    QAction *colorAct;

    //“窗口”菜单各功能项
    QAction *closeAct;
    QAction *closeAllAct;
    QAction *tileAct;
    QAction *cascadeAct;
    QAction *nextAct;
    QAction *previousAct;
    QAction *separatorAct;

    //“帮助”菜单各功能项
    QAction *aboutAct;
    QAction *aboutQtAct;

    /////////////////////////////////////////////////////
    //各工具条及其上子控件的指针

    //”文件“工具条
    QToolBar *fileToolBar;
    //”编辑“工具条
    QToolBar *editToolBar;
    //”格式“工具条
    QToolBar *formatToolBar;
    //字体组合选择工具条
    QToolBar *comboToolBar;
    //标号与编号类型选择框
    QComboBox *styleComboBox;
    //字体选择框
    QFontComboBox *fontComboBox;
    //字号选择框
    QComboBox *sizeComboBox;


    /////////////////////////////////////////////////////////



private:
    //创建系统动作的函数
    void createActions();
    //创建菜单
    void createMenus();
    //创建工具栏
    void createToolBars();
    //创建状态栏
    void createStatusBar();
    //使格式菜单及其对应的各工具按钮变为可用状态
    void enabledText();


    //查找子窗口
    QMdiSubWindow *findMyChild(const QString &fileName);

protected:
    void closeEvent(QCloseEvent *event);


};


#endif // QTWORD_H
