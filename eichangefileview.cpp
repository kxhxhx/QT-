#include "eichangefileview.h"

EIChangeFileView::EIChangeFileView(QTreeView * ProtocolTreeView,
                                   QTreeView * ViewLayoutTreeView,
                                   const QStringList ProtocolTreeViewHead,
                                   const QStringList ViewLayoutTreeViewHead)
    :ProtocolFilePath("../../Files/Protocol/")
    ,ViewLayoutFilePath("../../Files/ViewLayout/")
    ,ProtocolVersion("Version 1.0 ")
    ,ProtocolTree(ProtocolTreeView, ProtocolTreeViewHead)
    ,ViewLayoutTree(ViewLayoutTreeView, ViewLayoutTreeViewHead)
{

    ProtocolTree.TreeViewTemp->setDragEnabled(true);
    ProtocolTree.TreeViewTemp->viewport()->setAcceptDrops(true);
    ProtocolTree.TreeViewTemp->showDropIndicator();
    ProtocolTree.TreeViewTemp->setDragDropMode(QTreeView::InternalMove);




    ProtocolTree.RClickMenuText.append("Add File");
    ProtocolTree.RClickMenuText.append("Add Group");
    ProtocolTree.RClickMenuText.append("Add Protocol");
    ProtocolTree.RClickMenuText.append("Save File");
    ProtocolTree.RClickMenuText.append("Delete File");

    for(const QString &MenuText : ProtocolTree.RClickMenuText)
    {
        ProtocolTree.ViewAddAction(MenuText, ProtocolTree.RClickMenu);
    }

    ViewLayoutTree.RClickMenuText.append("Add File");
    for(const QString &MenuText : ViewLayoutTree.RClickMenuText)
    {
        ViewLayoutTree.ViewAddAction(MenuText, ViewLayoutTree.RClickMenu);
    }


    QDir ProtocolDir(ProtocolFilePath);
    QStringList FileNameList = ProtocolDir.entryList(QStringList() << "*.json", QDir::Files);
    foreach (const QString& FileName, FileNameList)
    {
        ReadProtocol(ProtocolFilePath + FileName);
    }


    // connect(ProtocolTree.ModelTemp, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(ProtocolItemChanged(QStandardItem*)));
}

void EIChangeFileView::ProtocolViewAddFile()
{
    QStandardItem *TargetItem = ProtocolTree.ModelTemp->item(ProtocolTree.ModelTemp->rowCount() - 1);
    QModelIndex TargetIndex = ProtocolTree.ModelTemp->indexFromItem(TargetItem);
    EIChangeFileView::ProtocolData Data;
    Data.Name = ProtocolTree.GetNewName(TargetIndex, "untitled", ".json", 0);
    Data.Time = QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm");
    AddProtocol(TargetIndex, EIChangeTreeView::RootNode, EIChangeTreeView::File, Data);
    WriteProtocol(ProtocolTree.ModelTemp->index(ProtocolTree.ModelTemp->rowCount() - 1, 0, TargetIndex));

}

void EIChangeFileView::ProtocolViewAddGroup()
{
    QModelIndex TargetIndex = ProtocolTree.TreeViewTemp->currentIndex();
    EIChangeFileView::ProtocolData Data;
    Data.Name = ProtocolTree.GetNewName(TargetIndex, "untitledGroup", "", 1);
    Data.Time = QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm");

    int Type = ProtocolTree.ModelTemp->data(TargetIndex, Qt::UserRole + EIChangeTreeView::DataType).toInt();
    AddProtocol(TargetIndex, Type, EIChangeTreeView::Group, Data);
}

void EIChangeFileView::ProtocolViewAddItem()
{
    QModelIndex TargetIndex = ProtocolTree.TreeViewTemp->currentIndex();
    EIChangeFileView::ProtocolData Data;
    Data.Name = ProtocolTree.GetNewName(TargetIndex, "untitled", "", 1);
    Data.Time = QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm");

    Data.DataHead = "None";
    Data.SlaveAddress = "None";
    Data.FunctionCode = "None";
    Data.Data = "None";
    Data.CRC = "None";
    Data.DataTail = "None";


    int Type = ProtocolTree.ModelTemp->data(TargetIndex, Qt::UserRole + EIChangeTreeView::DataType).toInt();
    AddProtocol(TargetIndex, Type, EIChangeTreeView::Item, Data);
}

void EIChangeFileView::ProtocolViewSaveFile()
{
    QModelIndex TargetIndex = ProtocolTree.TreeViewTemp->currentIndex();
    if(TargetIndex.isValid())
    {
        TargetIndex = ProtocolTree.GetRootIndex(TargetIndex);
        WriteProtocol(TargetIndex);
    }
}

void EIChangeFileView::ProtocolViewDeleteFile()
{
    QModelIndex TargetIndex = ProtocolTree.TreeViewTemp->currentIndex();
    ProtocolTree.DeleteRowTreeData(TargetIndex);
}

void EIChangeFileView::ViewLayoutViewAddFile()
{
    QStandardItem *TargetItem = ViewLayoutTree.ModelTemp->item(ViewLayoutTree.ModelTemp->rowCount() - 1);
    QModelIndex TargetIndex = ViewLayoutTree.ModelTemp->indexFromItem(TargetItem);
    EIChangeFileView::ViewLayoutData Data;
    Data.Name = ViewLayoutTree.GetNewName(TargetIndex, "untitled", ".json", 0);

    Data.Time = QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm");
    AddViewLayout(TargetIndex, EIChangeTreeView::RootNode, EIChangeTreeView::File, Data);
    // WriteProtocol(ViewLayoutTree.ModelTemp->index(ViewLayoutTree.ModelTemp->rowCount() - 1, 0, TargetIndex));

    ViewLayout *test = new ViewLayout;
    QString WindowTitle;
    if(Data.Name.indexOf(".json") != -1)
        WindowTitle = Data.Name.left(Data.Name.indexOf(".json"));

    test->setWindowTitle(WindowTitle);
    test->show();


    // EIChangeSlider *Button = new EIChangeSlider();
    // // Button->move(windowPos);
    // Button->show();

}
QJsonObject EIChangeFileView::ProtocoltoJson(QModelIndex CurrentIndex)
{
    QJsonObject JsonObj = {};

    if(!CurrentIndex.isValid())
        return JsonObj;

    QModelIndex ParentIndex = CurrentIndex.parent();
    int CurrentCount = ProtocolTree.ModelTemp->rowCount(ParentIndex);

    for(int row = 0; row < CurrentCount; row++)
    {
        if(ProtocolTree.ModelTemp->data(ProtocolTree.ModelTemp->index(row, 0, ParentIndex), Qt::UserRole + EIChangeTreeView::DataType).toInt() == EIChangeTreeView::File)
        {
            JsonObj.insert("Version", ProtocolVersion);
            JsonObj.insert("Type", EIChangeTreeView::File);
            JsonObj.insert("Time", ProtocolTree.ModelTemp->data(ProtocolTree.ModelTemp->index(row, EIChangeFileView::Protocol_Time, ParentIndex)).toString());
            // JsonObj.insert("Time", ProtocolTree.ModelTemp->d);
            JsonObj.insert("File", ProtocoltoJson(ProtocolTree.ModelTemp->index(0, 0, CurrentIndex)));


        }
        else if(ProtocolTree.ModelTemp->data(ProtocolTree.ModelTemp->index(row, 0, ParentIndex), Qt::UserRole + EIChangeTreeView::DataType).toInt() == EIChangeTreeView::Group)
        {
            QModelIndex SiblingIndex = ProtocolTree.ModelTemp->index(row, 0, ParentIndex);
            QJsonObject GroupJsonObj = {};
            GroupJsonObj.insert("Type", EIChangeTreeView::Group);
            GroupJsonObj.insert("Time", ProtocolTree.ModelTemp->data(ProtocolTree.ModelTemp->index(row, EIChangeFileView::Protocol_Time, ParentIndex)).toString());
            GroupJsonObj.insert("Group", ProtocoltoJson(ProtocolTree.ModelTemp->index(0, 0, SiblingIndex)));
            JsonObj.insert(ProtocolTree.ModelTemp->data(SiblingIndex).toString(), GroupJsonObj);

        }
        else if(ProtocolTree.ModelTemp->data(ProtocolTree.ModelTemp->index(row, 0, ParentIndex), Qt::UserRole + EIChangeTreeView::DataType).toInt() == EIChangeTreeView::Item)
        {
            QModelIndex SiblingIndex = ProtocolTree.ModelTemp->index(row, 0, ParentIndex);
            QJsonObject ProtocolJsonObj = {};
            ProtocolJsonObj.insert("Type", EIChangeTreeView::Item);
            ProtocolJsonObj.insert("Time", ProtocolTree.ModelTemp->data(ProtocolTree.ModelTemp->index(row, EIChangeFileView::Protocol_Time, ParentIndex)).toString());
            ProtocolJsonObj.insert("DataHead", ProtocolTree.ModelTemp->data(ProtocolTree.ModelTemp->index(row, EIChangeFileView::Protocol_DataHead, ParentIndex)).toString());
            ProtocolJsonObj.insert("SlaveAddress", ProtocolTree.ModelTemp->data(ProtocolTree.ModelTemp->index(row, EIChangeFileView::Protocol_SlaveAddress, ParentIndex)).toString());
            ProtocolJsonObj.insert("FunctionCode", ProtocolTree.ModelTemp->data(ProtocolTree.ModelTemp->index(row, EIChangeFileView::Protocol_FunctionCode, ParentIndex)).toString());
            ProtocolJsonObj.insert("Data", ProtocolTree.ModelTemp->data(ProtocolTree.ModelTemp->index(row, EIChangeFileView::Protocol_Data, ParentIndex)).toString());
            ProtocolJsonObj.insert("CRC", ProtocolTree.ModelTemp->data(ProtocolTree.ModelTemp->index(row, EIChangeFileView::Protocol_CRC, ParentIndex)).toString());
            ProtocolJsonObj.insert("DataTail", ProtocolTree.ModelTemp->data(ProtocolTree.ModelTemp->index(row, EIChangeFileView::Protocol_DataTail, ParentIndex)).toString());
            JsonObj.insert(ProtocolTree.ModelTemp->data(SiblingIndex).toString(), ProtocolJsonObj);
        }
    }
    return JsonObj;
}

void EIChangeFileView::JsontoProtocol(QModelIndex ParentIndex, QJsonObject JsonObj, QString Name)
{
    ProtocolData Data;

    if(JsonObj["Type"].toInt() == EIChangeTreeView::File)
    {
        QJsonObject FileDatadJsonObj = JsonObj["File"].toObject();
        Data.Name = Name;
        Data.Time = JsonObj["Time"].toString();
        AddProtocol(ParentIndex, EIChangeTreeView::RootNode, EIChangeTreeView::File, Data);

        QModelIndex CurrentIndex;

        for(const QString& ChildName : FileDatadJsonObj.keys())
        {
            QJsonObject GroupChildJsonObj = FileDatadJsonObj[ChildName].toObject();

            QStandardItem *RootItem = ProtocolTree.ModelTemp->item(ProtocolTree.ModelTemp->rowCount() - 1);
            QModelIndex RootIndex = ProtocolTree.ModelTemp->indexFromItem(RootItem);
            CurrentIndex = RootIndex;

            JsontoProtocol(CurrentIndex, GroupChildJsonObj, ChildName);
        }
    }
    else if(JsonObj["Type"].toInt() == EIChangeTreeView::Group)
    {
        QJsonObject GroupDatadJsonObj = JsonObj["Group"].toObject();
        Data.Name = Name;
        Data.Time = JsonObj["Time"].toString();

        AddProtocol(ParentIndex, EIChangeTreeView::Group, EIChangeTreeView::Group, Data);

        for(const QString& ChildName : GroupDatadJsonObj.keys())
        {
            QModelIndex CurrentIndex = ProtocolTree.ModelTemp->index(ProtocolTree.ModelTemp->rowCount(ParentIndex) - 1, 0, ParentIndex);

            QJsonObject GroupChildJsonObj = GroupDatadJsonObj[ChildName].toObject();
            JsontoProtocol(CurrentIndex, GroupChildJsonObj, ChildName);
        }

    }
    else if(JsonObj["Type"].toInt() == EIChangeTreeView::Item)
    {
        Data.Name = Name;
        Data.Time = JsonObj["Time"].toString();
        Data.DataHead = JsonObj["DataHead"].toString();
        Data.SlaveAddress = JsonObj["SlaveAddress"].toString();
        Data.FunctionCode = JsonObj["FunctionCode"].toString();
        Data.Data = JsonObj["Data"].toString();
        Data.CRC = JsonObj["CRC"].toString();
        Data.DataTail = JsonObj["DataTail"].toString();
        AddProtocol(ParentIndex, EIChangeTreeView::Group, EIChangeTreeView::Item, Data);
    }


}

void EIChangeFileView::FindProtocol(QString Name)
{
    QModelIndex CurrentIndex = ProtocolTree.TreeViewTemp->currentIndex();

    QModelIndex TargetIndex;
    if(CurrentIndex.isValid())
    {
        TargetIndex = ProtocolTree.GetRootIndex(CurrentIndex);
        TargetIndex = ProtocolTree.FindItem(Name, TargetIndex, 1);
        ProtocolTree.TreeViewTemp->setCurrentIndex(TargetIndex);
        ProtocolTree.TreeViewTemp->scrollTo(TargetIndex);
    }
}

void EIChangeFileView::AddViewLayout(QModelIndex CurrentIndex, int CurrentType, int SetChildType, ViewLayoutData Data)
{
    if(SetChildType == EIChangeTreeView::File)
    {
        QList<QVariant> RoleData;
        QList<int> RoleIndex;
        QModelIndex TargetIndex;

        RoleData.append(Data.Name);
        RoleData.append(Data.Time);
        RoleIndex.append(Qt::DisplayRole);
        RoleIndex.append(Qt::DisplayRole);

        ViewLayoutTree.CreateRowTreeData(CurrentIndex.parent(), RoleData, RoleIndex);

        if(CurrentIndex.isValid())
        {
            TargetIndex = ViewLayoutTree.ModelTemp->index(ViewLayoutTree.ModelTemp->rowCount() - 1, 0, CurrentIndex.parent());
        }
        else
        {
            QStandardItem *RootItem = ViewLayoutTree.ModelTemp->invisibleRootItem();
            QModelIndex RootIndex = ViewLayoutTree.ModelTemp->indexFromItem(RootItem);
            TargetIndex = ViewLayoutTree.ModelTemp->index(0, 0, RootIndex);

        }
        ViewLayoutTree.SetTreeData(TargetIndex, EIChangeTreeView::File, EIChangeFileView::ViewLayout_Name, Qt::UserRole + EIChangeTreeView::DataType);
    }

}

void EIChangeFileView::ProtocolItemChanged(QStandardItem *Item)
{
    QModelIndex CurrentIndex = ProtocolTree.ModelTemp->indexFromItem(Item);

}
void EIChangeFileView::WriteProtocol(QModelIndex CurrentIndex)
{
    QStandardItem *CurrentItems = ProtocolTree.ModelTemp->itemFromIndex(CurrentIndex);

    if(ProtocolTree.ModelTemp->data(CurrentIndex, Qt::UserRole + EIChangeTreeView::DataType).toInt() == EIChangeTreeView::File)
    {
        QJsonObject JsonObj = ProtocoltoJson(CurrentIndex);
        ProtocolTree.FileOperation.JsonWrite(ProtocolFilePath + CurrentItems->text(), JsonObj, 1);
    }
}

void EIChangeFileView::ReadProtocol(QString ProtocolFilePath)
{
    QJsonObject JsonObj = ProtocolTree.FileOperation.JsonRead(ProtocolFilePath);
    QFileInfo FileInfo(ProtocolFilePath);

    QModelIndex Index;

    JsontoProtocol(Index, JsonObj, FileInfo.fileName());

}
void EIChangeFileView::AddProtocol(QModelIndex CurrentIndex, int CurrentType, int SetChildType, ProtocolData Data)
{
    if(SetChildType == EIChangeTreeView::File)
    {
            QList<QVariant> RoleData;
            QList<int> RoleIndex;
            QModelIndex TargetIndex;

            RoleData.append(Data.Name);
            RoleData.append(Data.Time);
            RoleIndex.append(Qt::DisplayRole);
            RoleIndex.append(Qt::DisplayRole);

            ProtocolTree.CreateRowTreeData(CurrentIndex.parent(), RoleData, RoleIndex);

            if(CurrentIndex.isValid())
            {
                TargetIndex = ProtocolTree.ModelTemp->index(ProtocolTree.ModelTemp->rowCount() - 1, 0, CurrentIndex.parent());
            }
            else
            {
                QStandardItem *RootItem = ProtocolTree.ModelTemp->invisibleRootItem();
                QModelIndex RootIndex = ProtocolTree.ModelTemp->indexFromItem(RootItem);
                TargetIndex = ProtocolTree.ModelTemp->index(0, 0, RootIndex);

            }
            ProtocolTree.SetTreeData(TargetIndex, EIChangeTreeView::File, EIChangeFileView::Protocol_Name, Qt::UserRole + EIChangeTreeView::DataType);
            // ProtocolTree.SetTreeData(TargetIndex, EIChangeTreeView::File, EIChangeFileView::Protocol_Name, Qt::DisplayRole);
    }
    else if(SetChildType == EIChangeTreeView::Group)
    {
        if((CurrentType == EIChangeTreeView::File) || (CurrentType == EIChangeTreeView::Group))
        {
            QList<QVariant> RoleData;
            QList<int> RoleIndex;

            RoleData.append(Data.Name);
            RoleData.append(Data.Time);
            RoleIndex.append(Qt::DisplayRole);
            RoleIndex.append(Qt::DisplayRole);

            ProtocolTree.CreateRowTreeData(CurrentIndex, RoleData, RoleIndex);
            QModelIndex TargetIndex = ProtocolTree.ModelTemp->index(ProtocolTree.ModelTemp->rowCount(CurrentIndex) - 1, 0, CurrentIndex);
            ProtocolTree.SetTreeData(TargetIndex, EIChangeTreeView::Group, EIChangeFileView::Protocol_Name, Qt::UserRole + EIChangeTreeView::DataType);
        }
    }
    else if(SetChildType == EIChangeTreeView::Item)
    {
        if((CurrentType == EIChangeTreeView::File) || (CurrentType == EIChangeTreeView::Group))
        {
            QList<QVariant> RoleData;
            QList<int> RoleIndex;

            RoleData.append(Data.Name);
            RoleData.append(Data.Time);
            RoleData.append(Data.DataHead);
            RoleData.append(Data.SlaveAddress);
            RoleData.append(Data.FunctionCode);
            RoleData.append(Data.Data);
            RoleData.append(Data.CRC);
            RoleData.append(Data.DataTail);

            RoleIndex.append(Qt::DisplayRole);
            RoleIndex.append(Qt::DisplayRole);
            RoleIndex.append(Qt::DisplayRole);
            RoleIndex.append(Qt::DisplayRole);
            RoleIndex.append(Qt::DisplayRole);
            RoleIndex.append(Qt::DisplayRole);
            RoleIndex.append(Qt::DisplayRole);
            RoleIndex.append(Qt::DisplayRole);

            ProtocolTree.CreateRowTreeData(CurrentIndex, RoleData, RoleIndex);
            QModelIndex TargetIndex = ProtocolTree.ModelTemp->index(ProtocolTree.ModelTemp->rowCount(CurrentIndex) - 1, 0, CurrentIndex);
            ProtocolTree.SetTreeData(TargetIndex, EIChangeTreeView::Item, EIChangeFileView::Protocol_Name, Qt::UserRole + EIChangeTreeView::DataType);
        }
    }

}


