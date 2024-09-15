#include "eichangebasemenu.h"

EIChangeBaseMenu::~EIChangeBaseMenu()
{

}

void EIChangeBaseMenu::ActiontoWidgetAction()
{
    setActiveAction(nullptr);
}

bool EIChangeBaseMenu::eventFilter(QObject *obj, QEvent *event)
{
    return QMenu::eventFilter(obj, event);
}

void EIChangeBaseMenu::mouseMoveEvent(QMouseEvent *event)
{
    QMenu::mouseMoveEvent(event);
}

void EIChangeBaseMenu::mousePressEvent(QMouseEvent *event)
{
    QMenu::mousePressEvent(event);
}

void EIChangeBaseMenu::mouseReleaseEvent(QMouseEvent *event)
{
    Action = this->actionAt(event->pos());

    if(Action)
    {
        int Type = Action->property("Type").toInt();
        if((Type == EIChangeBaseMenu::CheckandInput)||(Type == EIChangeBaseMenu::Check)||(Type == EIChangeBaseMenu::Input))
        {
            emit CheckActionTrigger(Action);
            return;
        }
    }

    QMenu::mouseReleaseEvent(event);


}

void EIChangeBaseMenu::keyPressEvent(QKeyEvent * event)
{
    if(event->key() == Qt::Key_Return||event->key() == Qt::Key_Enter)
    {
        return;
    }
    QMenu::keyPressEvent(event);
}

void EIChangeBaseMenu::leaveEvent(QEvent *event)
{

    QMenu::leaveEvent(event);

}

void EIChangeBaseMenu::enterEvent(QEvent *event)
{

    QMenu::enterEvent(event);
}
