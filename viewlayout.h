#ifndef VIEWLAYOUT_H
#define VIEWLAYOUT_H

#include <QWidget>
#include <QKeyEvent>
#include <QDebug>
#include <QLineEdit>
#include <QMenu>
#include <QPushButton>
#include <QHBoxLayout>
#include "eichangeattribute.h"
#include "eichangeitemmodel.h"


#include "eichangebutton.h"
#include "eichangeslider.h"
#include "eichangescope.h"


namespace Ui {
class ViewLayout;
}

class ViewLayout : public QWidget
{
    Q_OBJECT

public:
    explicit ViewLayout(QWidget *parent = nullptr, QJsonObject Profiles = QJsonObject(), EIChangeItemMode *DataModel = nullptr);
    ~ViewLayout();

    EIChangeAttribute *Attribute;

    QStandardItemModel *DataModel;
    QJsonObject *Profile;
    bool isOpenLineEditControlSearch;
    QLineEdit *LineEditControlSearch;

    void ViewAddAction(QString Name, QMenu *Menu);

    QList<EIChangeSlider*> EIChangeSliderGroup;
    QList<EIChangeScope*> EIChangeScopeGroup;

signals:
    void ActionChange();

private:
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void RightClick(QAction* Action);
    void DataChange(QModelIndex topLeft, QModelIndex bottomRight, QVector<int> roles);
    void DeleteLineEditControlSearch();
    void ConfirmLineEditControlSearch();
    void on_ViewLayout_customContextMenuRequested(const QPoint &pos);

private:
    Ui::ViewLayout *ui;
};

#endif // VIEWLAYOUT_H
