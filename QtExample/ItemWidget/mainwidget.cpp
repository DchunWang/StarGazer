#include "mainwidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSlider>
#include <QGroupBox>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    angle = 0;
    scaleValue = 5;
    shearValue = 5;
    translateValue = 50;
    QGraphicsScene *scene = new QGraphicsScene;

    //限定新建QGraphicsScene对象的显示区域
    scene->setSceneRect(-200, -200, 400, 400);

    QPixmap *pixmap = new QPixmap("image.png");
    pixItem = new PixItem(pixmap);
    scene->addItem(pixItem);

    //新建一个视图对象
    view = new QGraphicsView;
    //将视图对象与场景相连
    view->setScene(scene);
    //设置视图的最小尺寸
    view->setMinimumSize(500, 500);

    ctrlFrame = new QFrame;
    //新建主窗体右侧的控制面板区
    createControlFrame();

    //主窗口布局
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setMargin(10);
    mainLayout->setSpacing(20);
    mainLayout->addWidget(view);
    mainLayout->addWidget(ctrlFrame);
    setLayout(mainLayout);
    //设置主窗体标题
    setWindowTitle(tr("Graphics Item Transformation"));


}

MainWidget::~MainWidget()
{

}

//右侧控制面板区包括几个滑块区
void MainWidget::createControlFrame()
{
    //旋转控制
    QSlider *rotateSlider = new QSlider;
    rotateSlider->setOrientation(Qt::Horizontal);
    rotateSlider->setRange(0, 360);
    QHBoxLayout *rotateLayout = new QHBoxLayout;
    rotateLayout->addWidget(rotateSlider);
    QGroupBox *rotateGroup = new QGroupBox(tr("Rotate"));
    rotateGroup->setLayout(rotateLayout);

    //缩放控制
    QSlider *scaleSlider = new QSlider;
    scaleSlider->setOrientation(Qt::Horizontal);
    scaleSlider->setRange(0, 2*scaleValue);
    scaleSlider->setValue(scaleValue);
    QHBoxLayout *scaleLayout = new QHBoxLayout;
    scaleLayout->addWidget(scaleSlider);
    QGroupBox *scaleGroup = new QGroupBox(tr("Scale"));
    scaleGroup->setLayout(scaleLayout);

    //切变控制
    QSlider *shearSlider = new QSlider;
    shearSlider->setOrientation(Qt::Horizontal);
    shearSlider->setRange(0, 2*shearValue);
    shearSlider->setValue(shearValue);
    QHBoxLayout *shearLayout = new QHBoxLayout;
    shearLayout->addWidget(shearSlider);
    QGroupBox *shearGroup = new QGroupBox(tr("Shear"));
    shearGroup->setLayout(shearLayout);

    //位移控制
    QSlider *translateSlider = new QSlider;
    translateSlider->setOrientation(Qt::Horizontal);
    translateSlider->setRange(0, 2*translateValue);
    translateSlider->setValue(translateValue);
    QHBoxLayout *translateLayout = new QHBoxLayout;
    translateLayout->addWidget(translateSlider);
    QGroupBox *translateGroup = new QGroupBox(tr("Translate"));
    translateGroup->setLayout(translateLayout);


    //控制面板布局
    QVBoxLayout *frameLayout = new QVBoxLayout;
    frameLayout->setMargin(10);
    frameLayout->setSpacing(20);
    frameLayout->addWidget(rotateGroup);
    frameLayout->addWidget(scaleGroup);
    frameLayout->addWidget(shearGroup);
    frameLayout->addWidget(translateGroup);

    ctrlFrame->setLayout(frameLayout);


    connect(rotateSlider, SIGNAL(valueChanged(int)), this, SLOT(slotRotate(int)));
    connect(scaleSlider, SIGNAL(valueChanged(int)), this, SLOT(slotScale(int)));
    connect(shearSlider, SIGNAL(valueChanged(int)), this, SLOT(slotShear(int)));
    connect(translateSlider, SIGNAL(valueChanged(int)), this, SLOT(slotTranslate(int)));
}

//实现图元旋转，要调用QGraphicsView类的rotate()函数
void MainWidget::slotRotate(int value)
{
    view->rotate(value - angle);
    angle = value;
}

//事项图元缩放，调用QGraphicsView类的scale()函数
void MainWidget::slotScale(int value)
{
    qreal s;
    if(value > scaleValue)
        s = pow(1.5, (value-scaleValue));
    else
        s = pow(1/1.5, (scaleValue-value));

    view->scale(s, s);

    scaleValue = value;
}

//实现图元切变，调用QGraphicsView类的shear()函数
void MainWidget::slotShear(int value)
{
    view->shear((value-shearValue)/10.0, 0);
    shearValue = value;
}

//实现图元位移，调用QGraphicsView类的translate()函数
void MainWidget::slotTranslate(int value)
{
    view->translate(value - translateValue, value-translateValue);
    translateValue = value;
}
