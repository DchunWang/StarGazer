#ifndef DATEDELEGATE_H
#define DATEDELEGATE_H

#include <QItemDelegate>


class DateDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    DateDelegate(QObject *parent = 0);

    //完成创建控件的工作
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;

    //设置控件显示的数据,将Model中的数据更新至Delegate中，相当于一个初始化工作
    void setEditorData(QWidget *editor, const QModelIndex &index) const;

    //将Delegate中对数据的改变更新至Model中
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;

    //更新控件区的显示
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const;
};

#endif // DATEDELEGATE_H
