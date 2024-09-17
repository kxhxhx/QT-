#include "viewlayout.h"
#include "ui_viewlayout.h"
ViewLayout::ViewLayout(QWidget *parent, QJsonObject *Profiles)
    : QWidget(parent)
    , Profiles(Profiles)
    , ui(new Ui::ViewLayout)
    , LineEditControlSearch(new QLineEdit(this))
    , isOpenLineEditControlSearch(false)
    , RClickMenu(new QMenu)
{
    ui->setupUi(this);
    this->installEventFilter(this);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    LineEditControlSearch->hide();

    connect(LineEditControlSearch, SIGNAL(returnPressed()), this, SLOT(ConfirmLineEditControlSearch()));


    RClickMenuText.append("Add Button");
    RClickMenuText.append("Add Slider");
    RClickMenuText.append("Add DoubleSlider");
    RClickMenuText.append("Add Scope");


    for(const QString &MenuText : RClickMenuText)
    {
        ViewAddAction(MenuText, RClickMenu);
    }

    foreach(QAction *Action, RClickMenu->actions())
    {
        connect(Action, SIGNAL(triggered(bool)), this, SLOT(ViewRightClick()));
    }


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

void ViewLayout::ViewRightClick()
{
    QAction *action = qobject_cast<QAction*>(sender());
    if(action->text() == RClickMenuText[ViewLayout::View_AddButton])
    {
        QPoint cursorPos = QCursor::pos();
        QPoint windowPos = mapFromGlobal(cursorPos);

        QPushButton *Button = new QPushButton("New Button", this);
        Button->move(windowPos);
        Button->show();

    }
    else if(action->text() == RClickMenuText[ViewLayout::View_AddSlider])
    {
        QPoint cursorPos = QCursor::pos();
        QPoint windowPos = mapFromGlobal(cursorPos);

        EIChangeSlider *Slider = new EIChangeSlider(this);
        EIChangeSliderGroup.append(Slider);
        Slider->show();
        Slider->move(windowPos);
    }
    else if(action->text() == RClickMenuText[ViewLayout::View_AddDoubleSlider])
    {
        QPoint cursorPos = QCursor::pos();
        QPoint windowPos = mapFromGlobal(cursorPos);

        EIChangeDoubleSlider *Slider = new EIChangeDoubleSlider(this);
        Slider->show();
        Slider->move(windowPos);
    }
    else if(action->text() == RClickMenuText[ViewLayout::View_AddScope])
    {
        QPoint cursorPos = QCursor::pos();
        QPoint windowPos = mapFromGlobal(cursorPos);

        EIChangeScope *Scope = new EIChangeScope(this);
        EIChangeScopeGroup.append(Scope);
        // connect(Scope, SIGNAL(Delete()), this, SLOT(DeleteChildWidget()));
        Scope->show();
        Scope->move(windowPos);
    }

}

void ViewLayout::on_ViewLayout_customContextMenuRequested(const QPoint &pos)
{
    RClickMenu->exec(QCursor::pos());
}

