#ifndef EICHANGEATTRIBUTE_H
#define EICHANGEATTRIBUTE_H

#include <QWidget>
#include <QDebug>
#include <QMenuBar>
#include <QMenu>
#include <QMouseEvent>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QRadioButton>
#include <QLineEdit>
#include <QWidgetAction>

#include "eichangebasemenuwidget.h"
#include "eichangebasemenu.h"
#include "eichangecheckmenuwidget.h"
#include "eichangeinputmenuwidget.h"
class EIChangeAttribute : public QObject
{
    Q_OBJECT
public:
    EIChangeAttribute(QObject *Parent, QString MenuName);
    ~EIChangeAttribute();
    struct MenuAttribute
    {
        QString Data;
        QString Name;
        int Type;
        QList<MenuAttribute*> Child;
        MenuAttribute *Parent;

        MenuAttribute(const QString &Text = " ", int Type = EIChangeBaseMenu::Text, MenuAttribute *Parent = nullptr, const QString &data = " ");
    };

    EIChangeBaseMenu *RClickMenu;
    QList<MenuAttribute*> RightMenuText;

    void ViewAddMenu(const MenuAttribute& Attribute, EIChangeBaseMenu *Menu);
    void MenuConfig();
signals:
    void Click(QAction *Action);

public slots:
    void RightClick(QAction *Action);
    void RightClickAction(bool Checked);

};

#endif // EICHANGEATTRIBUTE_H