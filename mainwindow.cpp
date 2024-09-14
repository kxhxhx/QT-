#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Config();

}

MainWindow::~MainWindow()
{
    EIChangeCloseSave();
    delete ui;
}

void MainWindow::SerialPortNumberGet()
{
    //获取端口号信息
    QList<QSerialPortInfo> SerialPortsInfo = QSerialPortInfo::availablePorts();
    ui->comboBox_PortNumber->clear();
    for(int i = 0; i < SerialPortsInfo.count(); i++)
    {
        if(!SerialPortNumberUsed.contains(SerialPortsInfo.at(i).portName()))
            ui->comboBox_PortNumber->addItem(SerialPortsInfo.at(i).portName());
    }
}

void MainWindow::SerialPortParasSet()
{
    ui->comboBox_BaudRate->addItem("9600");
    ui->comboBox_BaudRate->addItem("115200");
    ui->comboBox_BaudRate->addItem("921600");
    ui->comboBox_BaudRate->setEditable(true);

    ui->comboBox_FlowControl->addItem("None");
    ui->comboBox_FlowControl->addItem("Hard");
    ui->comboBox_FlowControl->addItem("Soft");

    ui->comboBox_CheckBits->addItem("None");
    ui->comboBox_CheckBits->addItem("Even");
    ui->comboBox_CheckBits->addItem("Odd");
    ui->comboBox_CheckBits->addItem("Space");
    ui->comboBox_CheckBits->addItem("Mark");

    ui->comboBox_DataBits->addItem("8");
    ui->comboBox_DataBits->addItem("7");
    ui->comboBox_DataBits->addItem("6");
    ui->comboBox_DataBits->addItem("5");

    ui->comboBox_StopBits->addItem("1");
    ui->comboBox_StopBits->addItem("1.5");
    ui->comboBox_StopBits->addItem("2");

    ui->comboBox_BaudRate->setCurrentText(JsonSettings.DataEngineJsonObj["BaudRate"].toString());
    ui->comboBox_FlowControl->setCurrentText(JsonSettings.DataEngineJsonObj["FlowControl"].toString());
    ui->comboBox_CheckBits->setCurrentText(JsonSettings.DataEngineJsonObj["CheckBits"].toString());
    ui->comboBox_DataBits->setCurrentText(JsonSettings.DataEngineJsonObj["DataBits"].toString());
    ui->comboBox_StopBits->setCurrentText(JsonSettings.DataEngineJsonObj["StopBits"].toString());



}

bool MainWindow::SerialPortConfig()
{
    ui->comboBox_PortNumber->installEventFilter(this);
    SerialPortNumberGet();
    SerialPortParasSet();

    return true;
}

QSerialPort* MainWindow::SerialPortLoad()
{
    QSerialPort *SerialPort = new QSerialPort;
    QString PortNumber = ui->comboBox_PortNumber->currentText();

    SerialPortNumberUsed.append(PortNumber);
    QString BaudRate = ui->comboBox_BaudRate->currentText();
    QString FlowControl = ui->comboBox_FlowControl->currentText();
    QString CheckBits = ui->comboBox_CheckBits->currentText();
    QString DataBits = ui->comboBox_DataBits->currentText();
    QString StopBits = ui->comboBox_StopBits->currentText();
    qint32 BaudRateN = BaudRate.toInt();


    //串口参数填入
    SerialPort->setPortName(PortNumber);
    SerialPort->setBaudRate(BaudRateN);

    if(FlowControl == "NONE")
    {
        SerialPort->setFlowControl(QSerialPort::NoFlowControl);
    }
    else if(FlowControl == "Hard")
    {
        SerialPort->setFlowControl(QSerialPort::HardwareControl);
    }
    else if(FlowControl == "Soft")
    {
        SerialPort->setFlowControl(QSerialPort::SoftwareControl);
    }
    if(CheckBits == "NONE")
    {
        SerialPort->setParity(QSerialPort::NoParity);
    }
    else if(CheckBits == "ODD")
    {
        SerialPort->setParity(QSerialPort::OddParity);
    }
    else if(CheckBits == "EVEN")
    {
        SerialPort->setParity(QSerialPort::EvenParity);
    }
    else if(CheckBits == "MARK")
    {
        SerialPort->setParity(QSerialPort::MarkParity);
    }
    else if(CheckBits == "SPACE")
    {
        SerialPort->setParity(QSerialPort::SpaceParity);
    }
    if(DataBits == "5")
    {
        SerialPort->setDataBits(QSerialPort::Data5);
    }
    else if(DataBits == "6")
    {
        SerialPort->setDataBits(QSerialPort::Data6);
    }
    else if(DataBits == "7")
    {
        SerialPort->setDataBits(QSerialPort::Data7);
    }
    else if(DataBits == "8")
    {
        SerialPort->setDataBits(QSerialPort::Data8);
    }
    if(StopBits == "1")
    {
        SerialPort->setStopBits(QSerialPort::OneStop);
    }
    else if(StopBits == "1.5")
    {
        SerialPort->setStopBits(QSerialPort::OneAndHalfStop);
    }
    else if(StopBits == "2")
    {
        SerialPort->setStopBits(QSerialPort::TwoStop);
    }

    return SerialPort;
}

void MainWindow::EIChangeSettingsDefault()
{


}

bool MainWindow::Config()
{

    connect(ui->lineEdit_FindProtocolName, SIGNAL(returnPressed()), this, SLOT(on_pushButton_Find_clicked()));



    ui->treeView_Protocol->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->treeView_ViewLayout->setContextMenuPolicy(Qt::CustomContextMenu);

    QStringList ProtocolHead;
    ProtocolHead <<"FilesName"
                 <<"Time"
                 <<"DataHead"
                 <<"SlaveAddress"
                 <<"FunctionCode"
                 <<"Data"
                 <<"CRC"
                 <<"DataTail";

    QStringList ViewLayoutHead;

    ViewLayoutHead <<"FilesName"
                   <<"Time";

    FileViewObj = new EIChangeFileView(ui->treeView_Protocol,
                                       ui->treeView_ViewLayout,
                                       ProtocolHead,
                                       ViewLayoutHead);

    foreach(QAction *Action, FileViewObj->ProtocolTree.RClickMenu->actions())
    {
        connect(Action, SIGNAL(triggered(bool)), this, SLOT(ProtocolRightClick()));
    }


    foreach(QAction *Action, FileViewObj->ViewLayoutTree.RClickMenu->actions())
    {
        connect(Action, SIGNAL(triggered(bool)), this, SLOT(ViewLayoutRightClick()));
    }


    JsonSettings.SettingsJsonConfig();

    if(JsonSettings.DataEngineJsonObj["DataEngineSelect"].toInt() == 0)
    {
        ui->comboBox_DataEngine->setCurrentIndex(0);
        SerialPortConfig();
    }
    else if(JsonSettings.DataEngineJsonObj["DataEngineSelect"].toInt() == 1)
    {

    }


    return true;

}

bool MainWindow::EIChangeCloseSave()
{
    if(ui->comboBox_DataEngine->currentIndex() == 0)
    {
        JsonSettings.DataEngineJsonObj["DataEngineSelect"] = ui->comboBox_DataEngine->currentIndex();
        JsonSettings.DataEngineJsonObj["BaudRate"] = ui->comboBox_BaudRate->currentText();
        JsonSettings.DataEngineJsonObj["FlowControl"] = ui->comboBox_FlowControl->currentText();
        JsonSettings.DataEngineJsonObj["CheckBits"] = ui->comboBox_CheckBits->currentText();
        JsonSettings.DataEngineJsonObj["DataBits"] = ui->comboBox_DataBits->currentText();
        JsonSettings.DataEngineJsonObj["StopBits"] = ui->comboBox_StopBits->currentText();

    }
    else if(ui->comboBox_DataEngine->currentIndex() == 1)
    {
        JsonSettings.DataEngineJsonObj["DataEngineSelect"] = ui->comboBox_DataEngine->currentIndex();
    }

    JsonSettings.StartConfigJsonObj["DataEngineSettings"] = JsonSettings.DataEngineJsonObj;
    JsonSettings.StartConfigJsonObj["ProtocolSettings"] = JsonSettings.ProtocolJsonObj;
    JsonSettings.StartConfigJsonObj["ViewLayoutSettings"] = JsonSettings.ViewLayoutJsonObj;


    return JsonSettings.FileOperation.JsonWrite(JsonSettings.SettingsFilePath, JsonSettings.StartConfigJsonObj, 1);
}

void MainWindow::ProtocolRightClick()
{
    QAction *action = qobject_cast<QAction*>(sender());
    if(action->text() == FileViewObj->ProtocolTree.RClickMenuText[EIChangeFileView::Protocol_AddFile])
    {
        FileViewObj->ProtocolViewAddFile();
    }
    else if(action->text() == FileViewObj->ProtocolTree.RClickMenuText[EIChangeFileView::Protocol_AddGroup])
    {
        FileViewObj->ProtocolViewAddGroup();
    }
    else if(action->text() == FileViewObj->ProtocolTree.RClickMenuText[EIChangeFileView::Protocol_AddProtocol])
    {
        FileViewObj->ProtocolViewAddItem();

    }
    else if(action->text() == FileViewObj->ProtocolTree.RClickMenuText[EIChangeFileView::Protocol_SaveFile])
    {
        FileViewObj->ProtocolViewSaveFile();
    }
    else if(action->text() == FileViewObj->ProtocolTree.RClickMenuText[EIChangeFileView::Protocol_DeleteFile])
    {
        FileViewObj->ProtocolViewDeleteFile();
    }
}

void MainWindow::ViewLayoutRightClick()
{
    QAction *action = qobject_cast<QAction*>(sender());
    if(action->text() == FileViewObj->ViewLayoutTree.RClickMenuText[EIChangeFileView::ViewLayout_AddFile])
    {
        FileViewObj->ViewLayoutViewAddFile();

    }


}

void MainWindow::on_comboBox_DataEngine_currentIndexChanged(int index)
{
    JsonSettings.DataEngineJsonObj["DataEngineSelect"] = index;
    ui->stackedWidget_DataEngine->setCurrentIndex(index);
    qDebug() << "DataEngineSelect: " << index;
}




void MainWindow::on_pushButton_Load_clicked()
{
    if(JsonSettings.DataEngineJsonObj["DataEngineSelect"].toInt() == 0)
    {
        SerialPortGroup.append(SerialPortLoad());
        if(!SerialPortGroup[SerialPortGroup.size() - 1]->open(QSerialPort::ReadWrite))
        {
            qDebug() << "serialport unsuccessfully ";
        }
        SerialPortNumberGet();
         qDebug() << "serialport successfully ";
    }
    else if(JsonSettings.DataEngineJsonObj["DataEngineSelect"].toInt() == 1)
    {

    }

}

void MainWindow::on_treeView_Protocol_customContextMenuRequested(const QPoint &pos)
{
    // CustomProtocol.RClickMenu->exec(pos);
    FileViewObj->ProtocolTree.RClickMenu->exec(QCursor::pos());
}


void MainWindow::on_treeView_ViewLayout_customContextMenuRequested(const QPoint &pos)
{
    FileViewObj->ViewLayoutTree.RClickMenu->exec(QCursor::pos());
}


void MainWindow::on_pushButton_Find_clicked()
{
    FileViewObj->FindProtocol(ui->lineEdit_FindProtocolName->text());
}

