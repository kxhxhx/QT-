#ifndef VIEWLAYOUT_H
#define VIEWLAYOUT_H

#include <QWidget>
#include <QKeyEvent>
#include <QDebug>
#include <QLineEdit>
#include <QMenu>
#include <QPushButton>

#include <QHBoxLayout>

#include "eichangebutton.h"
#include "eichangeslider.h"
#include "eichangedoubleslider.h"
#include "eichangescope.h"


namespace Ui {
class ViewLayout;
}

class ViewLayout : public QWidget
{
    Q_OBJECT

public:
    explicit ViewLayout(QWidget *parent = nullptr, QJsonObject *Profiles = nullptr);
    ~ViewLayout();


    enum ViewRightMenu {
        View_AddButton = 0,
        View_AddSlider,
        View_AddDoubleSlider,
        View_AddScope,
    };
    QJsonObject *Profiles;
    bool isOpenLineEditControlSearch;
    QLineEdit *LineEditControlSearch;

    void ViewAddAction(QString Name, QMenu *Menu);
    QMenu* RClickMenu;
    QList<QString> RClickMenuText;
    QList<EIChangeSlider*> EIChangeSliderGroup;
    QList<EIChangeScope*> EIChangeScopeGroup;

private:
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void DeleteLineEditControlSearch();
    void ConfirmLineEditControlSearch();
    void ViewRightClick();
    void on_ViewLayout_customContextMenuRequested(const QPoint &pos);

private:
    Ui::ViewLayout *ui;
};

#endif // VIEWLAYOUT_H
