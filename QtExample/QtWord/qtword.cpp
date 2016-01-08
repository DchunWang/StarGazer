#include "qtword.h"
#include <QtWidgets>


//const QString rsrcPath = ":/win";


QtWord::QtWord(QWidget *parent)
    : QMainWindow(parent)
{
    mdiArea = new QMdiArea;
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(mdiArea);

    move(200, 150);
    resize(800, 500);
    setWindowTitle(tr("Qt Word"));

    //自己添加的部分，可删，待测试
    createActions();
    createMenus();

}

QtWord::~QtWord()
{

}

//实现动作的函数createActions()
void QtWord::createActions()
{

    ////////////////////////////////////////////////////////////////////////////
    //“文件“菜单动作集
    newAct = new QAction(QIcon("fileNew.png"), tr("新建(&N)"),this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setToolTip("新建");
    newAct->setStatusTip(tr("创建一个新文档"));
    //connect(newAct, SIGNAL(triggered()), this, SLOT(fileNew()));

    openAct = new QAction(QIcon("fileOpen.png"), tr("打开(&O)..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setToolTip("打开");
    openAct->setStatusTip(tr("打开已存在的文档"));
    //connect(openAct, SIGNAL(triggered()), this, SLOT(fileOpen()));

    saveAct = new QAction(QIcon("fileSave.png"), tr("保存(&S)"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setToolTip("保存");
    saveAct->setStatusTip(tr("将当前文件存盘"));
    //connect(savaAct, SIGNAL(triggered()), this, SLOT(fileSave()));

    saveAsAct = new QAction(QIcon("fileSaveAs.png"),tr("另存为(&A)..."), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(tr("一个新名字保存文档"));
    //connect(saveAsAct, SIGNAL(triggered()), this, SLOT(fileSaveAs()));

    printAct = new QAction(QIcon("filePrint.png"), tr("打印(&P)..."), this);
    printAct->setShortcuts(QKeySequence::Print);
    printAct->setToolTip("打印");
    printAct->setStatusTip(tr("打印文档"));
    //connect(printAct, SIGNAL(triggered()), this, SLOT(filePrint()));

    printPreviewAct = new QAction(QIcon("fileprintPre.png"),tr("打印预览..."), this);
    printPreviewAct->setStatusTip(tr("预览打印效果"));
    //connect(printPriviewAct, SIGNAL(triggered()), this, SLOT(filePrintPreview()));

    exitAct = new QAction(QIcon("exit.png"),tr("退出(&X)"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("退出应用程序"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(closeAllWindows()));


    /////////////////////////////////////////////////////////////////////////////////////
    //“编辑”菜单动作集
    undoAct = new QAction(QIcon("editUndo.png"), tr("撤销(&U)"), this);
    undoAct->setShortcuts(QKeySequence::Undo);
    undoAct->setToolTip("撤销");
    undoAct->setStatusTip(tr("撤销当前动作"));

    redoAct = new QAction(QIcon("editRedo.png"), tr("重做(&R)"),this);
    redoAct->setShortcuts(QKeySequence::Redo);
    redoAct->setToolTip("重做");
    redoAct->setStatusTip(tr("恢复之前操作"));

    cutAct = new QAction(QIcon("editCut.png"), tr("剪切(&T)"), this);
    cutAct->setShortcuts(QKeySequence::Cut);
    cutAct->setToolTip("剪切");
    cutAct->setStatusTip(tr("从文档中裁剪所选内容，并将其放入剪贴板"));
    //connect(cutAct, SIGNAL(triggered()), this, SLOT(cut()));

    copyAct = new QAction(QIcon("editCopy.png"), tr("复制"), this);
    copyAct->setShortcuts(QKeySequence::Copy);
    copyAct->setToolTip("复制");
    copyAct->setStatusTip(tr("复制所选内容，并将其放入剪贴板"));
    //connect(copyAct, SIGNAL(triggered()), this, SLOT(copy()));

    pasteAct = new QAction(QIcon("editPaste.png"), tr("粘贴"), this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    pasteAct->setToolTip("粘贴");
    pasteAct->setStatusTip(tr("将剪贴板的内容粘贴到文档"));
    //connect(pasteAct, SIGNAL(triggered()), this, SLOT(paste()));


    //////////////////////////////////////////////////////////////////////////////////////
    //”格式“菜单动作集
    boldAct = new QAction(QIcon("bold.png"), tr("加粗(&B)"), this);
    boldAct->setCheckable(true);
    boldAct->setShortcut(Qt::CTRL + Qt::Key_B);
    boldAct->setToolTip("加粗");
    boldAct->setStatusTip(tr("将所选文字加粗"));
    QFont bold;
    bold.setBold(true);
    boldAct->setFont(bold);
    //connect(boldAct, SIGNAL(triggered()), this, SLOT(textBold()));

    italicAct = new QAction(QIcon("italic.png"), tr("斜体(&I)"), this);
    italicAct->setCheckable(true);
    italicAct->setShortcut(Qt::CTRL + Qt::Key_I);
    italicAct->setToolTip("斜体");
    italicAct->setStatusTip(tr("将所选文字用斜体显示"));
    QFont italic;
    italic.setItalic(true);
    italicAct->setFont(italic);
    //connect(italicAct, SIGNAL(triggered()), this, SLOT(textItalic()));

    underlineAct = new QAction(QIcon("underline.png"), tr("下划线(&U)"), this);
    underlineAct->setCheckable(true);
    underlineAct->setShortcut(Qt::CTRL +Qt::Key_U);
    underlineAct->setToolTip("下划线");
    underlineAct->setStatusTip(tr("为所选文字加下划线"));
    QFont underline;
    underline.setUnderline(true);
    underlineAct->setFont(underline);
    //connect(underlineAct, SIGNAL(triggered()),  this, SLOT(textUnderline()));

    //“格式”-“段落”子菜单下的各项为同一个菜单项组，只能选中其中一项
    QActionGroup *grp = new QActionGroup(this);
    connect(grp, SIGNAL(triggered(QAction *)), this, SLOT(textAlign(QActin *)));

    //if(QApplication::isLeftToRight())

        leftAlignAct = new QAction(QIcon("leftAlign.png"), tr("左对齐(&L)"), grp);
        centerAct = new QAction(QIcon("center.png"), tr("居中(&E)"), grp);
        rightAlignAct = new QAction(QIcon("rightAlign.png"), tr("右对齐(&R)"), grp);

    justifyAct = new QAction(QIcon("justify.png"), tr("两端对齐(&J)"), grp);

    leftAlignAct->setShortcut(Qt::CTRL + Qt::Key_L);
    leftAlignAct->setCheckable(true);
    leftAlignAct->setToolTip("左对齐");
    leftAlignAct->setStatusTip(tr("将文字左对齐"));

    centerAct->setShortcut(Qt::CTRL + Qt::Key_E);
    centerAct->setCheckable(true);
    centerAct->setToolTip("居中");
    centerAct->setStatusTip(tr("将文字居中对齐"));

    rightAlignAct->setShortcut(Qt::CTRL + Qt::Key_R);
    rightAlignAct->setCheckable(true);
    rightAlignAct->setToolTip("右对齐");
    rightAlignAct->setStatusTip(tr("将文字右对齐"));

    justifyAct->setShortcut(Qt::CTRL + Qt::Key_J);
    justifyAct->setCheckable(true);
    justifyAct->setToolTip("两端对齐");
    justifyAct->setStatusTip(tr("将文字两端对齐"));

    QPixmap pix(16,16);
    pix.fill(Qt::red);
    colorAct = new QAction(pix, tr("颜色(&C)..."), this);
    colorAct->setToolTip("颜色");
    colorAct->setStatusTip(tr("设置文字颜色"));
    //connect(colorAct, SIGNAL(triggered()), this, SLOT(textColor()));
}

//创建菜单的函数createMenus()
void QtWord::createMenus()
{
    //”文件”主菜单
    fileMenu = menuBar()->addMenu(tr("文件(&F)"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    //添加分割线
    fileMenu->addSeparator();
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    //再添加分割线
    fileMenu->addSeparator();
    fileMenu->addAction(printAct);
    fileMenu->addAction(printPreviewAct);
    //再添加分割线
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);



    //”编辑”主菜单
    editMenu = menuBar()->addMenu(tr("编辑(&E)"));
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
    editMenu->addSeparator();
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);


    //“格式”主菜单
    formatMenu = menuBar()->addMenu(tr("格式(&O)"));
    //“字体”子菜单
    fontMenu = formatMenu->addMenu(tr("字体(&D)"));
    //“段落”子菜单
    alignMenu = formatMenu->addMenu(tr("段落(&P)"));
    fontMenu->addAction(boldAct);
    fontMenu->addAction(italicAct);
    fontMenu->addAction(underlineAct);
    alignMenu->addAction(leftAlignAct);
    alignMenu->addAction(centerAct);
    alignMenu->addAction(rightAlignAct);
    alignMenu->addAction(justifyAct);
    formatMenu->addAction(colorAct);


}

//实现槽函数textAlign()
void QtWord::textAlign(QAction *a)
{

}
