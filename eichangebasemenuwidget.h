#ifndef EICHANGEBASEMENUWIDGET_H
#define EICHANGEBASEMENUWIDGET_H

#include <QWidgetAction>
#include <QEvent>
#include <QMouseEvent>
#include <QColor>
#include <QPalette>
#include <QDebug>
#include <QMenu>
#include <QAction>
#include <QWidget>

#include "eichangebasemenu.h"

class EIChangeBaseMenuWidget : public QWidget
{
    Q_OBJECT
public:
    EIChangeBaseMenuWidget(QWidget *Parent = nullptr, QMenu* Menu = nullptr);

    QMenu *WidgetMenu;
    QColor DefaultBackgroundColor;

    QPalette pal;


public slots:
    void Hovered();
    void Leaved();
    void Press();
    void Release();

signals:
    void EnterWidgetAction();
    void Actived();
protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

};

#endif // EICHANGEBASEMENUWIDGET_H
