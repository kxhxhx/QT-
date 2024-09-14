#include "eichangesettings.h"

void EIChangeSettings::SettingsJsonConfig()
{

    SettingsVersionNumber = 0;
    SettingsFilePath = "../../Files/Settings/StartConfig.json";
    StartConfigJsonObj = FileOperation.JsonRead(SettingsFilePath);

    if(StartConfigJsonObj.empty())
    {
        DataEngineJsonObj = {};
        ProtocolJsonObj = {};
        ViewLayoutJsonObj = {};
        StartConfigJsonObj = {};

        DataEngineJsonObj.insert("DataEngineSelect", 0);
        DataEngineJsonObj.insert("SerialPort", 0);
        DataEngineJsonObj.insert("Data Test", 1);

        DataEngineJsonObj.insert("BaudRate", "115200");
        DataEngineJsonObj.insert("FlowControl", "None");
        DataEngineJsonObj.insert("CheckBits", "None");
        DataEngineJsonObj.insert("DataBits", "8");
        DataEngineJsonObj.insert("StopBits", "1");


        ProtocolJsonObj.insert("ProtocolSelect", 0);
        ProtocolJsonObj.insert("DefaultProtocol", 0);

        ViewLayoutJsonObj.insert("ViewLayoutSelect", 0);
        ViewLayoutJsonObj.insert("DefaultViewLayoutJsonObj", 0);


        StartConfigJsonObj.insert("SettingVersion", SettingsVersionNumber);
        StartConfigJsonObj.insert("DataEngineSettings", DataEngineJsonObj);
        StartConfigJsonObj.insert("ProtocolSettings", ProtocolJsonObj);
        StartConfigJsonObj.insert("ViewLayoutSettings", ViewLayoutJsonObj);
        FileOperation.JsonWrite(SettingsFilePath, StartConfigJsonObj, 1);
        return;
    }
    else
    {
        if(StartConfigJsonObj.contains("SettingVersion"))
        {
            if(StartConfigJsonObj["SettingVersion"].toInt() != SettingsVersionNumber)
            {
                DataEngineJsonObj = {};
                ProtocolJsonObj = {};
                ViewLayoutJsonObj = {};
                StartConfigJsonObj = {};

                DataEngineJsonObj.insert("DataEngineSelect", 0);
                DataEngineJsonObj.insert("SerialPort", 0);
                DataEngineJsonObj.insert("Data Test", 1);

                DataEngineJsonObj.insert("BaudRate", "115200");
                DataEngineJsonObj.insert("FlowControl", "None");
                DataEngineJsonObj.insert("CheckBits", "None");
                DataEngineJsonObj.insert("DataBits", "8");
                DataEngineJsonObj.insert("StopBits", "1");


                ProtocolJsonObj.insert("ProtocolSelect", 0);
                ProtocolJsonObj.insert("DefaultProtocol", 0);

                ViewLayoutJsonObj.insert("ViewLayoutSelect", 0);
                ViewLayoutJsonObj.insert("DefaultViewLayoutJsonObj", 0);


                StartConfigJsonObj.insert("SettingVersion", SettingsVersionNumber);
                StartConfigJsonObj.insert("DataEngineSettings", DataEngineJsonObj);
                StartConfigJsonObj.insert("ProtocolSettings", ProtocolJsonObj);
                StartConfigJsonObj.insert("ViewLayoutSettings", ViewLayoutJsonObj);
                FileOperation.JsonWrite(SettingsFilePath, StartConfigJsonObj, 1);
                return;
            }
        }
        else
        {
            DataEngineJsonObj = {};
            ProtocolJsonObj = {};
            ViewLayoutJsonObj = {};
            StartConfigJsonObj = {};

            DataEngineJsonObj.insert("DataEngineSelect", 0);
            DataEngineJsonObj.insert("SerialPort", 0);
            DataEngineJsonObj.insert("Data Test", 1);

            DataEngineJsonObj.insert("BaudRate", "115200");
            DataEngineJsonObj.insert("FlowControl", "None");
            DataEngineJsonObj.insert("CheckBits", "None");
            DataEngineJsonObj.insert("DataBits", "8");
            DataEngineJsonObj.insert("StopBits", "1");


            ProtocolJsonObj.insert("ProtocolSelect", 0);
            ProtocolJsonObj.insert("DefaultProtocol", 0);

            ViewLayoutJsonObj.insert("ViewLayoutSelect", 0);
            ViewLayoutJsonObj.insert("DefaultViewLayoutJsonObj", 0);


            StartConfigJsonObj.insert("SettingVersion", SettingsVersionNumber);
            StartConfigJsonObj.insert("DataEngineSettings", DataEngineJsonObj);
            StartConfigJsonObj.insert("ProtocolSettings", ProtocolJsonObj);
            StartConfigJsonObj.insert("ViewLayoutSettings", ViewLayoutJsonObj);
            FileOperation.JsonWrite(SettingsFilePath, StartConfigJsonObj, 1);
            return;
        }

    }

    DataEngineJsonObj = StartConfigJsonObj["DataEngineSettings"].toObject();
    ProtocolJsonObj = StartConfigJsonObj["ProtocolSettings"].toObject();
    ViewLayoutJsonObj = StartConfigJsonObj["ViewLayoutSettings"].toObject();

}
