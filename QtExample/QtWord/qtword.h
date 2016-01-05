#ifndef QTWORD_H
#define QTWORD_H

#include <QMainWindow>
class QMdiArea;
class QAction;
class QMenu;

class QtWord : public QMainWindow
{
    Q_OBJECT
public:
    QtWord(QWidget *parent = 0);
    ~QtWord();

private slots:
    void textAlign(QAction *a);

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



private:
    //创建系统动作的函数
    void createActions();
    //创建菜单
    void createMenus();
};


#endif // QTWORD_H
