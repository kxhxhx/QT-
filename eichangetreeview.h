#ifndef EICHANGETREEVIEW_H
#define EICHANGETREEVIEW_H

#include <QMenu>
#include <QTreeView>
#include <QStandardItemModel>
#include "eichangefiles.h"

class EIChangeTreeView
{

public:

    enum TreeDataRoleEum
    {
        None = 0,
        DataType,

    };
    enum DataTypeEum
    {
        RootNode = 0,
        File,
        Group,
        Item,
    };
    EIChangeFiles FileOperation;

    QTreeView *TreeViewTemp;
    QStandardItemModel *ModelTemp;

    QMenu* RClickMenu;
    QList<QString> RClickMenuText;


    EIChangeTreeView(QTreeView *TreeView, const QStringList Head);
    void ViewAddAction(QString Name, QMenu* Menu);
    QModelIndex FindItem(QString Name, QModelIndex CurrentIndex, int FlagChild);
    bool isContain(QString Name, QModelIndex CurrentIndex, int FlagChild);
    QModelIndex GetRootIndex(QModelIndex CurrentIndex);
    QString GetNewName(QModelIndex CurrentIndex, QString BaseName, QString ExtensionName, int FlagChild);
    void SetTreeData(QModelIndex CurrentIndex, QVariant RoleData, int Column, int RoleIndex);
    void CreateRowTreeData(QModelIndex CurrentIndex, QList<QVariant> RoleData, QList<int> RoleIndex);
    void DeleteRowTreeData(QModelIndex CurrentIndex);

};

#endif // EICHANGETREEVIEW_H
