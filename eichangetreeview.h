#ifndef EICHANGETREEVIEW_H
#define EICHANGETREEVIEW_H

#include <QMenu>
#include <QTreeView>
#include <QStandardItemModel>
#include "eichangeitemmodel.h"

#include "eichangefiles.h"
#include "eichangeattribute.h"

class EIChangeTreeView : public QObject
{
    Q_OBJECT
public:
    explicit EIChangeTreeView(QTreeView *TreeView, const QStringList Head);

    enum TreeDataRoleEum
    {
        None = 0,
        DataType,

    };

    struct TreeData
    {
        QVariant Data;
        int Index;
        bool EditAble;
        TreeData(QVariant Data, int Index, bool EditAble);
    };
    QTreeView *TreeViewTemp;
    EIChangeItemMode *ModelTemp;

    EIChangeFiles FileOperation;
    EIChangeAttribute *Attribute;


    void CreateRowTreeData(QModelIndex CurrentIndex, QList<QVariant> RoleData, QList<int> RoleIndex);
    void CreateRowTreeData(QModelIndex CurrentIndex, QList<TreeData> RowTreeData);
    void CreateColumnTreeData(QModelIndex CurrentIndex, QList<TreeData> ColumnTreeData);

    void SetTreeData(QModelIndex CurrentIndex, QVariant RoleData, int Column, int RoleIndex);
    void SetTreeData(QModelIndex ParentIndex, QVariant RoleData, int RoleIndex, int Row, int Column);

    QJsonObject TreeDatatoJsonObj(QStandardItemModel *Model, QModelIndex ParentIndex, int Level);

    QModelIndex FindItem(QString Name, QModelIndex CurrentIndex, int FlagChild);
    bool isContain(QString Name, QModelIndex CurrentIndex, int FlagChild);
    QModelIndex GetRootIndex(QModelIndex CurrentIndex);
    QString GetNewName(QModelIndex CurrentIndex, QString BaseName, QString ExtensionName, int FlagChild);
    void DeleteRowTreeData(QModelIndex CurrentIndex);

private slots:
    void DataChange(QModelIndex topLeft, QModelIndex bottomRight, QVector<int> roles);
};

#endif // EICHANGETREEVIEW_H
