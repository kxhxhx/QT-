#ifndef EICHANGESETTINGS_H
#define EICHANGESETTINGS_H

#include "eichangefiles.h"

class EIChangeSettings
{
public:
    int SettingsVersionNumber;
    QString SettingsFilePath;
    QJsonObject StartConfigJsonObj;
    QJsonObject DataEngineJsonObj;
    QJsonObject ProtocolJsonObj;
    QJsonObject ViewLayoutJsonObj;

    EIChangeFiles FileOperation;
    void SettingsJsonConfig(void);

};

#endif // EICHANGESETTINGS_H
