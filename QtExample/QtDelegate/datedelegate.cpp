#include "datedelegate.h"
#include <QDateTimeEdit>

DateDelegate::DateDelegate(QObject *parent)
    :QItemDelegate(parent)
{

}

QWidget *DateDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                    const QModelIndex &index) const
{
    //新建一个QDateTimeEdit对象作为编辑时的输入控件
    QDateTimeEdit *editor = new QDateTimeEdit(parent);
    //设置此QDateTimeEdit对象的显示格式为yyyy-MM-dd，此为ISO标准显示方式
    editor->setDisplayFormat("yyyy-MM-dd");
    //设置日历选择的显示以Popup的方式，即下拉菜单方式显示
    editor->setCalendarPopup(true);
    //调用QObject类的installEventFilter()函数安装事件过滤器,
    //使DateDelegate能够捕获QDateTimeEdit对象的事件
    editor->installEventFilter(const_cast<DateDelegate *>(this));
    return editor;
}

void DateDelegate::setEditorData(QWidget *editor,
                                 const QModelIndex &index) const
{
    //获取指定index数据项的数据
    QString dateStr = index.model()->data(index).toString();
    //通过fromString()函数将以QString类型表示的日期数据转换为QDate类型
    QDate date = QDate::fromString(dateStr, Qt::ISODate);

    //将editor转换为QDateTimeEdit对象,以获得编辑控件的对象指针
    QDateTimeEdit *edit = static_cast<QDateTimeEdit *>(editor);
    //设置控件的显示数据
    edit->setDate(date);
}

void DateDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                const QModelIndex &index) const
{
    //通过紧缩转换获得编辑控件的对象指针
    QDateTimeEdit *edit = static_cast<QDateTimeEdit *>(editor);

    //获得编辑控件中的数据更新
    QDate date = edit->date();

    //调用setData()函数将数据修改更新到Model中
    model->setData(index, QVariant(date.toString(Qt::ISODate)));
}

void DateDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                                        const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
