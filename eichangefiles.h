#ifndef EICHANGEFILES_H
#define EICHANGEFILES_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>

#include <QStandardItemModel>
#include <QFile>
#include <QDir>
class EIChangeFiles
{
public:
    QJsonObject JsonRead(QString FilePath);
    bool JsonWrite(QString FilePath, QJsonObject JsonObj, int FlagClear);
    QList<QJsonObject> FolderJsonsRead(QString FilePath);
    bool FindTreeName(QString Name, QStandardItemModel *Model, QModelIndex CurrentIndex, int FlagChild);
    QString GenerateFileName(QStandardItemModel *itemModel, QModelIndex CurrentIndex, QString BaseName, QString ExtensionName, int FlagChild);
};

#endif // EICHANGEFILES_H
