#ifndef EICHANGEINPUTMENUWIDGET_H
#define EICHANGEINPUTMENUWIDGET_H

#include "eichangebasemenuwidget.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QRadioButton>
#include <QLineEdit>

class EIChangeInputMenuWidget : public EIChangeBaseMenuWidget
{
    Q_OBJECT
public:
    EIChangeInputMenuWidget(QWidget *Parent = nullptr, EIChangeBaseMenu* Menu = nullptr, QString Name = " ", QString Data = " ");

    int DefaultTextInputWidth;
    int DefaultMenuWidth;
    EIChangeBaseMenu *ChildMenu;
    QSpacerItem *IconSpacer;
    QSpacerItem *Spacer;
    QHBoxLayout *Layout;
    QLabel *Label;
    QLineEdit *InputEdit;
    QPushButton *Button;

    bool eventFilter(QObject *obj, QEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;


private slots:
    void DisplayInput();
    void DisplayCheckButtonText();
    void DisplayTextChange(QString Text);
};

#endif // EICHANGEINPUTMENUWIDGET_H
