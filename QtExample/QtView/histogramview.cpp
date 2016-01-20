#include "histogramview.h"
#include <QPainter>


HistogramView::HistogramView(QWidget *parent)
    : QAbstractItemView(parent)
{

}

//paintEvent函数完成具体柱状统计图绘制的工作
void HistogramView::paintEvent(QPaintEvent *)
{
    QPainter painter(viewport());
    painter.setPen(Qt::black);
    int x0 = 40;
    int y0 = 250;

    //完成x、y坐标轴的绘制，并标注坐标轴的变量

    //y坐标轴
    painter.drawLine(x0, y0, 40, 30);
    painter.drawLine(38, 32, 40, 30);
    painter.drawLine(40, 30, 42, 32);
    painter.drawText(20, 30, tr("人数"));
    for(int i = 1; i < 5; ++i)
    {
        painter.drawLine(-1, -1*50, 1, -i*50);
        painter.drawText(-20, -i*50, tr("%1").arg(i*5));
    }

    //x坐标轴
    painter.drawLine(x0, y0, 540, 250);
    painter.drawLine(538, 248, 540, 250);
    painter.drawLine(540, 250, 538, 252);
    painter.drawText(545, 250, tr("部门"));

    int posD = x0 + 20;
    int row;
    for(row = 0; row < model()->rowCount(rootIndex()); ++row)
    {
        QModelIndex index = model()->index(row, 0, rootIndex());
        QString dep = model()->data(index).toString();
        painter.drawText(posD, y0+20, dep);
        posD += 50;
    }

    //完成表格第1列数据的柱状统计图的绘制

    //男
    int posM = x0 + 20;
    for(row = 0; row < model()->rowCount(rootIndex()); ++row)
    {
        QModelIndex index = model()->index(row, 1, rootIndex());
        int male = model()->data(index).toDouble();
        int width = 10;
        if(selections->isSelected(index))
            painter.setBrush(QBrush(Qt::blue, Qt::Dense3Pattern));
        else
            painter.setBrush(Qt::blue);
        painter.drawRect(QRect(posM, y0-male*10, width, male*10));

        QRegion regionM(posM, y0-male*10, width, male*10);
        MRegionList << regionM;
        posM += 50;

    }

   //完成表格第2列数据的柱状统计图的绘制
    //女
    int posF = x0 + 30;
    for(row = 0; row < model()->rowCount(rootIndex()); ++row)
    {
        QModelIndex index = model()->index(row, 2, rootIndex());
        int female = model()->data(index).toDouble();
        int width = 10;

        //使用不同画刷颜色区别选中与未选中的数据选
        if(selections->isSelected(index))
            painter.setBrush(QBrush(Qt::red, Qt::Dense3Pattern));
        else
            painter.setBrush(Qt::red);

        painter.drawRect(QRect(posF, y0-female*10, width, female*10));
        QRegion regionF(posF, y0-female*10, width, female*10);

        //将此数据所占据的区域保存到FRegionList列表中，为后面的数据项选择做准备
        FRegionList<<regionF;
        posF += 50;
    }

    //完成表格第3列数据的柱状统计图的绘制
    int posS = x0 + 40;
    for(row = 0; row < model()->rowCount(rootIndex()); ++row)
    {
        QModelIndex index = model()->index(row, 3, rootIndex());
        int retire = model()->data(index).toDouble();
        int width = 10;
        if(selections->isSelected(index))
            painter.setBrush(QBrush(Qt::green, Qt::Dense3Pattern));
        else
            painter.setBrush(Qt::green);

        painter.drawRect(QRect(posS, y0-retire*10, width, retire*10));
        QRegion regionS(posS, y0-retire*10, width, retire*10);
        SRegionList << regionS;
        posS += 50;
    }
}


//dataChanged()函数实现当Model中的数据更改时，调用绘图设备的update()函数进行更新，反映数据的变化
void HistogramView::dataChanged(const QModelIndex &topLeft,
                                const QModelIndex &bottomRight)
{
    QAbstractItemView::dataChanged(topLeft, bottomRight);
    viewport()->update();
}

void HistogramView::setSelectionModel(QItemSelectionModel *selectionModel)
{
    selections = selectionModel;
}

//完成到数据项发生变化时调用update()函数，重绘绘图设备即可工作
void HistogramView::selectionChanged(const QItemSelection &selected,
                                     const QItemSelection &deselected)
{
    viewport()->update();
}

//鼠标按下事件，在调用setSelection()函数时确定鼠标单击点
//是否在某个数据项的区域内，并设置选择项
void HistogramView::mousePressEvent(QMouseEvent *event)
{
    QAbstractItemView::mousePressEvent(event);
    setSelection(QRect(event->pos().x(), event->pos().y(), 1, 1),
                 QItemSelectionModel::SelectCurrent);
}

void HistogramView::setSelection(const QRect &rect,
                                 QItemSelectionModel::SelectionFlags flags)
{
    //获取总行数
    int rows = model()->rowCount(rootIndex());
    //获取总列数
    int columns = model()->columnCount(rootIndex());

    //保存被选中的数据项的Index值
    QModelIndex selectedIndex;
    for(int row = 0; row < rows; ++row)
    {
        for(int column = 1; column < columns; ++column)
        {
            QModelIndex index = model()->index(row, column, rootIndex());
            QRegion region = itemRegion(index);
            if(!region.intersected(rect).isEmpty())
            {
                selectedIndex = index;
            }
        }
    }
        if(selectedIndex.isValid())
            selections->select(selectedIndex, flags);
        else
        {
            QModelIndex noIndex;
            selections->select(noIndex, flags);
        }
}

QModelIndex HistogramView::indexAt(const QPoint &point) const
{
    QPoint newPoint(point.x(), point.y());
    QRegion region;

    //男列
    foreach(region, MRegionList)
    {
        if(region.contains(newPoint))
        {
            int row = MRegionList.indexOf(region);
            QModelIndex index = model()->index(row, 1, rootIndex());
            return index;
        }
    }

    //女列
    foreach(region, FRegionList)
    {
        if(region.contains(newPoint))
        {
            int row = FRegionList.indexOf(region);
            QModelIndex index = model()->index(row, 2, rootIndex());
            return index;
        }
    }

    //合计列
    foreach(region, SRegionList)
    {
        if(region.contains(newPoint))
        {
            int row = SRegionList.indexOf(region);
            QModelIndex index = model()->index(row, 3, rootIndex());
            return index;
        }
    }

    return QModelIndex();
}

//由于没有用到下面这些函数的功能，所以没有具体实现内容，但仍然要写出函数体的框架

QRect HistogramView::visualRect(const QModelIndex &index) const {}
void HistogramView::scrollTo(const QModelIndex &index, ScrollHint){}
QModelIndex HistogramView::moveCursor(QAbstractItemView::CursorAction cursorAction,
                                      Qt::KeyboardModifiers modifiers){}
int HistogramView::horizontalOffset() const{}
int HistogramView::verticalOffset() const {}
bool HistogramView::isIndexHidden(const QModelIndex &index) const {}
QRegion HistogramView::visualRegionForSelection(const QItemSelection
                                                &selection) const {}

//下面的这个就是用到了的
QRegion HistogramView::itemRegion(QModelIndex index)
{
    QRegion region;
    if(index.column() == 1)     //男
        region = MRegionList[index.row()];
    if(index.column() == 2)     //女
        region = FRegionList[index.row()];
    if(index.column() == 3)     //合计
        region = SRegionList[index.row()];

    return region;
}






