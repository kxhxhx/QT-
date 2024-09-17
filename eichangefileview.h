#ifndef EICHANGEFILEVIEW_H
#define EICHANGEFILEVIEW_H

#include "eichangetreeview.h"
#include "eichangeslider.h"
#include "viewlayout.h"
class EIChangeFileView : public QObject
{
    Q_OBJECT
public:
    EIChangeFileView(QTreeView * ProtocolTreeView,
                     QTreeView * ViewLayoutTreeView,
                     const QStringList ProtocolTreeViewHead,
                     const QStringList ViewLayoutTreeViewHead);

    EIChangeTreeView ProtocolTree;
    EIChangeTreeView ViewLayoutTree;

    struct ProtocolData
    {
        QString Name;
        QString Time;
        QString DataHead;
        QString SlaveAddress;
        QString FunctionCode;
        QString Data;
        QString CRC;
        QString DataTail;
    };

    struct ViewLayoutData
    {
        QString Name;
        QString Time;

    };
    enum ProtocolHeadIndex {
        Protocol_Name = 0,
        Protocol_Time,
        Protocol_DataHead,
        Protocol_SlaveAddress,
        Protocol_FunctionCode,
        Protocol_Data,
        Protocol_CRC,
        Protocol_DataTail,
    };
    enum ProtocolRightMenu {
        Protocol_AddFile = 0,
        Protocol_AddGroup,
        Protocol_AddProtocol,
        Protocol_SaveFile,
        Protocol_DeleteFile,
    };

    enum ViewLayoutHeadIndexEum
    {
        ViewLayout_Name = 0,
        ViewLayout_Time,
    };
    enum ViewLayoutRightMenu {
        ViewLayout_AddFile = 0,

    };
    QString ProtocolFilePath;
    QString ViewLayoutFilePath;

    QString ProtocolVersion;

    void ProtocolViewAddFile(void);
    void ProtocolViewAddGroup(void);
    void ProtocolViewAddItem(void);
    void ProtocolViewSaveFile(void);
    void ProtocolViewDeleteFile(void);

    void ViewLayoutViewAddFile(void);

    void AddProtocol(QModelIndex CurrentIndex, int CurrentType, int SetChildType, ProtocolData Data);
    void WriteProtocol(QModelIndex CurrentIndex);
    void ReadProtocol(QString ProtocolFilePath);
    QJsonObject ProtocoltoJson(QModelIndex CurrentIndex);
    void JsontoProtocol(QModelIndex CurrentIndex, QJsonObject JsonObj, QString Name);
    void FindProtocol(QString Name);

    void AddViewLayout(QModelIndex CurrentIndex, int CurrentType, int SetChildType, ViewLayoutData Data);
    void WriteViewLayout();

private slots:
    void ProtocolItemChanged(QStandardItem* Item);

};

#endif // EICHANGEFILEVIEW_H
