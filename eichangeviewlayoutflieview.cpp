#include "eichangeviewlayoutflieview.h"


EIChangeViewLayoutFlieView::EIChangeViewLayoutFlieView(QTreeView *TreeView, const QStringList Head)
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

    Attribute->MenuConfig();

    connect(Attribute, SIGNAL(Click(QAction*)), this, SLOT(RightClick(QAction*)));

}

void EIChangeViewLayoutFlieView::AddViewLayout(QModelIndex CurrentIndex, int CurrentType, int SetChildType, ViewLayoutData Data)
{
    if(SetChildType == EIChangeAttribute::File)
    {
        QList<QVariant> RoleData;
        QList<int> RoleIndex;
        QModelIndex TargetIndex;

        RoleData.append(Data.Name);
        RoleData.append(Data.Data);
        RoleIndex.append(Qt::DisplayRole);
        RoleIndex.append(Qt::DisplayRole);

        CreateRowTreeData(CurrentIndex.parent(), RoleData, RoleIndex);

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
        SetTreeData(TargetIndex, EIChangeAttribute::File, EIChangeViewLayoutFlieView::ViewLayout_Name, Qt::UserRole + EIChangeTreeView::DataType);
    }

}

void EIChangeViewLayoutFlieView::RightClick(QAction *Action)
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


        }
        else if (ActionList[ActionList.size() - 2]->text() == Attribute->RightMenuText[1]->Name)
        {
            QModelIndex TargetIndex = TreeViewTemp->currentIndex();
            DeleteRowTreeData(TargetIndex);

        }
        else if (ActionList[ActionList.size() - 2]->text() == Attribute->RightMenuText[2]->Name)
        {
            QStandardItem *TargetItem = ModelTemp->item(ModelTemp->rowCount() - 1);
            QModelIndex TargetIndex = ModelTemp->indexFromItem(TargetItem);
            ViewLayoutData Data;
            Data.Name = GetNewName(TargetIndex, "untitled", ".json", 0);
            Data.Data = QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm");
            AddViewLayout(TargetIndex, EIChangeAttribute::RootNode, EIChangeAttribute::File, Data);
            // WriteProtocol(ViewLayoutTree.ModelTemp->index(ViewLayoutTree.ModelTemp->rowCount() - 1, 0, TargetIndex));


            QJsonObject JsonObj;

            JsonObj.insert("ProtocolAction", TreeDatatoJsonObj(DataModel, DataModel->invisibleRootItem()->index(), 0));


            ViewLayout *CustomView = new ViewLayout(nullptr, JsonObj);
            QString WindowTitle;
            if(Data.Name.indexOf(".json") != -1)
                WindowTitle = Data.Name.left(Data.Name.indexOf(".json"));

            CustomView->setWindowTitle(WindowTitle);
            CustomView->show();

        }
    }

}
