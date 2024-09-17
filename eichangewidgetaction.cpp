#include "eichangewidgetaction.h"

EIChangeWidgetAction::EIChangeWidgetAction(QObject *Parent)
    :QWidgetAction(Parent)
{

}

bool EIChangeWidgetAction::event(QEvent *event)
{
    return QWidgetAction::event(event);
}

bool EIChangeWidgetAction::eventFilter(QObject *obj, QEvent *event)
{
    return QWidgetAction::eventFilter(obj, event);
}

void EIChangeWidgetAction::CheckInterLocked()
{
    if(!this->property("PressCheck").toBool())
    {
        emit DisableCheck();
        return;
    }
    this->setProperty("PressCheck", false);

}

void EIChangeWidgetAction::Actived()
{
    QMenu *Menu = qobject_cast<QMenu*>(this->parent());
    if(Menu)
    {
        QAction *action = Menu->activeAction();

        if (action != this)
        {
            Menu->setActiveAction(this);
        }
        else
        {

        }
    }

}

void EIChangeWidgetAction::DisplayChildMenu()
{

}
