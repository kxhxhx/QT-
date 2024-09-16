#ifndef EICHANGEWIDGETACTION_H
#define EICHANGEWIDGETACTION_H

#include <QEvent>
#include <QMenu>
#include <QWidgetAction>
#include <QDebug>
class EIChangeWidgetAction : public QWidgetAction
{
    Q_OBJECT

public:
    EIChangeWidgetAction(QObject *Parent);

    bool event(QEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;

public slots:
    void Actived();
    void DisplayChildMenu();


};

#endif // EICHANGEWIDGETACTION_H
