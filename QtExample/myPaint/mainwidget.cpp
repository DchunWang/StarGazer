#include "mainwidget.h"
#include <QColorDialog>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    paintArea = new PaintArea;

    shapeLabel = new QLabel(tr("画笔形状:"));
    //画笔形状选择下拉列表框
    shapeComboBox = new QComboBox;
    shapeComboBox->addItem(tr("line"), PaintArea::Line);
    shapeComboBox->addItem(tr("Rectangle"), PaintArea::Rectangle);
    shapeComboBox->addItem(tr("RoundRect"), PaintArea::RoundRect);
    shapeComboBox->addItem(tr("Ellipse"), PaintArea::Ellipse);
    shapeComboBox->addItem(tr("Polygon"), PaintArea::Polygon);
    shapeComboBox->addItem(tr("PolyLine"), PaintArea::Polyline);
    shapeComboBox->addItem(tr("Points"), PaintArea::Points);
    shapeComboBox->addItem(tr("Arc"), PaintArea::Arc);
    shapeComboBox->addItem(tr("Path"), PaintArea::Path);
    shapeComboBox->addItem(tr("Text"), PaintArea::Text);
    shapeComboBox->addItem(tr("Pixmap"), PaintArea::Pixmap);

    penColorLabel = new QLabel(tr("画笔颜色:"));
    //画笔颜色选择控件
    penColorFrame = new QFrame;
    penColorFrame->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    penColorFrame->setAutoFillBackground(true);
    penColorFrame->setPalette(QPalette(Qt::blue));
    //画笔颜色更改按钮
    changeBtn = new QPushButton(tr("更改"));

    penWidthLabel = new QLabel(tr("画笔线宽:"));
    //画笔线宽选择控件
    penWidthSpinBox = new QSpinBox;
    penWidthSpinBox->setRange(0, 24);

    penStyleLabel = new QLabel(tr("画笔风格:"));
    //画笔风格选择控件
    penStyleComboBox = new QComboBox;
    penStyleComboBox->addItem(tr("SolidLine"), static_cast<int>(Qt::SolidLine));
    penStyleComboBox->addItem(tr("DashLine"), static_cast<int>(Qt::DashLine));
    penStyleComboBox->addItem(tr("DotLine"), static_cast<int>(Qt::DotLine));
    penStyleComboBox->addItem(tr("DashDotLine"), static_cast<int>(Qt::DashDotLine));
    penStyleComboBox->addItem(tr("DashDotDotLine"), static_cast<int>(Qt::DashDotDotLine));
    penStyleComboBox->addItem(tr("CustomDashLine"), static_cast<int>(Qt::CustomDashLine));

    penCapLabel = new QLabel(tr("画笔顶帽:"));
    //画笔顶帽选择控件
    penCapComboBox = new QComboBox;
    penCapComboBox->addItem(tr("SquareCap"), Qt::SquareCap);
    penCapComboBox->addItem(tr("FlatCap"), Qt::FlatCap);
    penCapComboBox->addItem(tr("RoundCap"), Qt::RoundCap);


    penJoinLabel = new QLabel(tr("画笔连接点:"));
    //画笔连接点风格选择框控件
    penJoinComboBox = new QComboBox;
    penJoinComboBox->addItem(tr("BevelJoin"), Qt::BevelJoin);
    penJoinComboBox->addItem(tr("MiterJoin"), Qt::MiterJoin);
    penJoinComboBox->addItem(tr("RoundJoin"), Qt::RoundJoin);

    fillStyleLabel = new QLabel(tr("填充模式:"));
    //填充模式下拉列表选择框控件
    fillStyleComboBox = new QComboBox;
    fillStyleComboBox->addItem(tr("OddEventFill"), Qt::OddEvenFill);
    fillStyleComboBox->addItem(tr("WindingFill"), Qt::WindingFill);

    spreadLabel = new QLabel(tr("铺展效果:"));
    //铺展效果下拉列表控件
    spreadComboBox = new QComboBox;
    spreadComboBox->addItem(tr("PadSpread"), QGradient::PadSpread);
    spreadComboBox->addItem(tr("RepeatSpread"), QGradient::RepeatSpread);
    spreadComboBox->addItem(tr("ReflectSpread"), QGradient::ReflectSpread);

    brushColorLabel = new QLabel(tr("画刷颜色:"));
    //画刷颜色选择控件
    brushColorFrame = new QFrame;
    brushColorFrame->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    brushColorFrame->setAutoFillBackground(true);
    brushColorFrame->setPalette(QPalette(Qt::green));
    //画刷颜色更改按钮
    changeBtn2 = new QPushButton(tr("更改"));

    brushStyleLabel = new QLabel(tr("画刷风格:"));
    //画刷风格选择下拉列表控件
    brushStyleComboBox = new QComboBox;
    brushStyleComboBox->addItem(tr("SolidPattern"), static_cast<int>(Qt::SolidPattern));
    brushStyleComboBox->addItem(tr("Dense1Pattern"), static_cast<int>(Qt::Dense1Pattern));
    brushStyleComboBox->addItem(tr("Dense2Pattern"), static_cast<int>(Qt::Dense2Pattern));
    brushStyleComboBox->addItem(tr("Dense3Pattern"), static_cast<int>(Qt::Dense3Pattern));
    brushStyleComboBox->addItem(tr("Dense4Pattern"), static_cast<int>(Qt::Dense4Pattern));
    brushStyleComboBox->addItem(tr("Dense5Pattern"), static_cast<int>(Qt::Dense5Pattern));
    brushStyleComboBox->addItem(tr("Dense6Pattern"), static_cast<int>(Qt::Dense6Pattern));
    brushStyleComboBox->addItem(tr("Dense7Pattern"), static_cast<int>(Qt::Dense7Pattern));
    brushStyleComboBox->addItem(tr("NoBrush"), static_cast<int>(Qt::NoBrush));
    brushStyleComboBox->addItem(tr("HorPattern"), static_cast<int>(Qt::HorPattern));
    brushStyleComboBox->addItem(tr("VerPattern"), static_cast<int>(Qt::VerPattern));
    brushStyleComboBox->addItem(tr("BDiagPattern"), static_cast<int>(Qt::BDiagPattern));
    brushStyleComboBox->addItem(tr("FDiagPattern"), static_cast<int>(Qt::FDiagPattern));
    brushStyleComboBox->addItem(tr("CrossPattern"), static_cast<int>(Qt::CrossPattern));
    brushStyleComboBox->addItem(tr("DiagCrossPattern"), static_cast<int>(Qt::DiagCrossPattern));
    brushStyleComboBox->addItem(tr("LinearGradientPattern"), static_cast<int>(Qt::LinearGradientPattern));
    brushStyleComboBox->addItem(tr("RadialGradientPattern"), static_cast<int>(Qt::RadialGradientPattern));
    brushStyleComboBox->addItem(tr("ConicalGradientPattern"), static_cast<int>(Qt::ConicalGradientPattern));
    brushStyleComboBox->addItem(tr("TexturePattern"), static_cast<int>(Qt::TexturePattern));

    //右边布局
    rightLayout = new QGridLayout;
    rightLayout->addWidget(shapeLabel, 0, 0);
    rightLayout->addWidget(shapeComboBox, 0, 1);
    rightLayout->addWidget(penColorLabel, 1, 0);
    rightLayout->addWidget(penColorFrame, 1, 1);
    rightLayout->addWidget(changeBtn, 1, 2);
    rightLayout->addWidget(penWidthLabel, 2, 0);
    rightLayout->addWidget(penWidthSpinBox, 2, 1);
    rightLayout->addWidget(penStyleLabel, 3, 0);
    rightLayout->addWidget(penStyleComboBox, 3, 1);
    rightLayout->addWidget(penCapLabel, 4, 0);
    rightLayout->addWidget(penCapComboBox, 4, 1);
    rightLayout->addWidget(penJoinLabel, 5, 0);
    rightLayout->addWidget(penJoinComboBox, 5, 1);
    rightLayout->addWidget(fillStyleLabel, 6,  0);
    rightLayout->addWidget(fillStyleComboBox, 6,  1);
    rightLayout->addWidget(spreadLabel, 7, 0);
    rightLayout->addWidget(spreadComboBox, 7, 1);
    rightLayout->addWidget(brushColorLabel, 8, 0);
    rightLayout->addWidget(brushColorFrame, 8, 1);
    rightLayout->addWidget(changeBtn2, 8, 2);
    rightLayout->addWidget(brushStyleLabel, 9, 0);
    rightLayout->addWidget(brushStyleComboBox, 9, 1);

    //整体布局
    mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(paintArea);
    mainLayout->addLayout(rightLayout);
    mainLayout->setStretchFactor(paintArea, 1);
    mainLayout->setStretchFactor(rightLayout, 0);


    //添加事件关联
    connect(shapeComboBox, SIGNAL(activated(int)), this, SLOT(showShape(int)));
    connect(changeBtn, SIGNAL(clicked()), this, SLOT(showPenColor()));
    connect(penWidthSpinBox, SIGNAL(valueChanged(int)), this, SLOT(showPenWidth(int)));
    connect(penStyleComboBox, SIGNAL(activated(int)), this, SLOT(showPenStyle(int)));
    connect(penCapComboBox, SIGNAL(activated(int)), this, SLOT(showPenCap(int)));
    connect(penJoinComboBox, SIGNAL(activated(int)), this, SLOT(showPenCap(int)));
    connect(fillStyleComboBox, SIGNAL(activated(int)), this, SLOT(showFillStyle()));
    connect(spreadComboBox, SIGNAL(activated(int)), this, SLOT(showSpread()));
    connect(changeBtn2, SIGNAL(clicked()), this, SLOT(showBrushColor()));
    connect(brushStyleComboBox, SIGNAL(activated(int)), this, SLOT(showBrush(int)));



}

MainWidget::~MainWidget()
{

}


//以下是各槽函数的定义

//showShape()函数，根据当前下拉列表框中选择的选项，调用
//PaintArea类的setShape()函数设置PaintArea对象的形状参数
void MainWidget::showShape(int value)
{
    PaintArea::Shape shape = PaintArea::Shape(shapeComboBox->itemData(value,Qt::UserRole).toInt());
    paintArea->setShape(shape);
}

//showPenColor()函数，利用颜色标准 对话框QColorDialog获取所选的颜色，
//采用QFrame和QPushButton对象组合完成，QFrame对象负责显示当前所选择
//的颜色，QPushButton对象负责显示当前你所选择的颜色，QPushButton对象
//用于触发颜色标准对话框进行颜色的选择
void MainWidget::showPenColor()
{
    //获取颜色值
    QColor color = QColorDialog::getColor(static_cast<int>(Qt::blue));
    //设置颜色显示框中的面板颜色
    penColorFrame->setPalette(QPalette(color));
    //获取微调框中的数值
    int value = penWidthSpinBox->value();

    //获取画笔的风格属性值
    Qt::PenStyle style = Qt::PenStyle(penStyleComboBox->itemData(
                          penStyleComboBox->currentIndex(),Qt::UserRole).toInt());
    //获取画笔的顶帽的属性值
    Qt::PenCapStyle cap = Qt::PenCapStyle(penCapComboBox->itemData(
                          penCapComboBox->currentIndex(), Qt::UserRole).toInt());
    //获取画笔连接点的属性值
    Qt::PenJoinStyle join = Qt::PenJoinStyle(penJoinComboBox->itemData(
                             penJoinComboBox->currentIndex(), Qt::UserRole).toInt());
    //调用PaintArea对象的setPen()函数设置PaintArea对象的画笔属性
    paintArea->setPen(QPen(color, value, style, cap, join));
}

//showPenWidth(int)函数，调整画笔线宽的微调框，改变图的线宽大小
//参数是微调框中的数值
void MainWidget::showPenWidth(int value)
{
    //获取颜色值
    QColor color = penColorFrame->palette().color(QPalette::Window);
    //获取画笔风格
    Qt::PenStyle style = Qt::PenStyle(penStyleComboBox->itemData(
                            penStyleComboBox->currentIndex(), Qt::UserRole).toInt());
    //获取画笔顶帽样式
    Qt::PenCapStyle cap = Qt::PenCapStyle(penCapComboBox->itemData(
                            penCapComboBox->currentIndex(), Qt::UserRole).toInt());
    //获取画笔连接点
    Qt::PenJoinStyle join = Qt::PenJoinStyle(penJoinComboBox->itemData(
                            penJoinComboBox->currentIndex(), Qt::UserRole).toInt());

    //利用之前获取的画笔相关的属性值，包括画笔颜色、画笔线宽、画笔风格、画笔顶帽
    //及画笔连接点，共同构成QPen对象,并调用PaintArea对象的setPen()函数设置
    //PaintArea对象的画笔属性。
    paintArea->setPen(QPen(color, value, style, cap, join));
}


void MainWidget::showPenStyle(int styleValue)
{
    //获取颜色值
    QColor color = penColorFrame->palette().color(QPalette::Window);
    //获取线宽值
    int value = penWidthSpinBox->value();
    //获取画笔风格
    Qt::PenStyle style = Qt::PenStyle(penStyleComboBox->itemData(
                          styleValue, Qt::UserRole).toInt());
    //获取画笔顶帽
    Qt::PenCapStyle cap = Qt::PenCapStyle(penCapComboBox->itemData(
                          penCapComboBox->currentIndex(),Qt::UserRole).toInt());
    //获取画笔连接点
    Qt::PenJoinStyle join = Qt::PenJoinStyle(penJoinComboBox->itemData(
                          penJoinComboBox->currentIndex(), Qt::UserRole).toInt());
    //设置画笔对象
    paintArea->setPen(QPen(color, value, style, cap, join));
}


void MainWidget::showPenCap(int capValue)
{
    //获取颜色值
    QColor color = penColorFrame->palette().color(QPalette::Window);
    //获取线宽值
    int value = penWidthSpinBox->value();
    //获取画笔风格
    Qt::PenStyle style = Qt::PenStyle(penStyleComboBox->itemData(
                         penStyleComboBox->currentIndex(),Qt::UserRole).toInt());
    //获取画笔顶帽
    Qt::PenCapStyle cap = Qt::PenCapStyle(penCapComboBox->itemData(
                                              capValue,Qt::UserRole).toInt());
    //获取画笔连接点
    Qt::PenJoinStyle join = Qt::PenJoinStyle(penJoinComboBox->itemData(
                            penJoinComboBox->currentIndex(), Qt::UserRole).toInt());
    //设置画笔对象
    paintArea->setPen(QPen(color, value, style, cap, join));
}

void MainWidget::showPenJoin(int joinValue)
{
    //获取颜色值
    QColor color = penColorFrame->palette().color(QPalette::Window);

    //获取线宽值
    int value = penWidthSpinBox->value();
    //获取画笔风格
    Qt::PenStyle style = Qt::PenStyle(penStyleComboBox->itemData(
                         penStyleComboBox->currentIndex(), Qt::UserRole).toInt());
    //获取画笔顶帽
    Qt::PenCapStyle cap = Qt::PenCapStyle(penCapComboBox->itemData(
                         penCapComboBox->currentIndex(), Qt::UserRole).toInt());
    //获取画笔连接点
    Qt::PenJoinStyle join = Qt::PenJoinStyle(penJoinComboBox->itemData(joinValue,
                                             Qt::UserRole).toInt());
    //设置画笔对象
    paintArea->setPen(QPen(color, value, style, cap, join));
}

void MainWidget::showFillStyle()
{
    Qt::FillRule rule = Qt::FillRule(fillStyleComboBox->itemData(
                        fillStyleComboBox->currentIndex(), Qt::UserRole).toInt());
    paintArea->setFillRule(rule);
}

void MainWidget::showSpread()
{
    spread = QGradient::Spread(spreadComboBox->itemData(
                        spreadComboBox->currentIndex(), Qt::UserRole).toInt());
}

//打开颜色对话框并设置画刷颜色用showBrushColor()函数和showBrush()函数
//其中并不是调用paintArea对象的setBrush()函数，而是调用showBrush()函数来
//设置显示区的画刷属性

void MainWidget::showBrushColor()
{
    QColor color = QColorDialog::getColor(static_cast<int>(Qt::blue));
    brushColorFrame->setPalette(QPalette(color));
    showBrush(brushStyleComboBox->currentIndex());
}


void MainWidget::showBrush(int value)
{
    //获取画刷的额颜色
    QColor color = brushColorFrame->palette().color(QPalette::Window);

    //获得所选的画刷的风格，若选择的是渐变或纹理图案，则需要进一步的处理
    Qt::BrushStyle style = Qt::BrushStyle(brushStyleComboBox->itemData(
                                              value, Qt::UserRole).toInt());

    if(style == Qt::LinearGradientPattern)      //如果选择的是线性渐变
    {
        //创建线性渐变类对象，其中需要两个参数，分别表示起止点的位置
        QLinearGradient linearGradient(0, 0, 400, 400);
        //设置起止的颜色
        linearGradient.setColorAt(0.0, Qt::white);
        linearGradient.setColorAt(0.2, color);
        linearGradient.setColorAt(1.0, Qt::black);

        linearGradient.setSpread(spread);

        paintArea->setBrush(linearGradient);
    }
    else if(style == Qt::RadialGradientPattern)     //如果选择的是圆形渐变
    {
        //创建圆形渐变对象，其中需要三个参数，分别表示圆心位置、半径值和焦点位置
        QRadialGradient radialGradient(200, 200, 150, 150, 100);

        radialGradient.setColorAt(0.0, Qt::white);
        radialGradient.setColorAt(0.2, color);
        radialGradient.setColorAt(1.0, Qt::black);
        radialGradient.setSpread(spread);

        paintArea->setBrush(radialGradient);
    }
    else if(style == Qt::ConicalGradientPattern)    //如果选择的是锥形渐变
    {
        //创建锥形渐变对象，其中需要两个参数，分别是锥形的顶点位置和渐变分界线与水平方向的夹角
        QConicalGradient conicalGradient(200, 200, 300);

        conicalGradient.setColorAt(0.0,Qt::white);
        conicalGradient.setColorAt(0.2, color);
        conicalGradient.setColorAt(1.0, Qt::black);

        paintArea->setBrush(conicalGradient);
    }
    else if(style == Qt::TexturePattern)            //如果选择的是文本
    {
        paintArea->setBrush(QBrush(QPixmap("myPic.png")));
    }
    else
    {
        paintArea->setBrush(QBrush(color, style));
    }
}
