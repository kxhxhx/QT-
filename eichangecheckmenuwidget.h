#ifndef EICHANGECHECKMENUWIDGET_H
#define EICHANGECHECKMENUWIDGET_H

#include "eichangebasemenuwidget.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QRadioButton>
#include <QLineEdit>

#include "eichangelineedit.h"

class EIChangeCheckMenuWidget : public EIChangeBaseMenuWidget
{
    Q_OBJECT
public:
    EIChangeCheckMenuWidget(QWidget *Parent = nullptr, QMenu* Menu = nullptr, QString Text = "", int Type = EIChangeBaseMenu::Check, QString Data = " ");


    int CheckType;
    int DefaultTextInputWidth;
    int DefaultMenuWidth;
    QMenu *TestMenu;
    QHBoxLayout *Layout;
    QSpacerItem *Spacer;
    EIChangeLineEdit *InputEdit;
    QPushButton *Button;
    QRadioButton *CheckButton;


    bool eventFilter(QObject *obj, QEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;


private slots:
    void DisplayInput();
    void DisplayCheckButtonText();
    void DisplayTextChange(QString Text);
};

#endif // EICHANGECHECKMENUWIDGET_H
