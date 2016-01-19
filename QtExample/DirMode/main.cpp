#include "mainwindow.h"
#include <QApplication>
#include <QAbstractItemModel>
#include <QAbstractItemView>
#include <QItemSelectionModel>
#include <QDirModel>
#include <QTreeView>
#include <QListView>
#include <QTableView>
#include <QSplitter>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //新建一个QDirModel对象，为数据访问做准备
    QDirModel model;

    //新建三种不同的View对象，以便文件目录可以以三种不同的方式显示
    QTreeView tree;
    QListView list;
    QTableView table;

    //调用setModel()函数设置View对象的Model为QDirModel对象的model
    tree.setModel(&model);
    list.setModel(&model);
    table.setModel(&model);

    //设置QTreeView对象的选择方式为多选
    tree.setSelectionMode(QAbstractItemView::MultiSelection);
    list.setSelectionModel(tree.selectionModel());
    table.setSelectionModel(tree.selectionModel());

    //为了实现双击QTreeView对象中的某个目录时，QListView对象和QTableView对象中
    //显示此选定目录下的所有文件和目录，需要连接QTreeView对象的doubleClicked()信号
    //与QListView对象和QTableView对象的setRootIndex()槽函数
    QObject::connect(&tree, SIGNAL(doubleClicked(QModelIndex)), &list,
                     SLOT(setRootIndex(QModelIndex)));
    QObject::connect(&tree, SIGNAL(doubleClicked(QModelIndex)), &table,
                     SLOT(setRootIndex(QModelIndex)));

    QSplitter *splitter = new QSplitter;
    splitter->addWidget(&tree);
    splitter->addWidget(&list);
    splitter->addWidget(&table);
    splitter->setWindowTitle(QObject::tr("Model/View"));
    splitter->show();

    return a.exec();
}
