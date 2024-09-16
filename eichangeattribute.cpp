#include "eichangeattribute.h"

EIChangeAttribute::EIChangeAttribute(QObject *Parent, QString MenuName)
    :QObject(Parent)
    ,RClickMenu(new EIChangeBaseMenu(MenuName))
{

}

EIChangeAttribute::~EIChangeAttribute()
{

}

void EIChangeAttribute::ViewAddMenu(const MenuAttribute &Attribute, EIChangeBaseMenu *Menu)
{
    if(!Attribute.Child.empty())
    {
        QAction *Action = Menu->addAction(Attribute.Name);
        EIChangeBaseMenu *ChildMenu = new EIChangeBaseMenu(Attribute.Name, Menu);

        Action->setMenu(ChildMenu);
        if(Attribute.Parent == nullptr)
            connect(ChildMenu,SIGNAL(triggered(QAction*)),this,SLOT(RightClick(QAction*)));


        for(const MenuAttribute* child : Attribute.Child)
        {
            if(child->Type == EIChangeBaseMenu::Check || child->Type == EIChangeBaseMenu::CheckandInput || child->Type == EIChangeBaseMenu::Input)
            {
                connect(ChildMenu, SIGNAL(CheckActionTrigger(QAction*)), this, SLOT(RightClick(QAction*)));
                break;
            }

        }
        for(const MenuAttribute* child : Attribute.Child)
        {
            ViewAddMenu(*child, ChildMenu);
        }
    }
    else
    {
        if(Attribute.Type == EIChangeBaseMenu::Text)
        {
            QAction *Action = new QAction(Attribute.Name);
            Menu->addAction(Action);

            if(Attribute.Parent == nullptr)
                connect(Action,SIGNAL(triggered(bool)),this,SLOT(RightClickAction(bool)));
        }
        else if(Attribute.Type == EIChangeBaseMenu::Input)
        {
            EIChangeInputMenuWidget *Container = new EIChangeInputMenuWidget(nullptr, Menu, Attribute.Name, Attribute.Data);
            EIChangeWidgetAction *WidgetAction = new EIChangeWidgetAction(Menu);
            WidgetAction->setText(Attribute.Name);
            WidgetAction->setProperty("Type", EIChangeBaseMenu::Input);
            WidgetAction->setDefaultWidget(Container);
            Menu->addAction(WidgetAction);

            connect(Container, SIGNAL(EnterWidgetAction()), WidgetAction, SLOT(Actived()));

            if(Attribute.Parent == nullptr)
                connect(WidgetAction, SIGNAL(triggered(bool)), this, SLOT(RightClickAction(bool)));
        }
        else if(Attribute.Type == EIChangeBaseMenu::Check)
        {
            EIChangeCheckMenuWidget *Container = new EIChangeCheckMenuWidget(nullptr, Menu, Attribute.Name, EIChangeBaseMenu::Check);
            EIChangeWidgetAction *WidgetAction = new EIChangeWidgetAction(Menu);
            WidgetAction->setText(Attribute.Name);
            WidgetAction->setProperty("Type", EIChangeBaseMenu::CheckandInput);

            WidgetAction->setDefaultWidget(Container);
            Menu->addAction(WidgetAction);

            connect(Container, SIGNAL(EnterWidgetAction()), WidgetAction, SLOT(Actived()));
            if(Attribute.Parent == nullptr)
                connect(WidgetAction, SIGNAL(triggered(bool)), this, SLOT(RightClickAction(bool)));
        }
        else if(Attribute.Type == EIChangeBaseMenu::CheckandInput)
        {
            EIChangeCheckMenuWidget *Container = new EIChangeCheckMenuWidget(nullptr, Menu, Attribute.Name, EIChangeBaseMenu::CheckandInput, Attribute.Data);
            EIChangeWidgetAction *WidgetAction = new EIChangeWidgetAction(Menu);
            WidgetAction->setText(Attribute.Name);
            WidgetAction->setProperty("Type", EIChangeBaseMenu::CheckandInput);

            if(Attribute.CheckInterLock)
                connect(Menu, SIGNAL(CheckInterLocked()), Container, SLOT(CheckInterLocked()));
            WidgetAction->setDefaultWidget(Container);
            Menu->addAction(WidgetAction);

            connect(Container, SIGNAL(EnterWidgetAction()), WidgetAction, SLOT(Actived()));
            if(Attribute.Parent == nullptr)
                connect(WidgetAction, SIGNAL(triggered(bool)), this, SLOT(RightClickAction(bool)));
        }
    }
}

void EIChangeAttribute::MenuConfig()
{
    for(MenuAttribute* Attribute: RightMenuText)
    {
        ViewAddMenu(*Attribute, RClickMenu);
    }
}
void EIChangeAttribute::RightClick(QAction *Action)
{
    emit Click(Action);
    static int count = 0;
    //获取发送者指针
    QMenu *childMenu=qobject_cast<QMenu *>(sender());
    qDebug()<<count++<<childMenu->title()<<Action->text();
    // //获取父菜单,直到没有父菜单为止
    // QMenu *parentMenu = childMenu;
    // while (parentMenu->parentWidget() != nullptr) {
    //     parentMenu = qobject_cast<QMenu *>(parentMenu->parentWidget());
    //     qDebug() << "parentMenu->objectName() == " << parentMenu->title();
    // }

}

void EIChangeAttribute::RightClickAction(bool Checked)
{
    QAction* Action = qobject_cast<QAction*>(sender());
    emit Click(Action);
    static int count = 0;
    if (Action) {
        qDebug() << count++ << Action->text();
    }

    // QMenu *parentMenu = Action->menu();
    // while (parentMenu->parentWidget() != nullptr) {
    //     parentMenu = qobject_cast<QMenu *>(parentMenu->parentWidget());
    //     qDebug() << "parentMenu->objectName() == " << parentMenu->title();
    // }

}
EIChangeAttribute::MenuAttribute::MenuAttribute(const QString &text, int type, MenuAttribute *parent, const QString &data)
    :Name(text)
    ,Parent(parent)
    ,Type(type)
    ,Data(data)
{
    if(parent)
    {
        parent->Child.append(this);
    }

}
