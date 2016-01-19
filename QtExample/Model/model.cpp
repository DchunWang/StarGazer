#include "model.h"
#include <QAbstractTableModel>

Model::Model(QObject *parent)
{
    armyMap[1] = tr("陈记臣");
    armyMap[2] = tr("黄庆忠");
    armyMap[3] = tr("张泽鹏");
    armyMap[4] = tr("张惠康");

    weaponTypeMap[1] = tr("男");
    weaponTypeMap[2] = tr("女");
    weaponTypeMap[3] = tr("充");
    weaponTypeMap[4] = tr("基");
    weaponTypeMap[5] = tr("伪");
    weaponTypeMap[6] = tr("腐");
    weaponTypeMap[7] = tr("宅");
    weaponTypeMap[8] = tr("现");

    populateModel();
}

void Model::populateModel()
{
    header << tr("姓名") << tr("性趣") << tr("性点");
    army << 1 << 2 << 3 << 4 << 2 << 3 << 1 << 4;
    weaponType << 1 << 3 << 5 << 7 << 4 << 8 << 6 << 2;
    weapon << tr("12") << tr("23") << tr("23:30") << tr("24:00")
           << tr("13") << tr("19:00") << tr("23:10") << tr("01:20");
}

int Model::columnCount(const QModelIndex &parent) const
{
    return 3;
}

int Model::rowCount(const QModelIndex &parent) const
{
    return army.size();
}

QVariant Model::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if(role == Qt::DisplayRole)
    {
        switch(index.column())
        {
        case 0:
            return armyMap[army[index.row()]];
            break;
        case 1:
            return weaponTypeMap[weaponType[index.row()]];
            break;
        case 2:
            return weapon[index.row()];
        default:
            return QVariant();
        }
    }
    return QVariant();
}

QVariant Model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
        return header[section];
    return QAbstractTableModel::headerData(section, orientation, role);
}

