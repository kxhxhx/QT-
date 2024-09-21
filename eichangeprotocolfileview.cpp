#include "eichangeprotocolfileview.h"

EIChangeProtocolFileView::EIChangeProtocolFileView(QTreeView *TreeView, const QStringList Head)
    :EIChangeTreeView(TreeView, Head)
{
    TreeView->setDragEnabled(true);
    TreeView->setDragEnabled(true);
    TreeView->viewport()->setAcceptDrops(true);
    TreeView->showDropIndicator();
    TreeView->setDragDropMode(QTreeView::InternalMove);

    EIChangeAttribute::MenuAttribute* Save = new EIChangeAttribute::MenuAttribute("Save");
    Attribute->RightMenuText.append(Save);
    EIChangeAttribute::MenuAttribute* Delete = new EIChangeAttribute::MenuAttribute("Delete");
    Attribute->RightMenuText.append(Delete);
    EIChangeAttribute::MenuAttribute* AddFile = new EIChangeAttribute::MenuAttribute("Add File");
    Attribute->RightMenuText.append(AddFile);
    EIChangeAttribute::MenuAttribute* AddGroup = new EIChangeAttribute::MenuAttribute("Add Group");
    Attribute->RightMenuText.append(AddGroup);
    EIChangeAttribute::MenuAttribute* AddProtocol = new EIChangeAttribute::MenuAttribute("Add Protocol");
    Attribute->RightMenuText.append(AddProtocol);

    Attribute->MenuConfig();

    connect(Attribute, SIGNAL(Click(QAction*)), this, SLOT(RightClick(QAction*)));


    QDir ProtocolDir(FilePath);
    QStringList FileNameList = ProtocolDir.entryList(QStringList() << "*.json", QDir::Files);
    foreach (const QString& FileName, FileNameList)
    {
        ReadProtocol(FilePath + FileName);
    }

}

void EIChangeProtocolFileView::AddProtocol(QModelIndex CurrentIndex, int CurrentType, int SetChildType, ProtocolData Data)
{
    if(SetChildType == EIChangeAttribute::File)
    {

        QModelIndex TargetIndex;
        QList<TreeData> FileData;

        TreeData Name(Data.Name, Qt::DisplayRole, true);
        FileData.append(Name);

        TreeData Time(Data.Time, Qt::DisplayRole, false);
        FileData.append(Time);

        CreateRowTreeData(CurrentIndex.parent(), FileData);

        if(CurrentIndex.isValid())
        {
            TargetIndex = ModelTemp->index(ModelTemp->rowCount() - 1, 0, CurrentIndex.parent());
        }
        else
        {
            QStandardItem *RootItem = ModelTemp->invisibleRootItem();
            QModelIndex RootIndex = ModelTemp->indexFromItem(RootItem);
            TargetIndex = ModelTemp->index(0, 0, RootIndex);

        }
        SetTreeData(TargetIndex, EIChangeAttribute::File, EIChangeProtocolFileView::Protocol_Name, Qt::UserRole + EIChangeTreeView::DataType);
    }
    else if(SetChildType == EIChangeAttribute::Group)
    {
        if((CurrentType == EIChangeAttribute::File) || (CurrentType == EIChangeAttribute::Group))
        {
            QList<TreeData> FileData;
            TreeData Name(Data.Name, Qt::DisplayRole, true);
            FileData.append(Name);
            TreeData Time(Data.Time, Qt::DisplayRole, false);
            FileData.append(Time);
            CreateRowTreeData(CurrentIndex, FileData);

            QList<QString> HearText;
            HearText.append("GroupDataHead");
            HearText.append("GroupSlaveAddress");
            HearText.append("GroupCRC");
            HearText.append("GroupDataTail");
            QList<TreeData> ProtocolDataHeader;
            for(int i = 0; i < HearText.size(); i++)
            {
                TreeData DataHeader(HearText[i], Qt::DisplayRole, false);
                ProtocolDataHeader.append(DataHeader);
            }
            CreateColumnTreeData(ModelTemp->index(ModelTemp->rowCount(CurrentIndex) - 1, 0, CurrentIndex), ProtocolDataHeader);

            QList<QString> DataText;
            DataText.append("None");
            DataText.append("None");
            DataText.append("None");
            DataText.append("None");
            QList<TreeData> ProtocolData;
            for(int i = 0; i < DataText.size(); i++)
            {
                TreeData Data(DataText[i], Qt::DisplayRole, true);
                ProtocolData.append(Data);
            }
            CreateColumnTreeData(ModelTemp->index(ModelTemp->rowCount(CurrentIndex) - 1, 0, CurrentIndex), ProtocolData);



            QModelIndex TargetIndex = ModelTemp->index(ModelTemp->rowCount(CurrentIndex) - 1, 0, CurrentIndex);
            SetTreeData(TargetIndex, EIChangeAttribute::Group, EIChangeProtocolFileView::Protocol_Name, Qt::UserRole + EIChangeTreeView::DataType);
        }
    }
    else if(SetChildType == EIChangeAttribute::Item)
    {
        if((CurrentType == EIChangeAttribute::File) || (CurrentType == EIChangeAttribute::Group))
        {
            QList<TreeData> FileData;
            TreeData Name(Data.Name, Qt::DisplayRole, true);
            FileData.append(Name);
            TreeData Time(Data.Time, Qt::DisplayRole, false);
            FileData.append(Time);
            CreateRowTreeData(CurrentIndex, FileData);

            QList<QString> HearText;
            HearText.append("DataHead");
            HearText.append("SlaveAddress");
            HearText.append("FunctionCode");
            HearText.append("CRC");
            HearText.append("DataTail");
            QList<TreeData> ProtocolDataHeader;
            for(int i = 0; i < HearText.size(); i++)
            {
                TreeData DataHeader(HearText[i], Qt::DisplayRole, false);
                ProtocolDataHeader.append(DataHeader);
            }
            CreateColumnTreeData(ModelTemp->index(ModelTemp->rowCount(CurrentIndex) - 1, 0, CurrentIndex), ProtocolDataHeader);

            // qDebug() << ModelTemp->rowCount(CurrentIndex);

            QList<QString> DataText;
            DataText.append("None");
            DataText.append("None");
            DataText.append("None");
            DataText.append("None");
            DataText.append("None");
            QList<TreeData> ProtocolData;
            for(int i = 0; i < DataText.size(); i++)
            {
                TreeData Data(DataText[i], Qt::DisplayRole, true);
                ProtocolData.append(Data);
            }
            CreateColumnTreeData(ModelTemp->index(ModelTemp->rowCount(CurrentIndex) - 1, 0, CurrentIndex), ProtocolData);


            QModelIndex TargetIndex = ModelTemp->index(ModelTemp->rowCount(CurrentIndex) - 1, 0, CurrentIndex);
            SetTreeData(TargetIndex, EIChangeAttribute::Item, EIChangeProtocolFileView::Protocol_Name, Qt::UserRole + EIChangeTreeView::DataType);
        }
    }

}

void EIChangeProtocolFileView::WriteProtocol(QModelIndex CurrentIndex)
{
    if(CurrentIndex.isValid())
    {
        QStandardItem *CurrentItems = ModelTemp->itemFromIndex(CurrentIndex);

        int DataRole = ModelTemp->data(CurrentIndex, Qt::UserRole + EIChangeTreeView::DataType).toInt();
        QString Data = ModelTemp->data(CurrentIndex, Qt::DisplayRole).toString();
        if(DataRole == EIChangeAttribute::File)
        {
            QJsonObject JsonObj = {};
            QJsonObject JsonChildObj = ProtocoltoJson(CurrentIndex);
            JsonChildObj.insert("Type", "File");
            JsonObj.insert(Data, JsonChildObj);
            FileOperation.JsonWrite(FilePath + CurrentItems->text(), JsonObj, 1);

            // QJsonArray JsonObj = {};
            // JsonObj.append(QJsonObject{{Data, ProtocoltoJson(CurrentIndex)}});
            // FileOperation.JsonWrite(FilePath + CurrentItems->text(), JsonObj, 1);
        }

    }
}

void EIChangeProtocolFileView::ReadProtocol(QString ProtocolFilePath)
{
    QJsonObject JsonObj = FileOperation.JsonRead(ProtocolFilePath);

    QStandardItem *rootItem = ModelTemp->invisibleRootItem();

    JsontoProtocol(rootItem, JsonObj);

    // QJsonArray JsonObj = FileOperation.JsonRead(ProtocolFilePath, 0);

    // QStandardItem *rootItem = ModelTemp->invisibleRootItem();

    // JsontoProtocol(rootItem, JsonObj);
}

QJsonObject EIChangeProtocolFileView::ProtocoltoJson(QModelIndex CurrentIndex)
{
    QJsonObject JsonObj = {};
    if(!CurrentIndex.isValid())
        return JsonObj;

    int CurrentCount = ModelTemp->rowCount(CurrentIndex);
    for(int i = 0; i < CurrentCount; i++)
    {
        int DataRole = ModelTemp->data(ModelTemp->index(i, 0, CurrentIndex), Qt::UserRole + EIChangeTreeView::DataType).toInt();

        if((DataRole == EIChangeAttribute::File) || (DataRole == EIChangeAttribute::Group) || (DataRole == EIChangeAttribute::Item))
        {
            QString Name = ModelTemp->data(ModelTemp->index(i, 0, CurrentIndex)).toString();
            QJsonObject JsonChildObj = ProtocoltoJson(ModelTemp->index(i, 0, CurrentIndex));

            JsonChildObj.insert("Type", ModelTemp->data(ModelTemp->index(i, 1, CurrentIndex)).toString());

            JsonObj.insert(Name, JsonChildObj);
        }
        else
        {

            QString Name = ModelTemp->data(ModelTemp->index(i, 0, CurrentIndex)).toString();
            QString Data = ModelTemp->data(ModelTemp->index(i, 1, CurrentIndex)).toString();
            JsonObj.insert(Name, Data);

        }
    }
    return JsonObj;
}

void EIChangeProtocolFileView::JsontoProtocol(QStandardItem *ParentItem, QJsonObject JsonObj)
{
    for (const QString &Key : JsonObj.keys())
    {
        QJsonObject ChildObject = JsonObj[Key].toObject();
        if(ChildObject.isEmpty())
        {
            if(Key == "Type")
            {

            }
            else
            {
                QStandardItem *ChildNameItem = new QStandardItem(Key);
                QStandardItem *ChildDataItem = new QStandardItem(JsonObj[Key].toString());
                ChildNameItem->setEditable(false);
                QList<QStandardItem *> ChildItem;
                ChildItem.append(ChildNameItem);
                ChildItem.append(ChildDataItem);
                ParentItem->appendRow(ChildItem);
            }

        }
        else
        {

            QStandardItem *ChildNameItem = new QStandardItem(Key);
            QStandardItem *ChildDataItem = new QStandardItem;
            if(ChildObject["Type"].toString() == "File")
            {
                ChildNameItem->setData(EIChangeAttribute::File, Qt::UserRole + EIChangeTreeView::DataType);
                // ChildNameItem->setEditable(false);
                ChildDataItem->setData(ChildObject["Type"].toString(), Qt::DisplayRole);
                ChildDataItem->setEditable(false);

            }
            else if(ChildObject["Type"].toString() == "Group")
            {
                ChildNameItem->setData(EIChangeAttribute::Group, Qt::UserRole + EIChangeTreeView::DataType);
                // ChildNameItem->setEditable(false);
                ChildDataItem->setData(ChildObject["Type"].toString(), Qt::DisplayRole);
                ChildDataItem->setEditable(false);

            }
            else if(ChildObject["Type"].toString() == "Item")
            {
                ChildNameItem->setData(EIChangeAttribute::Item, Qt::UserRole + EIChangeTreeView::DataType);
                // ChildNameItem->setEditable(false);
                ChildDataItem->setData(ChildObject["Type"].toString(), Qt::DisplayRole);
                ChildDataItem->setEditable(false);

            }

            QList<QStandardItem *> ChildItem;
            ChildItem.append(ChildNameItem);
            ChildItem.append(ChildDataItem);
            ParentItem->appendRow(ChildItem);
            JsontoProtocol(ChildNameItem, ChildObject);

        }
    }
}

QJsonArray EIChangeProtocolFileView::ProtocoltoJson(QModelIndex CurrentIndex, int FlagDiff)
{
    QJsonArray JsonObj = {};
    if(!CurrentIndex.isValid())
        return JsonObj;

    int CurrentCount = ModelTemp->rowCount(CurrentIndex);
    for(int i = 0; i < CurrentCount; i++)
    {
        int DataRole = ModelTemp->data(ModelTemp->index(i, 0, CurrentIndex), Qt::UserRole + EIChangeTreeView::DataType).toInt();

        qDebug() << ModelTemp->data(ModelTemp->index(i, 0, CurrentIndex)).toString();
        if((DataRole == EIChangeAttribute::File) || (DataRole == EIChangeAttribute::Group) || (DataRole == EIChangeAttribute::Item))
        {
            QString Name = ModelTemp->data(ModelTemp->index(i, 0, CurrentIndex)).toString();
            JsonObj.append(QJsonObject{{Name, ProtocoltoJson(ModelTemp->index(i, 0, CurrentIndex), 0)}});


        }
        else
        {
            QString Name = ModelTemp->data(ModelTemp->index(i, 0, CurrentIndex)).toString();
            QString Data = ModelTemp->data(ModelTemp->index(i, 1, CurrentIndex)).toString();
            JsonObj.append(QJsonObject{{Name, Data}});

        }
    }
    return JsonObj;

}

void EIChangeProtocolFileView::JsontoProtocol(QStandardItem *ParentItem, QJsonArray JsonObj)
{
    for (int i = 0; i < JsonObj.size(); ++i)
    {
        const QJsonValue &value = JsonObj[i];

        if (value.isObject())
        {
            QJsonObject childObject = value.toObject();
            QStandardItem *ChildNameItem = new QStandardItem(QString("Item %1").arg(i)); // 使用索引作为名称
            QStandardItem *ChildDataItem = new QStandardItem; // 这里可以留空
            QList<QStandardItem *> ChildItem;
            ChildItem.append(ChildNameItem);
            ChildItem.append(ChildDataItem);
            ParentItem->appendRow(ChildItem);
            JsontoProtocol(ChildNameItem, childObject); // 递归处理子对象
        }
        else if (value.isArray())
        {
            QStandardItem *ChildNameItem = new QStandardItem(QString("Array %1").arg(i)); // 使用索引作为名称
            QStandardItem *ChildDataItem = new QStandardItem; // 这里可以留空
            QList<QStandardItem *> ChildItem;
            ChildItem.append(ChildNameItem);
            ChildItem.append(ChildDataItem);
            ParentItem->appendRow(ChildItem);
            JsontoProtocol(ChildNameItem, value.toArray()); // 递归处理子数组
        }
        else
        {
            QStandardItem *ChildNameItem = new QStandardItem(QString("Item %1").arg(i)); // 使用索引作为名称
            QStandardItem *ChildDataItem = new QStandardItem(value.toString());
            QList<QStandardItem *> ChildItem;
            ChildItem.append(ChildNameItem);
            ChildItem.append(ChildDataItem);
            ParentItem->appendRow(ChildItem);
        }
    }

}
void EIChangeProtocolFileView::RightClick(QAction *Action)
{
    if(Action)
    {
        QList<QAction*> ActionList;
        ActionList.append(Action);

        EIChangeBaseMenu *RootMenu = qobject_cast<EIChangeBaseMenu*>(Action->parent());
        while(RootMenu)
        {
            QString LastTitle = RootMenu->title();
            QAction *AssociatedAction = RootMenu->menuAction();
            ActionList.append(AssociatedAction);
            RootMenu = qobject_cast<EIChangeBaseMenu*>(AssociatedAction->parent());
            if(LastTitle == RootMenu->title())
                break;
        }

        if(ActionList[ActionList.size() - 2]->text() == Attribute->RightMenuText[0]->Name)
        {
            QModelIndex TargetIndex = GetRootIndex(TreeViewTemp->currentIndex());
            qDebug() << ModelTemp->rowCount(TargetIndex);
            if(TargetIndex.isValid())
            {
                WriteProtocol(TargetIndex);
            }

        }
        else if (ActionList[ActionList.size() - 2]->text() == Attribute->RightMenuText[1]->Name)
        {

        }
        else if (ActionList[ActionList.size() - 2]->text() == Attribute->RightMenuText[2]->Name)
        {
            QStandardItem *TargetItem = ModelTemp->item(ModelTemp->rowCount() - 1);
            QModelIndex TargetIndex = ModelTemp->indexFromItem(TargetItem);
            ProtocolData Data;
            Data.Name = GetNewName(TargetIndex, "untitled", ".json", 0);
            Data.Time = "File";
            AddProtocol(TargetIndex, EIChangeAttribute::RootNode, EIChangeAttribute::File, Data);
            // WriteProtocol(ModelTemp->index(ModelTemp->rowCount() - 1, 0, TargetIndex));

        }
        else if (ActionList[ActionList.size() - 2]->text() == Attribute->RightMenuText[3]->Name)
        {
            QModelIndex TargetIndex = TreeViewTemp->currentIndex();
            ProtocolData Data;
            Data.Name = GetNewName(TargetIndex, "untitled", "", 1);
            Data.Time = "Group";

            int Type = ModelTemp->data(TargetIndex, Qt::UserRole + EIChangeTreeView::DataType).toInt();
            AddProtocol(TargetIndex, Type, EIChangeAttribute::Group, Data);
            // WriteProtocol(ModelTemp->index(ModelTemp->rowCount() - 1, 0, TargetIndex));

        }
        else if (ActionList[ActionList.size() - 2]->text() == Attribute->RightMenuText[4]->Name)
        {
            QModelIndex TargetIndex = TreeViewTemp->currentIndex();
            ProtocolData Data;
            Data.Name = GetNewName(TargetIndex, "untitled", "", 1);
            Data.Time = "Item";
            int Type = ModelTemp->data(TargetIndex, Qt::UserRole + EIChangeTreeView::DataType).toInt();
            AddProtocol(TargetIndex, Type, EIChangeAttribute::Item, Data);
        }

    }
}
