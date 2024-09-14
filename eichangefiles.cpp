#include "eichangefiles.h"

QJsonObject EIChangeFiles::JsonRead(QString FilePath)
{
    QJsonObject JsonObj = {};
    QFile StartConfigFile(FilePath);
    if(!StartConfigFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "配置文件无法打开";
        return JsonObj;
    }

    QByteArray StartConfigData(StartConfigFile.readAll());
    StartConfigFile.close();

    QJsonParseError jError;
    QJsonDocument StartConfigjDoc = QJsonDocument::fromJson(StartConfigData, &jError);
    if(jError.error != QJsonParseError::NoError)
    {
        qDebug() << "json文件格式错误" << jError.errorString();
        return JsonObj;
    }

    return JsonObj = StartConfigjDoc.object();

}

bool EIChangeFiles::JsonWrite(QString FilePath, QJsonObject JsonObj, int FlagClear)
{
    QFile StartConfigFile(FilePath);
    if(FlagClear == 1)
    {
        if(!StartConfigFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
        {
            qDebug() << "配置文件无法打开";
            return false;
        }
    }
    else
    {
        if(!StartConfigFile.open(QIODevice::WriteOnly))
        {
            qDebug() << "配置文件无法打开";
            return false;
        }
    }

    QJsonDocument jsonDoc;
    jsonDoc.setObject(JsonObj);


    StartConfigFile.write(jsonDoc.toJson());
    StartConfigFile.close();

    return true;

}

QList<QJsonObject> EIChangeFiles::FolderJsonsRead(QString FilePath)
{
    QDir ProtocolDir(FilePath);
    QStringList FileList = ProtocolDir.entryList(QStringList() << "*.json", QDir::Files);
    QList<QJsonObject> JsonList;
    for(const QString& FileName : FileList)
    {
        QJsonObject Jsonobj = JsonRead(ProtocolDir.absoluteFilePath(FileName));
        JsonList.append(Jsonobj);
    }

    return JsonList;

}

bool EIChangeFiles::FindTreeName(QString Name, QStandardItemModel *Model, QModelIndex CurrentIndex, int FlagChild)
{
    bool FlagCheck;
    if(!CurrentIndex.isValid())
        return true;

    QModelIndex ParentIndex = CurrentIndex.parent();
    int CurrentCount = Model->rowCount(ParentIndex);

    for(int row = 0; row < CurrentCount; row++)
    {
        QModelIndex SiblingIndex = Model->index(row, 0, ParentIndex);

        // qDebug()<<Model->data(SiblingIndex).toString();
        if(Model->data(SiblingIndex).toString() == Name)
            return false;

        if(FlagChild == 1)
        {
            FlagCheck = FindTreeName(Name, Model, Model->index(0, 0, SiblingIndex), FlagChild);
            if(FlagCheck == false)
                return false;
        }

    }

    return true;
}

QString EIChangeFiles::GenerateFileName(QStandardItemModel *Model, QModelIndex CurrentIndex, QString BaseName, QString ExtensionName, int FlagChild)
{

    QString FileName;
    int FileIndex = 0;
    while(true)
    {
        if(FileIndex == 0)
        {
            FileName = BaseName + ExtensionName;
        }
        else
        {
            FileName = BaseName + QString::number(FileIndex) + ExtensionName;
        }

        if(FindTreeName(FileName, Model, CurrentIndex, FlagChild))
        {
            return FileName;
        }

        FileIndex++;
    }

}
