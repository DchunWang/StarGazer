#include "mapwidget.h"
#include <QSlider>
#include <QGridLayout>
#include <QFile>
#include <QTextStream>
#include <QGraphicsScene>
#include <math.h>

MapWidget::MapWidget()
{
    //用于读取描述地图信息的文件（包括地图名及经纬度等信息
    readMap();
    zoom = 50;
    int width = map.width();
    int height = map.height();

    //新建一个QGraphicsScene对象为主窗口连接一个场景
    QGraphicsScene *scene = new QGraphicsScene(this);
    //限定场景的显示区域为地图的大小
    scene->setSceneRect(-width/2, -height/2, width, height);
    setScene(scene);
    setCacheMode(CacheBackground);

    //用于地图缩放的滑动条
    /* 新建一个QSlider对象作为地图的缩放控制，设置地图缩放比例值范围
     * 为0~100， 当前初始值为50，并将缩放控制条的valueChanged()信号
     * 与地图缩放slotZoom()槽函数关联
     */
    QSlider *slider = new QSlider;
    slider->setOrientation(Qt::Vertical);
    slider->setRange(1,100);
    slider->setTickInterval(10);
    slider->setValue(50);
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(slotZoom(int)));

    QLabel *zoominLabel = new QLabel;
    zoominLabel->setScaledContents(true);
    zoominLabel->setPixmap(QPixmap("zoomin.png"));

    QLabel *zoomoutLabel = new QLabel;
    zoomoutLabel->setScaledContents(true);
    zoomoutLabel->setPixmap(QPixmap("zoomout.png"));

    //坐标值显示区
    QLabel *label1 = new QLabel(tr("GraphicsView:"));
    viewCoord = new QLabel;
    QLabel *label2 = new QLabel(tr("GraphicsScene:"));
    sceneCoord = new QLabel;
    QLabel *label3 = new QLabel(tr("map:"));
    mapCoord = new QLabel;

    //坐标显示布局
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(label1, 0, 0);
    gridLayout->addWidget(viewCoord, 0, 1);
    gridLayout->addWidget(label2, 1, 0);
    gridLayout->addWidget(sceneCoord, 1, 1);
    gridLayout->addWidget(label3, 2, 0);
    gridLayout->addWidget(mapCoord, 2, 1);
    gridLayout->setSizeConstraint(QLayout::SetFixedSize);

    QFrame *coordFrame = new QFrame;
    coordFrame->setLayout(gridLayout);

    //缩放控制子布局
    QVBoxLayout *zoomLayout = new QVBoxLayout;
    zoomLayout->addWidget(zoominLabel);
    zoomLayout->addWidget(slider);
    zoomLayout->addWidget(zoomoutLabel);

    //坐标显示区域布局
    QVBoxLayout *coordLayout = new QVBoxLayout;
    coordLayout->addWidget(coordFrame);
    coordLayout->addStretch();

    //主布局
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(zoomLayout);
    mainLayout->addLayout(coordLayout);
    mainLayout->addStretch();
    mainLayout->setMargin(30);
    mainLayout->setSpacing(10);
    setLayout(mainLayout);
    setWindowTitle(tr("Qt Map"));
    setMinimumSize(600, 400);

}

//读取地图信息的函数
void MapWidget::readMap()
{
    QString mapName;
    //新建一个QFile对象，"maps.txt"是描述地图信息的文本文件
    QFile mapFile("maps.txt");
    //以”只读"方式打开此文件
    int ok = mapFile.open(QIODevice::ReadOnly);
    //分别读取地图的名称和四个经纬度信息
    if(ok)
    {
        QTextStream ts(&mapFile);
        if(!ts.atEnd())
        {
            ts>>mapName;
            ts >> x1 >> y1 >> x2 >>y2;
        }
    }
    //将地图读取至私有变量map中
    map.load(mapName);
}

//实现地图缩放
void MapWidget::slotZoom(int value)
{
    qreal s;
    //放大
    if(value > zoom)
    {
        s = pow(1.01, (value-zoom));
    }
    else
    {
        //缩小
        s = pow(1/1.01, (zoom-value));
    }
    scale(s, s);
    zoom = value;
}

//重载QGraphicsView类的drawBackground()函数
void MapWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->drawPixmap(int(sceneRect().left()), int(sceneRect().top()),map);
}

//重载鼠标移动事件,完成某点在各层坐标中的映射及显示
void MapWidget::mouseMoveEvent(QMouseEvent *event)
{
    //QGraphicsView坐标
    QPoint viewPoint = event->pos();
    viewCoord->setText(QString::number(viewPoint.x()) + "," +
                       QString::number(viewPoint.y()));

    //QGraphicsScene坐标
    QPointF scenePoint = mapToMap(viewPoint);
    sceneCoord->setText(QString::number(scenePoint.x()) + "," +
                        QString::number(scenePoint.y()));

    //地图坐标（经纬度值)
    QPointF latLon = mapToMap(scenePoint);
    mapCoord->setText(QString::number(latLon.x()) + "," +
                      QString::number(latLon.y()));
}

//完成从场景坐标到地图坐标的转换
QPointF MapWidget::mapToMap(QPointF p)
{
    QPointF latLon;
    qreal w = sceneRect().width();
    qreal h = sceneRect().height();
    qreal lon = y1 - ((h/2 + p.y()) * abs(y1-y2)/h);
    qreal lat = x1 + ((w/2 + p.x()) * abs(x1-x2)/w);

    latLon.setX(lat);
    latLon.setY(lon);
    return latLon;
}

