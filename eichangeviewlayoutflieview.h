#ifndef EICHANGEVIEWLAYOUTFLIEVIEW_H
#define EICHANGEVIEWLAYOUTFLIEVIEW_H


#include "eichangetreeview.h"
#include "eichangeattribute.h"
#include "viewlayout.h"
class EIChangeViewLayoutFlieView : public EIChangeTreeView
{
    Q_OBJECT
public:
    EIChangeViewLayoutFlieView(QTreeView *TreeView, const QStringList Head);

    enum ViewLayoutHeadIndexEum
    {
        ViewLayout_Name = 0,
        ViewLayout_Data,
    };
    struct ViewLayoutData
    {
        QString Name;
        QString Data;
    };
    EIChangeItemMode *DataModel;

    QList<ViewLayout*> ViewLayoutList;

    QString FilePath = "../../Files/ViewLayout/";
    QString Version;

    void AddViewLayout(QModelIndex CurrentIndex, int CurrentType, int SetChildType, ViewLayoutData Data);

private slots:
    void RightClick(QAction *Action);

};

#endif // EICHANGEVIEWLAYOUTFLIEVIEW_H
