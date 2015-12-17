#include "myword.h"
#include "centralwidget.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QColor>
#include <QColorDialog>
#include <QTextList>


MyWord::MyWord(QWidget *parent)
    : QMainWindow(parent)
{
    //设置窗体的标题
    setWindowTitle(tr("MyWord"));
    //新建一个自定义的窗体对象
    Cent = new CentralWidget(this);
    //设置这个窗体对象为主窗体
    setCentralWidget(Cent);


    /////////////////////////////////////////////////////////
    //文本编辑功能相关


    fontLabel1 = new QLabel(tr("字体"));

    //字体下拉列表，使得能够从中选择所需的字体
    fontComboBox = new QFontComboBox;
    //setFontFilters接口可过滤只在下拉列表框中显示某一类字体
    fontComboBox->setFontFilters(QFontComboBox::ScalableFonts);

    fontLabel2 = new QLabel(tr("字号"));
    //字号下拉列表
    sizeComboBox = new QComboBox;


    //实现在字号下拉列表 框中 填充各种不同的字号条目
    //QFontDatabase类用于表示当前系统中所有可用的格式信息，主要是字体和字号大小
    QFontDatabase db;

    //standardSizes()函数返回可用标准字号的列表，
    //并将它们插入到字号下拉列表中
    foreach(int size, db.standardSizes())
        sizeComboBox->addItem(QString::number(size));


    //定义粗体按钮
    boldBtn = new QToolButton;
    //设置粗体按钮图标
    boldBtn->setIcon(QIcon("bold.png"));
    //设置粗体按钮为可
    boldBtn->setCheckable(true);
    //boldBtn->setStatusTip(tr("加粗"));

    italicBtn = new QToolButton;
    italicBtn->setIcon(QIcon("italic.png"));
    italicBtn->setCheckable(true);
    //italicBtn->setStatusTip(tr("斜体"));

    underlineBtn = new QToolButton;
    underlineBtn->setIcon(QIcon("underline.png"));
    underlineBtn->setCheckable(true);
    //underlineBtn->setStatusTip(tr("下划线"));

    colorBtn = new QToolButton;
    colorBtn->setIcon(QIcon("color.png"));
    colorBtn->setCheckable(true);
    //colorBtn->setStatusTip(tr("颜色"));

    //添加相应的事件关联
    connect(fontComboBox, SIGNAL(activated(QString)), this,
            SLOT(showFontComboBox(QString)));
    connect(sizeComboBox, SIGNAL(activated(QString)), this,
            SLOT(showSizeSpinBox(QString)));
    connect(boldBtn, SIGNAL(clicked()), this, SLOT(showBoldBtn()));
    connect(italicBtn, SIGNAL(clicked()), this, SLOT(showItalicBtn()));
    connect(underlineBtn, SIGNAL(clicked()), this, SLOT(showUnderlineBtn()));
    connect(colorBtn, SIGNAL(clicked()), this, SLOT(showColorBtn()));

    connect(Cent->text, SIGNAL(currentCharFormatChanged(const QTextCharFormat &)),
           this, SLOT(showCurrentFormatChanged(const QTextCharFormat &)));


    /////////////////////////////////////////////////////////


    listLabel = new QLabel(tr("排序"));
    listComboBox = new QComboBox;
    listComboBox->addItem("Standard");
    listComboBox->addItem("QTextListFormat::ListDisc");
    listComboBox->addItem("QTextListFormat::ListCircle");
    listComboBox->addItem("QTextListFormat::ListSquare");
    listComboBox->addItem("QTextListFormat::ListDecimal");
    listComboBox->addItem("QTextListFormat::LIstLowerAlpha");
    listComboBox->addItem("QTextListFormat::ListUpperAlpha");
    listComboBox->addItem("QTextListFormat::ListLowerRoman");
    listComboBox->addItem("QTextListFormat::ListUpperRoman");

    connect(listComboBox, SIGNAL(activated(int)), this, SLOT(showList(int)));

//    connect(Cent->text->document(), SIGNAL(undoAvailable(bool)),
//            undoAction, SLOT(setEnabled(bool)));

//    connect(Cent->text->document(), SIGNAL(redoAvailable(bool)),
//            redoAction, SLOT(setEnabled(bool)));

    connect(Cent->text, SIGNAL(cursorPositionChanged()), this,
            SLOT(showCursorPositionChanged()));






    //创建动作
    createActions();
    //创建菜单
    createMenus();
    //创建工具栏
    createToolBars();

    //如果加载了图片
    if(img.load("image.png"))
    {
        //在主窗体的imageLabel对象中放置图片
        Cent->imageLabel->setPixmap(QPixmap::fromImage(img));
    }


}

MyWord::~MyWord()
{

}

//创建动作的函数createAction()，用于创建一系列的动作
//QAction类为用户提供了一个统一的命令接口，无论是从菜单、工具栏还是快捷键触发，
//都是调用同样的动作操作接口，以达到同样的目的。

void MyWord::createActions()
{
    //打开动作的创建
    //先新建一个QAction对象，注意其中所需的参数
    openFileAction = new QAction(QIcon("open.png"), tr("打开"), this);
    //然后设置这个动作命令的快捷键
    openFileAction->setShortcut(tr("Ctrl+O"));
    //再设置这个动作的说明提示文字
    openFileAction->setStatusTip(tr("打开一个文件"));

    //新建动作
    newFileAction = new QAction(QIcon("newFile.png"), tr("新建"), this);
    newFileAction->setShortcut(tr("Ctrl+N"));
    newFileAction->setStatusTip(tr("新建一个文件"));

    //打印文本动作
    printTextAction = new QAction(QIcon("printText.png"), tr("打印文本"), this);
    printTextAction->setShortcut(tr("Ctrl+T"));
    printTextAction->setStatusTip(tr("打印文本"));

    //打印图片动作
    printImageAction = new QAction(QIcon("printImage.png"), tr("打印图片"), this);
    printImageAction->setShortcut(tr("Ctrl+I"));
    printImageAction->setStatusTip(tr("打印图片"));

    //退出动作
    exitAction = new QAction(tr("退出"), this);
    exitAction->setShortcut(tr("Ctrl+E"));
    exitAction->setStatusTip(tr("退出程序"));

    //复制动作
    copyAction = new QAction(QIcon("copy.png"), tr("复制"), this);
    copyAction->setShortcut(tr("Ctrl+C"));
    copyAction->setStatusTip(tr("复制"));

    //剪切动作
    cutAction = new QAction(QIcon("cut.png"), tr("剪切"), this);
    cutAction->setShortcut(tr("Ctrl + X"));
    cutAction->setStatusTip(tr("剪切"));

    //粘贴动作
    pasteAction = new QAction(QIcon("paste.png"), tr("粘贴"),  this);
    pasteAction->setShortcut(tr("Ctrl+V"));
    pasteAction->setStatusTip(tr("粘贴"));

    //关于动作
    aboutAction = new QAction(tr("关于"),this);
    aboutAction->setShortcut(tr("Ctrl + Y"));
    aboutAction->setStatusTip(tr("关于"));

    //放大动作
    zoomInAction = new QAction(QIcon("zoomIn.png"), tr("放大"), this);
    zoomInAction->setShortcut(tr("Ctrl + ]"));
    zoomInAction->setStatusTip(tr("放大"));

    //缩小动作
    zoomOutAction = new QAction(QIcon("zoomOut.png"), tr("缩小"), this);
    zoomOutAction->setShortcut(tr("Ctrl +  ["));
    zoomOutAction->setStatusTip(tr("缩小"));

    //旋转动作有快捷键吗？
    //旋转90度动作
    rotate90Action = new QAction(QIcon("rotate90.png"),tr("旋转90度"), this);
    rotate90Action->setStatusTip(tr("旋转90度"));

    //旋转180度动作
    rotate180Action = new QAction(QIcon("rotate180.png"), tr("旋转180度"), this);
    rotate180Action->setStatusTip(tr("将一幅图旋转180度"));

    //旋转270度动作
    rotate270Action = new QAction(QIcon("rotate270.png"), tr("旋转270度"), this);
    rotate270Action->setStatusTip(tr("将一幅图旋转270度"));

    //实现图像的镜像动作
    //纵向镜像
    mirrorVerticalAction = new QAction(QIcon("mirrorVertical.png"), tr("纵向镜像"),this);
    mirrorVerticalAction->setStatusTip(tr("对一幅图做纵向镜像"));

    //横向镜像
    mirrorHorizontalAction = new QAction(QIcon("mirrorHorizontal.png"), tr("横向镜像"), this);
    mirrorHorizontalAction->setStatusTip(tr("对一幅图做横向镜像"));

    //实现撤销和恢复动作
    undoAction = new QAction(QIcon("undo.png"), tr("撤销"), this);
    redoAction = new QAction(QIcon("redo.png"), tr("重做"), this);

    //添加各个动作的事件关联
    connect(newFileAction, SIGNAL(triggered()), this, SLOT(showNewFile()));
    connect(openFileAction, SIGNAL(triggered()), this, SLOT(showOpenFile()));
    connect(printTextAction, SIGNAL(triggered()), this, SLOT(showPrintText()));
    connect(printImageAction, SIGNAL(triggered()), this, SLOT(showPrintImage()));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
    connect(copyAction, SIGNAL(triggered()), Cent->text, SLOT(copy()));
    connect(cutAction, SIGNAL(triggered()), Cent->text, SLOT(cut()));
    connect(pasteAction, SIGNAL(triggered()), Cent->text, SLOT(paste()));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(QApplication::aboutQt()));
    connect(zoomInAction, SIGNAL(triggered()), this, SLOT(showZoomIn()));
    connect(zoomOutAction, SIGNAL(triggered()), this, SLOT(showZoomOut()));
    connect(rotate90Action, SIGNAL(triggered()), this, SLOT(showRotate90()));
    connect(rotate180Action, SIGNAL(triggered()), this, SLOT(showRotate180()));
    connect(rotate270Action, SIGNAL(triggered()), this, SLOT(showRotate270()));
    connect(mirrorVerticalAction, SIGNAL(triggered()), this, SLOT(showMirrorVertical()));
    connect(mirrorHorizontalAction, SIGNAL(triggered()), this, SLOT(showMirrorHorizontal()));
    connect(undoAction, SIGNAL(triggered()), Cent->text, SLOT(undo()));
    connect(redoAction, SIGNAL(triggered()), Cent->text, SLOT(redo()));

    ///////////////////////////////////////////////////////////////////////////////////////////

    //排序：左对齐、右对齐、居中对齐、两端对齐
    actionGroup = new QActionGroup(this);
    leftAction = new QAction(QIcon("left.png"), tr("左对齐"), actionGroup);
    leftAction->setCheckable(true);
    rightAction = new QAction(QIcon("right.png"), tr("右对齐"), actionGroup);
    rightAction->setCheckable(true);
    centerAction = new QAction(QIcon("center.png"), tr("居中对齐"), actionGroup);
    centerAction->setCheckable(true);
    justifyAction = new QAction(QIcon("justify.png"), tr("两端对齐"), actionGroup);
    justifyAction->setCheckable(true);

    connect(actionGroup, SIGNAL(triggered(QAction *)),  this, SLOT(showAlignment(QAction*)));

}


//在实现了各个动作之后，需要将他们通过菜单、工具栏和快捷键的方式体现出来
//菜单的实现函数createMenes()
void MyWord::createMenus()
{
    //文件菜单
    //首先需要在菜单栏中添加一个菜单项
    fileMenu = menuBar()->addMenu(tr("文件"));
    //然后将相应的动作添加到该菜单下
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(newFileAction);
    fileMenu->addAction(printTextAction);
    fileMenu->addAction(printImageAction);
    //然后在该菜单下添加一个分隔符
    fileMenu->addSeparator();
    //之后再继续在该菜单下添加相对特殊的动作——退出动作
    fileMenu->addAction(exitAction);

    //以相同的方式添加缩放菜单、旋转菜单和镜像菜单

    //编辑菜单
    editMenu = menuBar()->addMenu(tr("编辑"));
    editMenu->addAction(copyAction);
    editMenu->addAction(cutAction);
    editMenu->addAction(pasteAction);
    editMenu->addAction(aboutAction);
    editMenu->addSeparator();
    editMenu->addAction(zoomInAction);
    editMenu->addAction(zoomOutAction);

    //旋转菜单
    rotateMenu = menuBar()->addMenu(tr("旋转"));
    rotateMenu->addAction(rotate90Action);
    rotateMenu->addAction(rotate180Action);
    rotateMenu->addAction(rotate270Action);

    //镜像菜单
    mirrorMenu = menuBar()->addMenu(tr("镜像"));
    mirrorMenu->addAction(mirrorVerticalAction);
    mirrorMenu->addAction(mirrorHorizontalAction);

}

//对于工具栏的实现createToolBars()
//主窗口的工具栏上可以有多个工具条，通常采用一个菜单对应一个工具条的方式
//也可以根据需要对工具条进行划分

void MyWord::createToolBars()
{
    //文件工具条
    //首先向工具栏中添加一个工具条，
    fileTool = addToolBar("File");
    //然后向这个工具条中添加相应的动作
    fileTool->addAction(openFileAction);
    fileTool->addAction(newFileAction);
    fileTool->addAction(printTextAction);
    fileTool->addAction(printImageAction);

    //依照上面的方式依次添加编辑、旋转和镜像工具条

    //编辑工具条
    editTool = addToolBar("Edit");
    editTool->addAction(copyAction);
    editTool->addAction(cutAction);
    editTool->addAction(pasteAction);

    //工具条也可以添加分隔符
    editTool->addSeparator();
    editTool->addAction(zoomInAction);
    editTool->addAction(zoomOutAction);

    //旋转工具条
    rotateTool = addToolBar("Rotate");
    rotateTool->addAction(rotate90Action);
    rotateTool->addAction(rotate180Action);
    rotateTool->addAction(rotate270Action);

    //撤销和重做工具条
    doToolBar = addToolBar("DoEdit");
    doToolBar->addAction(undoAction);
    doToolBar->addAction(redoAction);


    /////////////////////////////////////////////////////////////
    fontToolBar =addToolBar("Font");
    fontToolBar->addWidget(fontLabel1);
    fontToolBar->addWidget(fontComboBox);
    fontToolBar->addWidget(fontLabel2);
    fontToolBar->addWidget(sizeComboBox);

    fontToolBar->addSeparator();

    fontToolBar->addWidget(boldBtn);
    fontToolBar->addWidget(italicBtn);
    fontToolBar->addWidget(underlineBtn);

    fontToolBar->addSeparator();

    fontToolBar->addWidget(colorBtn);

    ////////////////////////////////////////////////////////////

    //对齐工具条
    listToolBar = addToolBar("list");
    listToolBar->addWidget(listLabel);
    listToolBar->addWidget(listComboBox);
    listToolBar->addSeparator();
    listToolBar->addActions(actionGroup->actions());


}


//以上，便完成了程序总体的界面设计
//之后，则需要将相应的动作与具体的事件相互关联，
//使其能够完成相应的功能

//其中，需要完成的操作主要有：
//添加相应的槽函数，并完成槽函数的定义
//关联信号与槽函数，也即添加事件关联


//////////////////////////////////////////////////////


//文件操作的功能

//creates new file


void MyWord::showNewFile()
{
    //新建一个自创的窗口
    MyWord *newCent = new MyWord;
    //将新窗口显示出来
    newCent->show();
}

void MyWord::showOpenFile()
{
    filename = QFileDialog::getOpenFileName(this);
    if(filename.isEmpty())
    {
        if(Cent->text->document()->isEmpty())
        {
            loadFile(filename);
        }
        else
        {
            MyWord *newCentWid = new MyWord;
            newCentWid->show();
            newCentWid->loadFile(filename);
        }
    }

}


void MyWord::loadFile(QString filename)
{
    printf("file name : %s\n", filename.data());
    QFile file(filename);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream textStream(&file);
        while(!textStream.atEnd())
        {
            Cent->text->append(textStream.readLine());
            printf("read line\n");
        }
        printf("end\n");
    }
}

void MyWord::showPrintText()
{
    //新建一个QPrinter对象
    QPrinter printer;

    //创建一个QPrintDialog对象，参数为QPrinter对象
    QPrintDialog printDialog(&printer, this);

    //判断打印对话框显示后用户是否单击“打印”按钮
    if(printDialog.exec())
    {
        //获得QTextEdit对象的文档
        QTextDocument *doc = Cent->text->document();
        doc->print(&printer);
    }
}


void MyWord::showPrintImage()
{
    //新建一个QPrinter对象
    QPrinter printer;
    //创建一个QPrintDialog对象
    QPrintDialog printDialog(&printer, this);
    //判断打印对话框显示后用户是否单击“打印”按钮
    if(printDialog.exec())
    {
        //创建一个QPainter对象，并指定绘图设备为一个QPrinter对象
        QPainter painter(&printer);
        //获得QPainter对象的视图矩形区域
        QRect rect = painter.viewport();
        //获得图像的大小
        QSize sz = img.size();
        //按照图形的比例大小重新设置视图矩形区域
        sz.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), sz.width(), sz.height());

        //设置QPainter窗口大小为图像大小
        painter.setWindow(img.rect());
        //打印图像
        painter.drawImage(0, 0, img);
    }
}

void MyWord::showZoomIn()
{
    //有效性判断
    if(img.isNull())
        return;

    //创建一个QMatrix类的实例
    QMatrix matrix;
    //分别按照2倍比例对水平和垂直方向进行放大，并将当前显示的图形按照该坐标矩阵进行转换
    matrix.scale(2, 2);
    img = img.transformed(matrix);
    //重新设置显示图形
    Cent->imageLabel->setPixmap(QPixmap::fromImage(img));
}

void MyWord::showZoomOut()
{
    if(img.isNull())
        return;

    QMatrix matrix;
    matrix.scale(0.5 , 0.5);
    img = img.transformed(matrix);
    Cent->imageLabel->setPixmap(QPixmap::fromImage(img));
}


void MyWord::showRotate90()
{
    //还是有效性判断
    if(img.isNull())
        return;

    //然后再创建一个QMatrix对象
    QMatrix matrix;
    //设置使其旋转90度
    matrix.rotate(90);
    //使图形按照设置的方式进行转换
    img = img.transformed(matrix);
    //重新设置显示图形
    Cent->imageLabel->setPixmap(QPixmap::fromImage(img));
}


void MyWord::showRotate180()
{
    if(img.isNull())
        return;

    QMatrix matrix;
    matrix.rotate(180);
    img = img.transformed(matrix);
    Cent->imageLabel->setPixmap(QPixmap::fromImage(img));
}


void MyWord::showRotate270()
{
    if(img.isNull())
        return;

    QMatrix matrix;
    matrix.rotate(270);
    img = img.transformed(matrix);
    Cent->imageLabel->setPixmap(QPixmap::fromImage(img));
}



void MyWord::showMirrorVertical()
{
    //首先是有效性判断
    if(img.isNull())
        return;

    //然后是对图形进行镜像转换
    //其中mirrored函数的两个参数分别是(horizontal, vertical)
    img = img.mirrored(false, true);

    Cent->imageLabel->setPixmap(QPixmap::fromImage(img));
}

void MyWord::showMirrorHorizontal()
{
    if(img.isNull())
        return;

    img = img.mirrored(true, false);
    Cent->imageLabel->setPixmap(QPixmap::fromImage(img));
}


//以上便完成了菜单栏中各个命令动作的所有功能，但还没有文本编辑功能
//所以下面就是对文本编辑功能的补充


//////////////////////////////////////////////////////////

//设置字体

void MyWord::showFontComboBox(QString comboStr)
{
    //创建一个QTextCharFormat对象
    QTextCharFormat fmt;

    //选择的字体名称设置给QTextCharFormat对象
    fmt.setFontFamily(comboStr);

    //将新的格式应用到光标选区内的字符
    mergeFormat(fmt);
}

//所有对于QTexhDocument进行的修改都是通过QTextCursor类来完成的
void MyWord::mergeFormat(QTextCharFormat format)
{
    //获得编辑框中的光标
    QTextCursor cursor = Cent->text->textCursor();

    //若光标没有高亮选区，则将光标所在处的词作为选区
    if(!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);

    //调用QTextCursor的mergeCharFormat()函数将参数所表示的格式
    //应用到光标所在处的字符上
    cursor.mergeCharFormat(format);

    //调用QTextEdit的mergeCurrentCharFormat()函数将格式
    //应用到选取内的所有字符上
    Cent->text->mergeCurrentCharFormat(format);
}

//设置选定文字的字号大小
void MyWord::showSizeSpinBox(QString spinValue)
{
    //创建一个QTextCharFormat对象，用于对文本字符格式的设置
    QTextCharFormat fmt;

    //设置格式，这里是设置字体大小
    fmt.setFontPointSize(spinValue.toFloat());

    //将设置好的格式应用到选区内的所有字符上
    Cent->text->mergeCurrentCharFormat(fmt);
}


//设置字体加粗
void MyWord::showBoldBtn()
{
    //创建一个QTextCharFormat对象
    QTextCharFormat fmt;

    //设置格式为字体加粗
    fmt.setFontWeight(boldBtn->isChecked() ? QFont::Bold : QFont::Normal);

    //将设置好的格式应用到选区内的所有字符上
    Cent->text->mergeCurrentCharFormat(fmt);
}

//设置字体倾斜
void  MyWord::showItalicBtn()
{
    QTextCharFormat fmt;

    fmt.setFontItalic(italicBtn->isChecked());

    Cent->text->mergeCurrentCharFormat(fmt);
}



//设置文字下划线
void MyWord::showUnderlineBtn()
{
    QTextCharFormat fmt;

    fmt.setFontUnderline(underlineBtn->isChecked());

    Cent->text->mergeCurrentCharFormat(fmt);
}


//设置文字颜色
void MyWord::showColorBtn()
{
    //使用标准颜色对话框的方式，当单机出发颜色按钮时，
    //弹出标准颜色对话框选择颜色
    QColor color = QColorDialog::getColor(Qt::red, this);

    if(color.isValid())
    {
        QTextCharFormat fmt;
        fmt.setForeground(color);
        Cent->text->mergeCurrentCharFormat(fmt);
    }
}




//设置字符格式
//当光标所在处的字符格式发生变化时调用此槽函数，
//函数根据新的字符格式将工具栏上各个控件的显示更新
void MyWord::showCurrentFormatChanged(const QTextCharFormat &fmt)
{
    //
    fontComboBox->setCurrentIndex(fontComboBox->findText(fmt.fontFamily()));

    //
    sizeComboBox->setCurrentIndex(sizeComboBox->findText(
                                      QString::number(fmt.fontPointSize())));

    //
    boldBtn->setChecked(fmt.font().bold());

    //
    italicBtn->setChecked(fmt.fontItalic());

    //
    underlineBtn->setChecked(fmt.fontUnderline());
}


//以上部分便是对于文本编辑功能的实现

///////////////////////////////////////////////////////////////////////////////////

//以下便是对于排版功能的实现


//完成对按下某个对齐按钮的响应，使其按指定格式对齐
//其中调用了QTextEdit的setAlignment()函数来实现当前段落的对齐调整
void MyWord::showAlignment(QAction *act)
{
    if(act == leftAction)
        Cent->text->setAlignment(Qt::AlignLeft);
    if(act == rightAction)
        Cent->text->setAlignment(Qt::AlignRight);
    if(act == centerAction)
        Cent->text->setAlignment(Qt::AlignCenter);
    if(act == justifyAction)
        Cent->text->setAlignment(Qt::AlignJustify);
}


////响应文本中光标位置处发生改变的信号
void MyWord::showCursorPositionChanged()
{
    if(Cent->text->alignment() == Qt::AlignLeft)
        leftAction->setChecked(true);
    if(Cent->text->alignment() == Qt::AlignRight)
        rightAction->setChecked(true);
    if(Cent->text->alignment() == Qt::AlignCenter)
        centerAction->setChecked(true);
    if(Cent->text->alignment() == Qt::AlignJustify)
        justifyAction->setChecked(true);
}


////实现文本排序
void MyWord::showList(int index)
{
    //获得编辑框的QTextCursor对象指针
    QTextCursor cursor = Cent->text->textCursor();

    if(index != 0)
    {
        //从下拉列表框中选择二确定QTextListFormat的style属性值
        QTextListFormat::Style style = QTextListFormat::ListDisc;

        switch(index)
        {
        default:
        case 1:
            style = QTextListFormat::ListDisc; break;
        case 2:
            style = QTextListFormat::ListCircle; break;
        case 3:
            style = QTextListFormat::ListSquare; break;
        case 4:
            style = QTextListFormat::ListDecimal; break;
        case 5:
            style = QTextListFormat::ListLowerAlpha; break;
        case 6:
            style = QTextListFormat::ListUpperAlpha; break;
        case 7:
            style = QTextListFormat::ListLowerRoman; break;
        case 8:
            style = QTextListFormat::ListUpperRoman; break;
        }

        //设置缩进值,并将设置的格式应用到光标所在处的文本处
        //以下begin和end之间的内容，这两个函数的作用是设定这两个函数之间的
        //所有操作相当于一个动作,如果需要撤销或恢复，则这些动作将同时被撤销
        //或恢复
        cursor.beginEditBlock();
        QTextBlockFormat blockFmt = cursor.blockFormat();
        QTextListFormat listFmt;
        if(cursor.currentList())
        {
            listFmt = cursor.currentList()->format();
        }
        else
        {
            listFmt.setIndent(blockFmt.indent() + 1);
            blockFmt.setIndent(0);
            cursor.setBlockFormat(blockFmt);
        }
        listFmt.setStyle(style);
        cursor.createList(listFmt);
        cursor.endEditBlock();
    }
    else
    {
        QTextBlockFormat bfmt;
        bfmt.setObjectIndex(-1);
        cursor.mergeBlockFormat(bfmt);

    }
}


