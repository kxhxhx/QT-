#include "viewlayout.h"
#include "ui_viewlayout.h"
ViewLayout::ViewLayout(QWidget *parent, QJsonObject Profile)
    : QWidget(parent)
    , Attribute(new EIChangeAttribute(parent, "ViewLayout"))
    , Profile(new QJsonObject(Profile))
    , ui(new Ui::ViewLayout)
    , LineEditControlSearch(new QLineEdit(this))
    , isOpenLineEditControlSearch(false)
{
    ui->setupUi(this);
    this->installEventFilter(this);
    this->setContextMenuPolicy(Qt::CustomContextMenu);

    LineEditControlSearch->hide();
    connect(LineEditControlSearch, SIGNAL(returnPressed()), this, SLOT(ConfirmLineEditControlSearch()));


    EIChangeAttribute::MenuAttribute* AddButton = new EIChangeAttribute::MenuAttribute("Add Button");
    Attribute->RightMenuText.append(AddButton);
    EIChangeAttribute::MenuAttribute* AddSlider = new EIChangeAttribute::MenuAttribute("Add Slider");
    Attribute->RightMenuText.append(AddSlider);
    EIChangeAttribute::MenuAttribute* AddScope = new EIChangeAttribute::MenuAttribute("Add Scope");
    Attribute->RightMenuText.append(AddScope);
    Attribute->MenuConfig();
    connect(Attribute, SIGNAL(Click(QAction*)), this, SLOT(RightClick(QAction*)));


    // QJsonObject JsonObj = Profile["ProtocolAction"].toObject();

    // if(JsonObj.isEmpty())
    // {

    // }




}

ViewLayout::~ViewLayout()
{
    delete ui;
}

void ViewLayout::ViewAddAction(QString Name, QMenu *Menu)
{
    QAction *ActionObj = new QAction(Name);
    Menu->addAction(ActionObj);
}
// void ViewLayout::keyPressEvent(QKeyEvent *event)
// {

//     if(event->key() == Qt::Key_Return||event->key() == Qt::Key_Enter)
//     {

//         QPoint MousePos = QCursor::pos();

//         QPoint WidgetPos = mapFromGlobal(MousePos);
//         if(!childAt(MousePos))
//         {
//             if(isOpenLineEditControlSearch)
//             {
//                 isOpenLineEditControlSearch = false;
//                 return;
//             }
//             else
//             {
//                 isOpenLineEditControlSearch = true;
//                 LineEditControlSearch->show();
//             }

//             LineEditControlSearch->move(WidgetPos);

//         }
//     }
// }

bool ViewLayout::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == this && event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter)
        {

            QPoint MousePos = QCursor::pos();
            QPoint WidgetPos = mapFromGlobal(MousePos);
            if(!childAt(WidgetPos))
            {
                if(isOpenLineEditControlSearch)
                {
                    isOpenLineEditControlSearch = false;
                }
                else
                {
                    isOpenLineEditControlSearch = true;
                    LineEditControlSearch->show();
                }
                LineEditControlSearch->move(WidgetPos);
            }

        }
    }
    return QWidget::eventFilter(obj, event);
}

void ViewLayout::DeleteLineEditControlSearch()
{
    LineEditControlSearch->hide();

    // isOpenLineEditControlSearch = false;
}

void ViewLayout::ConfirmLineEditControlSearch()
{

    DeleteLineEditControlSearch();
}

void ViewLayout::RightClick(QAction *Action)
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
            QPoint cursorPos = QCursor::pos();
            QPoint windowPos = mapFromGlobal(cursorPos);

            QPushButton *Button = new QPushButton("New Button", this);
            // connect(this, SIGNAL(ActionChange()), Button, SLOT(ActionChange()));
            Button->move(windowPos);
            Button->show();

        }
        else if (ActionList[ActionList.size() - 2]->text() == Attribute->RightMenuText[1]->Name)
        {
            QPoint cursorPos = QCursor::pos();
            QPoint windowPos = mapFromGlobal(cursorPos);

            QJsonObject *JsonObj = new QJsonObject();
            QJsonObject ProtocolAction = Profile->value("ProtocolAction").toObject();
            JsonObj->insert("ProtocolAction", ProtocolAction);

            EIChangeSlider *Slider = new EIChangeSlider(this, JsonObj);
            connect(this, SIGNAL(ActionChange()), Slider, SLOT(ActionChange()));

            EIChangeSliderGroup.append(Slider);
            Slider->show();
            Slider->move(windowPos);

        }
        else if (ActionList[ActionList.size() - 2]->text() == Attribute->RightMenuText[2]->Name)
        {
            QPoint cursorPos = QCursor::pos();
            QPoint windowPos = mapFromGlobal(cursorPos);

            EIChangeScope *Scope = new EIChangeScope(this);
            connect(this, SIGNAL(ActionChange()), Scope, SLOT(ActionChange()));
            EIChangeScopeGroup.append(Scope);

            Scope->show();
            Scope->move(windowPos);

        }
    }
}

void ViewLayout::DataChange()
{
    emit ActionChange();
}
void ViewLayout::on_ViewLayout_customContextMenuRequested(const QPoint &pos)
{
    Attribute->RClickMenu->exec(QCursor::pos());
}

