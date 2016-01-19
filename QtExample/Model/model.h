#ifndef MODEL_H
#define MODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include <QMap>
#include <QStringList>

class Model : public QAbstractTableModel
{
public :
    explicit Model(QObject *parent = 0);

    //虚函数声明
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
    QVector<short> army;
    QVector<short> weaponType;
    //使用QMap数据结构保存“数值-文字"的映射
    QMap<short, QString> armyMap;
    QMap<short, QString> weaponTypeMap;
    QStringList weapon;
    QStringList header;
    //完成表格数据的初始化填充
    void populateModel();
};

#endif
