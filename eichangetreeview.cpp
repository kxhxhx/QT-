#include "eichangetreeview.h"

EIChangeTreeView::EIChangeTreeView(QTreeView *TreeView, const QStringList Head)
    : QObject(TreeView)
    , TreeViewTemp(TreeView)
    , Attribute(new EIChangeAttribute(TreeView, "TreeView"))
{
    ModelTemp = new EIChangeItemMode(TreeViewTemp);
    ModelTemp->setHorizontalHeaderLabels(Head);
    TreeViewTemp->setModel(ModelTemp);

    connect(ModelTemp, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)), this, SLOT(DataChange(QModelIndex,QModelIndex,QVector<int>)));

}

void EIChangeTreeView::CreateRowTreeData(QModelIndex CurrentIndex, QList<TreeData> RowTreeData)
{
    QList<QStandardItem *> ItemGroup;
    for(int i = 0; i < RowTreeData.size(); i++)
    {
        QStandardItem *Item = new QStandardItem;
        Item->setData(RowTreeData[i].Data, RowTreeData[i].Index);
        Item->setEditable(RowTreeData[i].EditAble);
        ItemGroup.append(Item);
    }
    if(CurrentIndex.isValid())
    {
        QStandardItem *CurrentItem = ModelTemp->itemFromIndex(CurrentIndex);
        CurrentItem->appendRow(ItemGroup);
    }
    else
    {
        ModelTemp->appendRow(ItemGroup);
    }

}

void EIChangeTreeView::CreateColumnTreeData(QModelIndex CurrentIndex, QList<TreeData> ColumnTreeData)
{
    QList<QStandardItem *> ItemGroup;
    for(int i = 0; i < ColumnTreeData.size(); i++)
    {
        QStandardItem *Item = new QStandardItem;
        Item->setData(ColumnTreeData[i].Data, ColumnTreeData[i].Index);
        Item->setEditable(ColumnTreeData[i].EditAble);
        ItemGroup.append(Item);
    }

    if(CurrentIndex.isValid())
    {
        QStandardItem *CurrentItem = ModelTemp->itemFromIndex(CurrentIndex);
        CurrentItem->appendColumn(ItemGroup);
    }
    else
    {
        ModelTemp->appendColumn(ItemGroup);
    }

}
QModelIndex EIChangeTreeView::FindItem(QString Name, QModelIndex CurrentIndex, int FlagChild)
{
    if(!CurrentIndex.isValid())
        return CurrentIndex;

    QModelIndex ParentIndex = CurrentIndex.parent();
    int CurrentCount = ModelTemp->rowCount(ParentIndex);

    QModelIndex FindIndex;

    for(int row = 0; row < CurrentCount; row++)
    {
        QModelIndex SiblingIndex = ModelTemp->index(row, 0, ParentIndex);

        qDebug()<<ModelTemp->data(SiblingIndex).toString();
        if(ModelTemp->data(SiblingIndex).toString() == Name)
            return SiblingIndex;

        if(FlagChild == 1)
        {
            FindIndex = FindItem(Name, ModelTemp->index(0, 0, SiblingIndex), FlagChild);
            if(ModelTemp->data(FindIndex).toString() == Name)
                return FindIndex;

        }
    }
    return FindIndex;
}

bool EIChangeTreeView::isContain(QString Name, QModelIndex CurrentIndex, int FlagChild)
{
    bool FlagContain;
    if(!CurrentIndex.isValid())
        return false;

    QModelIndex ParentIndex = CurrentIndex.parent();
    int CurrentCount = ModelTemp->rowCount(ParentIndex);

    for(int row = 0; row < CurrentCount; row++)
    {
        QModelIndex SiblingIndex = ModelTemp->index(row, 0, ParentIndex);

        if(ModelTemp->data(SiblingIndex).toString() == Name)
            return true;

        if(FlagChild == 1)
        {
            FlagContain = isContain(Name, ModelTemp->index(0, 0, SiblingIndex), FlagChild);
            if(FlagContain == true)
                return true;
        }

    }

    return false;
}

QModelIndex EIChangeTreeView::GetRootIndex(QModelIndex CurrentIndex)
{
    while(CurrentIndex.parent().isValid())
    {
        CurrentIndex = CurrentIndex.parent();
    }
    return CurrentIndex;
}

QString EIChangeTreeView::GetNewName(QModelIndex CurrentIndex, QString BaseName, QString ExtensionName, int FlagChild)
{
    QString FileName;
    int FileIndex = 0;
    while(true)
    {
        if(FileIndex == 0)
        {
            FileName = BaseName + ExtensionName;
        }
        else
        {
            FileName = BaseName + QString::number(FileIndex) + ExtensionName;
        }

        if(!isContain(FileName, CurrentIndex, FlagChild))
        {
            return FileName;
        }

        FileIndex++;
    }
}

void EIChangeTreeView::SetTreeData(QModelIndex CurrentIndex, QVariant RoleData, int Column, int RoleIndex)
{
    QModelIndex TargetIndex = ModelTemp->index(CurrentIndex.row(), Column, CurrentIndex.parent());
    QStandardItem *Item = ModelTemp->itemFromIndex(TargetIndex);
    Item->setData(RoleData, RoleIndex);
}

void EIChangeTreeView::SetTreeData(QModelIndex ParentIndex, QVariant RoleData, int RoleIndex, int Row, int Column)
{
    QModelIndex TargetIndex = ModelTemp->index(Row, Column, ParentIndex);
    QStandardItem *Item = ModelTemp->itemFromIndex(TargetIndex);
    Item->setData(RoleData, RoleIndex);
}

QJsonObject EIChangeTreeView::TreeDatatoJsonObj(QStandardItemModel *Model, QModelIndex ParentIndex, int Level)
{
    int RowCount = Model->rowCount(ParentIndex);
    QJsonObject JsonObj = {};
    for(int Row = 0; Row < RowCount; Row++)
    {
        QModelIndex Index = Model->index(Row, 0, ParentIndex);
        if(Index.isValid())
        {
            int Type = Model->data(Index, Qt::UserRole + EIChangeTreeView::DataType).toInt();
            if(Type)
            {
                QString ItemText = Model->data(Index).toString();
                QJsonObject ChildJsonObj = TreeDatatoJsonObj(Model, Index, Level + 1);
                ChildJsonObj.insert("Type", Type);
                JsonObj.insert(ItemText, ChildJsonObj);
            }

        }
    }
    return JsonObj;
}

void EIChangeTreeView::CreateRowTreeData(QModelIndex CurrentIndex, QList<QVariant> RoleData, QList<int> RoleIndex)
{
    QList<QStandardItem *> ItemGroup;
    for(int i = 0; i < RoleData.size(); i++)
    {
        QStandardItem *Item = new QStandardItem;

        Item->setData(RoleData[i], RoleIndex[i]);
        ItemGroup.append(Item);
    }
    if(CurrentIndex.isValid())
    {
        QStandardItem *CurrentItem = ModelTemp->itemFromIndex(CurrentIndex);
        CurrentItem->appendRow(ItemGroup);
    }
    else
    {
        ModelTemp->appendRow(ItemGroup);
    }
}
void EIChangeTreeView::DeleteRowTreeData(QModelIndex CurrentIndex)
{
    if(CurrentIndex.isValid())
    {
        ModelTemp->removeRow(CurrentIndex.row(), CurrentIndex.parent());
    }
}

void EIChangeTreeView::DataChange(QModelIndex topLeft, QModelIndex bottomRight, QVector<int> roles)
{
    // QString
    // isContain();
    ModelTemp->data(topLeft).toString();
}

EIChangeTreeView::TreeData::TreeData(QVariant Data, int Index, bool EditAble)
    :Data(Data)
    ,Index(Index)
    ,EditAble(EditAble)
{

}
