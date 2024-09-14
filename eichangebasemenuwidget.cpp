#include "eichangebasemenuwidget.h"

EIChangeBaseMenuWidget::EIChangeBaseMenuWidget(QWidget *Parent, QMenu* Menu)
    :QWidget(Parent)
    ,WidgetMenu(Menu)
{

    pal = this->palette();
    DefaultBackgroundColor = pal.color(QPalette::Window);
    pal.setColor(QPalette::Window, DefaultBackgroundColor);
    this->setAutoFillBackground(true);
    this->setPalette(pal);

}

void EIChangeBaseMenuWidget::Hovered()
{
    pal.setColor(QPalette::Window, QColor(144, 200, 246));
    this->setPalette(pal);
}

void EIChangeBaseMenuWidget::Leaved()
{
    pal.setColor(QPalette::Window, DefaultBackgroundColor);
    this->setPalette(pal);
}

void EIChangeBaseMenuWidget::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
}

bool EIChangeBaseMenuWidget::eventFilter(QObject *obj, QEvent *event)
{
    return QWidget::eventFilter(obj, event);
}

void EIChangeBaseMenuWidget::enterEvent(QEvent *event)
{
    Hovered();
    emit EnterWidgetAction();
    QWidget::enterEvent(event);
}

void EIChangeBaseMenuWidget::leaveEvent(QEvent *event)
{
    Leaved();
    QWidget::leaveEvent(event);
}
