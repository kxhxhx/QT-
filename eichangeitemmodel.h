#ifndef EICHANGEITEMMODEL_H
#define EICHANGEITEMMODEL_H

#include <QStandardItemModel>
#include <QMimeData>

class EIChangeItemMode : public QStandardItemModel
{
    Q_OBJECT

public:
    enum DataTypeEnum
    {
        RootNode = 0,
        File,
        Group,
        Item,
    };
    enum TreeDataRoleEum
    {
        None = 0,
        DataType,

    };

    EIChangeItemMode(QObject *parent = nullptr) : QStandardItemModel(parent) {}

    Qt::ItemFlags flags(const QModelIndex &index) const override
    {
        Qt::ItemFlags defaultFlags = QStandardItemModel::flags(index);

        if (index.isValid())
        {
            DataTypeEnum type = static_cast<DataTypeEnum>(index.data(Qt::UserRole + DataType).toInt());


            if (type == Group || type == Item)
            {
                defaultFlags |= Qt::ItemIsDragEnabled;
            }


            if (type == File || type == Group)
            {
                defaultFlags |= Qt::ItemIsDropEnabled;
            }
        }

        return defaultFlags;
    }

    bool canDropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) const override
    {
        if (!parent.isValid())
            return false;

        DataTypeEnum parentType = static_cast<DataTypeEnum>(parent.data(Qt::UserRole + DataType).toInt());

        if (parentType != File && parentType != Group)
            return false;


        QByteArray encodedData = data->data("application/x-qabstractitemmodeldatalist");
        QDataStream stream(&encodedData, QIODevice::ReadOnly);
        int srcRow, srcCol;
        QMap<int, QVariant> roleDataMap;
        stream >> srcRow >> srcCol >> roleDataMap;

        DataTypeEnum srcType = static_cast<DataTypeEnum>(roleDataMap[Qt::UserRole + DataType].toInt());


        return (srcType == Group || srcType == Item);
    }

    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) override
    {
        if (!canDropMimeData(data, action, row, column, parent))
            return false;

        return QStandardItemModel::dropMimeData(data, action, row, column, parent);
    }
};

#endif // EICHANGEITEMMODEL_H
