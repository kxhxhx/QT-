#ifndef EICHANGEPROTOCOLFILEVIEW_H
#define EICHANGEPROTOCOLFILEVIEW_H

#include "eichangetreeview.h"
#include "eichangeattribute.h"


class EIChangeProtocolFileView : public EIChangeTreeView
{
    Q_OBJECT
public:
    EIChangeProtocolFileView(QTreeView *TreeView, const QStringList Head);

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
    QString ProtocolVersion;
    QString FilePath = "../../Files/Protocol/";
    QString Version;

    void AddProtocol(QModelIndex CurrentIndex, int CurrentType, int SetChildType, ProtocolData Data);
    void DeleteProtocol();
    void WriteProtocol(QModelIndex CurrentIndex);
    void ReadProtocol(QString ProtocolFilePath);

    QJsonObject ProtocoltoJson(QModelIndex CurrentIndex);
    void JsontoProtocol(QStandardItem *ParentItem, QJsonObject JsonObj);

    QJsonArray ProtocoltoJson(QModelIndex CurrentIndex, int FlagDiff);
    void JsontoProtocol(QStandardItem *ParentItem, QJsonArray JsonObj);

    //void FindProtocol(QString Name);
private slots:
    void RightClick(QAction *Action);


};

#endif // EICHANGEPROTOCOLFILEVIEW_H
