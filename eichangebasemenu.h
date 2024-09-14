#ifndef EICHANGEBASEMENU_H
#define EICHANGEBASEMENU_H

#include <QMenu>
#include <QAction>
#include <QWidgetAction>
#include <QWidget>
#include <QMouseEvent>
#include <QEvent>
#include <QDebug>
#include <QTimer>
#include <QRadioButton>
// #include "eichangecheckmenuwidget.h"

class EIChangeBaseMenu : public QMenu
{
    Q_OBJECT
public:
    explicit EIChangeBaseMenu(QWidget *parent = nullptr)
    : QMenu(parent) {

    }

    explicit EIChangeBaseMenu(const QString &title, QWidget *parent = nullptr)
    : QMenu(title, parent) {

    }

    ~EIChangeBaseMenu();
public:
    enum MenuActionType
    {
        Text = 0,
        Input,
        Check,
        CheckandInput,
    };
    QAction *Action;
signals:
    void CheckActionTrigger(QAction *Action);

public slots:
    void ActiontoWidgetAction();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void enterEvent(QEvent *event) override;
};


#endif // EICHANGEBASEMENU_H
