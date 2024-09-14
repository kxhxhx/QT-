#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QtSerialPort>
#include <QSerialPortInfo>


#include "eichangesettings.h"
#include "viewlayout.h"
#include "eichangefileview.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    EIChangeSettings JsonSettings;

    ViewLayout CustomViewLayout;

    EIChangeFileView *FileViewObj;

    QList<QSerialPort*> SerialPortGroup;
    QList<int> SerialPortNumber;
    QList<QString> SerialPortNumberUsed;


private:
    Ui::MainWindow *ui;

    void SerialPortNumberGet(void);
    void SerialPortParasSet(void);
    bool SerialPortConfig(void);
    QSerialPort* SerialPortLoad(void);

    void EIChangeSettingsDefault(void);
    bool Config(void);
    bool EIChangeCloseSave(void);


private slots:
    void ProtocolRightClick(void);


    void ViewLayoutRightClick(void);

private slots:
    void on_comboBox_DataEngine_currentIndexChanged(int index);
    void on_pushButton_Load_clicked();

    void on_treeView_Protocol_customContextMenuRequested(const QPoint &pos);
    void on_treeView_ViewLayout_customContextMenuRequested(const QPoint &pos);
    void on_pushButton_Find_clicked();
};
#endif // MAINWINDOW_H
