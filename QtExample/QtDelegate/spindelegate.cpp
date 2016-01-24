#include "spindelegate.h"
#include <QSpinBox>


spinDelegate::spinDelegate(QObject *parent)
    :QItemDelegate(parent)
{

}

QWidget *spinDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                    const QModelIndex &index) const
{
    QSpinBox *editor = new QSpinBox(parent);
    editor->setRange(0, 10000);
    editor->installEventFilter(const_cast<spinDelegate *>(this));
    return editor;
}

void spinDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    int value = index.model()->data(index).toInt();
    QSpinBox *box = static_cast<QSpinBox *>(editor);
    box->setValue(value);
}

void spinDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                const QModelIndex &index) const
{
    QSpinBox *box = static_cast<QSpinBox *>(editor);
    int value = box->value();
    model->setData(index, value);
}

void spinDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                                        const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

