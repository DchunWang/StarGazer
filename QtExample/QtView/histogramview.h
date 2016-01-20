#ifndef HISTOGRAMVIEW_H
#define HISTOGRAMVIEW_H

#include <QAbstractItemView>
#include <QItemSelectionModel>
#include <QRegion>
#include <QMouseEvent>

/**
 * @brief The HistogramView class
 * 自定义的类HistogramView继承自QAbstractView类，
 * 用于对表格数据进行柱状图的显示
 */

class HistogramView : public QAbstractItemView
{
    Q_OBJECT
public:
    HistogramView(QWidget *parent = 0);

    /* QAbstractItemView类中的这些纯虚函数不一定都要事先，
     * 可以根据需要选择性地实现，但一定要声明
     */

    //虚函数声明
    QRect visualRect(const QModelIndex &index) const;
    void scrollTo(const QModelIndex &index, ScrollHint hint = EnsureVisible);
    QModelIndex indexAt(const QPoint &point) const;
    //为selection赋初值
    void setSelectionModel(QItemSelectionModel *selectionModel);
    QRegion itemRegion(QModelIndex index);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);

protected slots:
    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);

protected:
    //虚函数声明
    QModelIndex moveCursor(QAbstractItemView::CursorAction cursorAction,
                           Qt::KeyboardModifiers modifiers);
    int horizontalOffset() const;
    int verticalOffset() const;
    bool isIndexHidden(const QModelIndex &index) const;
    void setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags flags);
    QRegion visualRegionForSelection(const QItemSelection &selection) const;
private:
    //用于保存于视图选择相关的内容
    QItemSelectionModel *selections;
    //用于保存其中某一类型柱状图的区域范围，而每个区域是QList中的一个值
    QList<QRegion> MRegionList;
    QList<QRegion> FRegionList;
    QList<QRegion> SRegionList;
};

#endif // HISTOGRAMVIEW_H
