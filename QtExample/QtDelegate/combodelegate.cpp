#include "combodelegate.h"
#include <QComboBox>

comboDelegate::comboDelegate(QObject *parent)
    : QItemDelegate(parent)
{


}

QWidget *comboDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                     const QModelIndex &index) const
{
    QComboBox *editor = new QComboBox(parent);
    editor->addItem("工人");
    editor->addItem("农民");
    editor->addItem("医生");
    editor->addItem("律师");
    editor->addItem("军人");
    editor->installEventFilter(const_cast<comboDelegate*>(this));
    return editor;
}

void comboDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString str = index.model()->data(index).toString();
    QComboBox *box = static_cast<QComboBox *> (editor);
    int i = box->findText(str);
    box->setCurrentIndex(i);
}

void comboDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                 const QModelIndex &index) const
{
    QComboBox *box = static_cast<QComboBox *>(editor);
    QString str = box->currentText();
    model->setData(index,str);
}

void comboDelegate::updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem
                                         &option, const QModelIndex &index)const
{
    editor->setGeometry(option.rect);
}





