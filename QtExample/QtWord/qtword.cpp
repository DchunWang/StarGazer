#include "qtword.h"
#include <QtWidgets>


const QString rsrcPath = ":/image";


QtWord::QtWord(QWidget *parent)
    : QMainWindow(parent)
{
    mdiArea = new QMdiArea;
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(mdiArea);

    connect(mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this,
            SLOT(updateMenus()));
    updateMenus();

    move(200, 150);
    resize(800, 500);
    setWindowTitle(tr("Qt Word"));

    //创建信号映射器
    windowMapper = new QSignalMapper(this);
    //映射器重新发送信号，根据信号设置活动窗口
    connect(windowMapper, SIGNAL(mapped(QWidget *)), this,
            SLOT(setActiveSubWindow(QWidget * )));


    //自己添加的部分，可删，待测试
    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    updateMenus();
//    MyChild *childEdit = new MyChild();
//    childEdit->show();

}

QtWord::~QtWord()
{

}

//实现各动作
void QtWord::createActions()
{

    ////////////////////////////////////////////////////////////////////////////
    //“文件“菜单动作集
    newAct = new QAction(QIcon(rsrcPath + "/fileNew.png"), tr("新建(&N)"),this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setToolTip("新建");
    newAct->setStatusTip(tr("创建一个新文档"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(fileNew()));

    openAct = new QAction(QIcon(rsrcPath + "/fileOpen.png"), tr("打开(&O)..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setToolTip("打开");
    openAct->setStatusTip(tr("打开已存在的文档"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(fileOpen()));

    saveAct = new QAction(QIcon(rsrcPath + "/fileSave.png"), tr("保存(&S)"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setToolTip("保存");
    saveAct->setStatusTip(tr("将当前文件存盘"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(fileSave()));

    saveAsAct = new QAction(QIcon(rsrcPath + "/fileSaveAs.png"),tr("另存为(&A)..."), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(tr("一个新名字保存文档"));
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(fileSaveAs()));

    printAct = new QAction(QIcon(rsrcPath + "/filePrint.png"), tr("打印(&P)..."), this);
    printAct->setShortcuts(QKeySequence::Print);
    printAct->setToolTip("打印");
    printAct->setStatusTip(tr("打印文档"));
    connect(printAct, SIGNAL(triggered()), this, SLOT(filePrint()));

    printPreviewAct = new QAction(QIcon(rsrcPath + "/filePrintPre.png"),tr("打印预览..."), this);
    printPreviewAct->setStatusTip(tr("预览打印效果"));
    connect(printPreviewAct, SIGNAL(triggered()), this, SLOT(filePrintPreview()));

    exitAct = new QAction(QIcon(rsrcPath + "/exit.png"),tr("退出(&X)"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("退出应用程序"));
    connect(exitAct, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));


    /////////////////////////////////////////////////////////////////////////////////////
    //“编辑”菜单动作集
    undoAct = new QAction(QIcon(rsrcPath + "/editUndo.png"), tr("撤销(&U)"), this);
    undoAct->setShortcuts(QKeySequence::Undo);
    undoAct->setToolTip("撤销");
    undoAct->setStatusTip(tr("撤销当前动作"));
    connect(undoAct, SIGNAL(triggered()), this, SLOT(undo()));

    redoAct = new QAction(QIcon(rsrcPath + "/editRedo.png"), tr("重做(&R)"),this);
    redoAct->setShortcuts(QKeySequence::Redo);
    redoAct->setToolTip("重做");
    redoAct->setStatusTip(tr("恢复之前操作"));
    connect(redoAct, SIGNAL(triggered()), this, SLOT(redo()));

    cutAct = new QAction(QIcon(rsrcPath + "/editCut.png"), tr("剪切(&T)"), this);
    cutAct->setShortcuts(QKeySequence::Cut);
    cutAct->setToolTip("剪切");
    cutAct->setStatusTip(tr("从文档中裁剪所选内容，并将其放入剪贴板"));
    connect(cutAct, SIGNAL(triggered()), this, SLOT(cut()));

    copyAct = new QAction(QIcon(rsrcPath + "/editCopy.png"), tr("复制"), this);
    copyAct->setShortcuts(QKeySequence::Copy);
    copyAct->setToolTip("复制");
    copyAct->setStatusTip(tr("复制所选内容，并将其放入剪贴板"));
    connect(copyAct, SIGNAL(triggered()), this, SLOT(copy()));

    pasteAct = new QAction(QIcon(rsrcPath + "/editPaste.png"), tr("粘贴"), this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    pasteAct->setToolTip("粘贴");
    pasteAct->setStatusTip(tr("将剪贴板的内容粘贴到文档"));
    connect(pasteAct, SIGNAL(triggered()), this, SLOT(paste()));


    //////////////////////////////////////////////////////////////////////////////////////
    //”格式“菜单动作集
    boldAct = new QAction(QIcon(rsrcPath + "/bold.png"), tr("加粗(&B)"), this);
    boldAct->setCheckable(true);
    boldAct->setShortcut(Qt::CTRL + Qt::Key_B);
    boldAct->setToolTip("加粗");
    boldAct->setStatusTip(tr("将所选文字加粗"));
    QFont bold;
    bold.setBold(true);
    boldAct->setFont(bold);
    connect(boldAct, SIGNAL(triggered()), this, SLOT(textBold()));

    italicAct = new QAction(QIcon(rsrcPath + "/italic.png"), tr("斜体(&I)"), this);
    italicAct->setCheckable(true);
    italicAct->setShortcut(Qt::CTRL + Qt::Key_I);
    italicAct->setToolTip("斜体");
    italicAct->setStatusTip(tr("将所选文字用斜体显示"));
    QFont italic;
    italic.setItalic(true);
    italicAct->setFont(italic);
    connect(italicAct, SIGNAL(triggered()), this, SLOT(textItalic()));

    underlineAct = new QAction(QIcon(rsrcPath + "/underline.png"), tr("下划线(&U)"), this);
    underlineAct->setCheckable(true);
    underlineAct->setShortcut(Qt::CTRL +Qt::Key_U);
    underlineAct->setToolTip("下划线");
    underlineAct->setStatusTip(tr("为所选文字加下划线"));
    QFont underline;
    underline.setUnderline(true);
    underlineAct->setFont(underline);
    connect(underlineAct, SIGNAL(triggered()),  this, SLOT(textUnderline()));

    //“格式”-“段落”子菜单下的各项为同一个菜单项组，只能选中其中一项
    QActionGroup *grp = new QActionGroup(this);
    connect(grp, SIGNAL(triggered(QAction *)), this, SLOT(textAlign(QAction *)));

    //if(QApplication::isLeftToRight())

        leftAlignAct = new QAction(QIcon(rsrcPath + "/leftAlign.png"), tr("左对齐(&L)"), grp);
        centerAct = new QAction(QIcon(rsrcPath + "/center.png"), tr("居中(&E)"), grp);
        rightAlignAct = new QAction(QIcon(rsrcPath + "/rightAlign.png"), tr("右对齐(&R)"), grp);

    justifyAct = new QAction(QIcon(rsrcPath + "/justify.png"), tr("两端对齐(&J)"), grp);

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
    connect(colorAct, SIGNAL(triggered()), this, SLOT(textColor()));


    ////////////////////////////////////////////////////////////////////////////////////
    //“窗口”菜单动作集
    closeAct = new QAction(tr("关闭(&O)"), this);
    closeAct->setStatusTip(tr("关闭活动文档子窗口"));
    connect(closeAct, SIGNAL(triggered()), mdiArea, SLOT(closeActiveSubWindow()));

    closeAllAct = new QAction(tr("关闭所有(&A)"), this);
    closeAllAct->setStatusTip(tr("关闭所有子窗口"));
    connect(closeAllAct, SIGNAL(triggered()), mdiArea, SLOT(closeAllSubWindows()));

    tileAct = new QAction(tr("平铺(&T)"), this);
    tileAct->setStatusTip(tr("平铺子窗口"));
    connect(tileAct, SIGNAL(triggered()), mdiArea, SLOT(tileSubWindows()));

    cascadeAct = new QAction(tr("层叠(&C)"), this);
    cascadeAct->setStatusTip(tr("层叠子窗口"));
    connect(cascadeAct, SIGNAL(triggered()), mdiArea, SLOT(cascadeSubWindows()));

    nextAct = new QAction(tr("下一个(&X)"), this);
    nextAct->setShortcuts(QKeySequence::NextChild);
    nextAct->setStatusTip(tr("移动焦点到下一个子窗口"));
    connect(nextAct, SIGNAL(triggered()), mdiArea, SLOT(activateNextSubWindow()));

    previousAct = new QAction(tr("前一个(&V)"), this);
    previousAct->setShortcuts(QKeySequence::PreviousChild);
    previousAct->setStatusTip(tr("移动焦点到前一个子窗口"));
    connect(previousAct, SIGNAL(triggered()), mdiArea, SLOT(activatePreviousSubWindow()));

    separatorAct = new QAction(this);
    separatorAct->setSeparator(true);

    ///////////////////////////////////////////////////////////////////////////////////////
    //“帮助 ”菜单各功能集
    aboutAct = new QAction(QIcon(rsrcPath + "/about.png"), tr("关于(&A)"), this);
    aboutAct->setStatusTip(tr("关于QtWord"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(QIcon(rsrcPath + "/aboutQt.png"), tr("关于Qt(&Q)"), this);
    aboutQtAct->setStatusTip(tr("关于Qt库"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

//创建菜单
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

    //“窗口”主菜单
    windowMenu = menuBar()->addMenu(tr("窗口(&W)"));
//    windowMenu->addAction(closeAct);
//    windowMenu->addAction(closeAllAct);
//    windowMenu->addSeparator();
//    windowMenu->addAction(tileAct);
//    windowMenu->addAction(cascadeAct);
//    windowMenu->addSeparator();
//    windowMenu->addAction(nextAct);
//    windowMenu->addAction(previousAct);
    //windowMenu->addAction(separatorAct);
    updateWindowMenu();
    connect(windowMenu, SIGNAL(aboutToShow()), this, SLOT(updateWindowMenu()));
    menuBar()->addSeparator();

    //”帮助“主菜单
    helpMenu = menuBar()->addMenu(tr("帮助(&H)"));
    helpMenu->addAction(aboutAct);
    helpMenu->addSeparator();
    helpMenu->addAction(aboutQtAct);

}

//创建工具条
void QtWord::createToolBars()
{
    //”文件“工具条
    fileToolBar = addToolBar(tr("文件"));
    fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(saveAct);
    fileToolBar->addSeparator();
    fileToolBar->addAction(printAct);
    fileToolBar->addAction(printPreviewAct);

    //”编辑“工具条
    editToolBar = addToolBar(tr("编辑"));
    editToolBar->addAction(undoAct);
    editToolBar->addAction(redoAct);
    editToolBar->addSeparator();
    editToolBar->addAction(cutAct);
    editToolBar->addAction(copyAct);
    editToolBar->addAction(pasteAct);

    //”格式“工具条
    formatToolBar = addToolBar(tr("格式"));
    formatToolBar->addAction(boldAct);
    formatToolBar->addAction(italicAct);
    formatToolBar->addAction(underlineAct);
    formatToolBar->addSeparator();
    formatToolBar->addAction(leftAlignAct);
    formatToolBar->addAction(centerAct);
    formatToolBar->addAction(rightAlignAct);
    formatToolBar->addAction(justifyAct);
    formatToolBar->addSeparator();
    formatToolBar->addAction(colorAct);

    //”组合“选择工具条
    //使工具条可以分多行显示
    addToolBarBreak(Qt::TopToolBarArea);
    comboToolBar = addToolBar(tr("组合选择"));
    styleComboBox = new QComboBox();
    comboToolBar->addWidget(styleComboBox);
    styleComboBox->addItem("标准");
    styleComboBox->addItem("项目符号(A)");
    styleComboBox->addItem("项目符号(B)");
    styleComboBox->addItem("项目符号(C)");
    styleComboBox->addItem("编号(1)");
    styleComboBox->addItem("编号(2)");
    styleComboBox->addItem("编号(3)");
    styleComboBox->addItem("编号(4)");
    styleComboBox->addItem("编号(5)");
    styleComboBox->setStatusTip(tr("段落加标号或编号"));
    connect(styleComboBox, SIGNAL(activated(int)), this, SLOT(textStyle(int)));

    fontComboBox = new QFontComboBox();
    comboToolBar->addWidget(fontComboBox);
    fontComboBox->setStatusTip(tr("更改字体"));
    connect(fontComboBox, SIGNAL(activated(QString)), this, SLOT(textFamily(QString)));

    sizeComboBox = new QComboBox();
    comboToolBar->addWidget(sizeComboBox);
    sizeComboBox->setEditable(true);
    sizeComboBox->setStatusTip(tr("更改字号"));
    QFontDatabase db;
    foreach(int size, db.standardSizes())
        sizeComboBox->addItem(QString::number(size));
    connect(sizeComboBox, SIGNAL(activated(QString)), this, SLOT(textSize(QString)));

    sizeComboBox->setCurrentIndex(sizeComboBox->findText(QString::number(
    QApplication::font().pointSize())));
}




//实现槽函数about()
void QtWord::about()
{
    QMessageBox::about(this, tr("关于"), tr("这是一个基于Qt实现的文字处理软件，具有类似"
                                          "微软Office Word的功能"));
}

//实现创建子窗口
MyChild *QtWord::createMyChild()
{
    //创建MyChild部件
    MyChild *child = new MyChild;
    //向多文档区域添加子窗口，child为中心部件
    mdiArea->addSubWindow(child);
    //根据QTextEdit类是否可以复制信号，设置剪切、复制动作是否可用
    connect(child, SIGNAL(copyAvailable(bool)), cutAct, SLOT(setEnabled(bool)));
    connect(child, SIGNAL(copyAvailable(bool)), copyAct, SLOT(setEnabled(bool)));
    return child;
}

//实现新建文件的操作
void QtWord::fileNew()
{
    MyChild *child = createMyChild();
    child->newFile();
    child->show();
    enabledText();
}


//实现
void QtWord::enabledText()
{
    boldAct->setEnabled(true);
    italicAct->setEnabled(true);
    underlineAct->setEnabled(true);
    leftAlignAct->setEnabled(true);
    centerAct->setEnabled(true);
    rightAlignAct->setEnabled(true);
    justifyAct->setEnabled(true);
    colorAct->setEnabled(true);
}

//更新菜单
void QtWord::updateMenus()
{
//    //至少有一个子文档打开时的情况
//    bool hasMyChild = (activeMyChild() != 0);
//    saveAct->setEnabled(hasMyChild);
//    saveAsAct->setEnabled(hasMyChild);
////    printAct->setEnabled(hasMyChild);
////    printPreviewAct->setEnabled(hasMyChild);

//#ifndef QT_NO_CLIPBOARD
//    pasteAct->setEnabled(hasMyChild);
//#endif

//    closeAct->setEnabled(hasMyChild);
//    closeAllAct->setEnabled(hasMyChild);
//    tileAct->setEnabled(hasMyChild);
//    cascadeAct->setEnabled(hasMyChild);
//    nextAct->setEnabled(hasMyChild);
//    previousAct->setEnabled(hasMyChild);

//    //设置分隔条是否显示
//    separatorAct->setVisible(hasMyChild);

//    //文档打开并且其中有内容被选中的情况

//#ifndef QT_NO_CLIPBOARD
//     bool hasSelection = (activeMyChild() &&
//                          activeMyChild()->textCursor().hasSelection());

//    cutAct->setEnabled(hasSelection);
//    copyAct->setEnabled(hasSelection);
////    boldAct->setEnabled(hasSelection);
////    italicAct->setEnabled(hasSelection);
////    underlineAct->setEnabled(hasSelection);
////    leftAlignAct->setEnabled(hasSelection);
////    centerAct->setEnabled(hasSelection);
////    rightAlignAct->setEnabled(hasSelection);
////    justifyAct->setEnabled(hasSelection);
////    colorAct->setEnabled(hasSelection);
//#endif
}

MyChild *QtWord::activeMyChild()
{
    //若有活动窗口，则将其内的中心部件装换为MyChild类型；
    //若没有，则直接返回
    if(QMdiSubWindow *activeSubWindow = mdiArea->activeSubWindow())
        return qobject_cast<MyChild *>(activeSubWindow->widget());
    else
        return 0;
}


//更新菜单的槽函数
void QtWord::updateWindowMenu()
{
    //首先清空菜单，然后再添加各个菜单工作
    windowMenu->clear();
    windowMenu->addAction(closeAct);
    windowMenu->addAction(closeAllAct);
    windowMenu->addSeparator();
    windowMenu->addAction(tileAct);
    windowMenu->addAction(cascadeAct);
    windowMenu->addSeparator();
    windowMenu->addAction(nextAct);
    windowMenu->addAction(previousAct);
    windowMenu->addAction(separatorAct);

    //如果有活动窗口，则显示分隔条
    QList<QMdiSubWindow *> windows = mdiArea->subWindowList();
    separatorAct->setVisible(!windows.isEmpty());

    //遍历各个子窗，显示当前已打开的文档子窗口项
    for(int i = 0; i < windows.size(); ++i)
    {
        MyChild *child = qobject_cast<MyChild *>(windows.at(i)->widget());
        QString text;
        if(i < 9)
        {
            text = tr("&%1 %2").arg(i + 1).arg(child->userFriendlyCurrentFile());

        }
        else
        {
            text = tr("%1 %2").arg(i+1).arg(child->userFriendlyCurrentFile());
        }

        //添加动作到菜单，设置动作可以选择
        QAction*action = windowMenu->addAction(text);
        action->setCheckable(true);

        //设置当前活动窗口动作为选中状态
        action->setChecked(child == activeMyChild());

        //关联动作的触发信号到信号映射器的map()槽， 这个槽会发送mapped()信号
        connect(action, SIGNAL(triggered()), windowMapper, SLOT(map()));

        //将动作与相应的窗口部件进行映射，在发送mapped()信号时就会以这个窗口部件为参数
        windowMapper->setMapping(action, windows.at(i));
    }
    //使得字体设置菜单可用
    enabledText();

}


void QtWord::closeEvent(QCloseEvent *event)
{
    mdiArea->closeAllSubWindows();
    if(mdiArea->currentSubWindow())
    {
        event->ignore();

    }
    else
    {
        event->accept();
    }
}

void QtWord::createStatusBar()
{
    statusBar()->showMessage(tr("就绪"));
}


void QtWord::fileOpen()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("打开"),
                       QString(), tr("HTML 文档 (*.htm *.html);;所有文件 (*.*)"));

    if(!fileName.isEmpty())
    {
        QMdiSubWindow *existing = findMyChild(fileName);
        if(existing)
        {
            mdiArea->setActiveSubWindow(existing);
            return;
        }
        MyChild *child = createMyChild();
        if(child->loadFile(fileName))
        {
            statusBar()->showMessage(tr("文件已载入"), 2000);
            child->show();

        }
        else
        {
            child->close();
        }
    }
}


QMdiSubWindow *QtWord::findMyChild(const QString &fileName)
{
    QString canonicalFilePath = QFileInfo(fileName).canonicalFilePath();
    foreach(QMdiSubWindow *window, mdiArea->subWindowList())
    {
        MyChild *myChild = qobject_cast<MyChild *>(window->widget());
        if(myChild->currentFile() == canonicalFilePath)
            return window;
    }
    return 0;
}


void QtWord::fileSave()
{
    if(activeMyChild() && activeMyChild()->save())
        statusBar()->showMessage(tr("保存成功"), 2000);
}

void QtWord::fileSaveAs()
{
    if(activeMyChild() && activeMyChild()->saveAs())
        statusBar()->showMessage(tr("保存成功"), 2000);

}

void QtWord::undo()
{
    if(activeMyChild())
        activeMyChild()->undo();
}

void QtWord::redo()
{
    if(activeMyChild())
        activeMyChild()->redo();
}

void QtWord::cut()
{
    if(activeMyChild())
        activeMyChild()->cut();
}

void QtWord::copy()
{
    if(activeMyChild())
        activeMyChild()->copy();
}

void QtWord::paste()
{
    if(activeMyChild())
        activeMyChild()->paste();
}

void QtWord::textBold()
{
    QTextCharFormat fmt;
    fmt.setFontWeight(boldAct->isChecked()?QFont::Bold : QFont::Normal);
    if(activeMyChild())
        activeMyChild()->mergeFormatOnWordOrSelection(fmt);
}


void QtWord::textItalic()
{
    QTextCharFormat fmt;
    fmt.setFontItalic(italicAct->isChecked());
    if(activeMyChild())
        activeMyChild()->mergeFormatOnWordOrSelection(fmt);
}

void QtWord::textUnderline()
{
    QTextCharFormat fmt;
    fmt.setFontUnderline(underlineAct->isChecked());
    if(activeMyChild())
        activeMyChild()->mergeFormatOnWordOrSelection(fmt);
}

void QtWord::textFamily(const QString &f)
{
    QTextCharFormat fmt;
    fmt.setFontFamily(f);
    if(activeMyChild())
        activeMyChild()->mergeFormatOnWordOrSelection(fmt);
}

void QtWord::textSize(const QString &p)
{
    qreal pointSize = p.toFloat();
    if(p.toFloat() > 0)
    {
        QTextCharFormat fmt;
        fmt.setFontPointSize(pointSize);
        if(activeMyChild())
            activeMyChild()->mergeFormatOnWordOrSelection(fmt);
    }
}

void QtWord::textAlign(QAction *a)
{
    if(activeMyChild())
    {
        if(a == leftAlignAct)
            activeMyChild()->setAlign(1);
        else if(a == centerAct)
            activeMyChild()->setAlign(2);
        else if(a == rightAlignAct)
            activeMyChild()->setAlign(3);
        else if(a == justifyAct)
            activeMyChild()->setAlign(4);
    }
}

void QtWord::textColor()
{
    if(activeMyChild())
    {
        QColor col = QColorDialog::getColor(activeMyChild()->textColor(), this);
        if(!col.isValid())
            return;
        QTextCharFormat fmt;
        fmt.setForeground(col);
        activeMyChild()->mergeFormatOnWordOrSelection(fmt);
        //colorChanged(col);
    }
}

void QtWord::textStyle(int styleIndex)
{
    if(activeMyChild())
        activeMyChild()->setStyle(styleIndex);
}

void QtWord::filePrint()
{
    QPrinter printer(QPrinter::HighResolution);
    QPrintDialog *dlg = new QPrintDialog(&printer, this);
    if(activeMyChild()->textCursor().hasSelection())
        dlg->addEnabledOption(QAbstractPrintDialog::PrintSelection);
    dlg->setWindowTitle(tr("打印文档"));
    if(dlg->exec() == QDialog::Accepted)
        activeMyChild()->print(&printer);
    delete dlg;
}

void QtWord::filePrintPreview()
{
    QPrinter printer(QPrinter::HighResolution);
    QPrintPreviewDialog preview(&printer, this);
    connect(&preview, SIGNAL(paintRequested(QPrinter*)), SLOT(printPreview(QPrinter*)));
    preview.exec();
}

void QtWord::printPreview(QPrinter *printer)
{
    activeMyChild()->print(printer);
}

//自己补充
void QtWord::setActiveSubWindow(QWidget *window)
{
    if (!window)
        return;
    mdiArea->setActiveSubWindow(qobject_cast<QMdiSubWindow *>(window));
}
