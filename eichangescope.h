#ifndef EICHANGESCOPE_H
#define EICHANGESCOPE_H

#include <QWidget>
#include "eichangebasewidget.h"
#include <QtCharts>
#include <QChartView>

#include <QDebug>
#include <QtMath>

#include "eichangeattribute.h"
#include "eichangedoubleslider.h"

namespace Ui {
class EIChangeScope;
}
class EIChangeChartView : public QChartView
{
    Q_OBJECT
public:
    explicit EIChangeChartView(QWidget *parent = nullptr);
    ~EIChangeChartView();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

signals:
    void signalMouseEvent(int eventId, QMouseEvent *event);
    void signalWheelEvent(QWheelEvent *event);


};
class EIChangeScope : public EIChangeBaseWidget
{
    Q_OBJECT

public:
    explicit EIChangeScope(QWidget *Parent = nullptr);
    ~EIChangeScope();

    struct Protocol
    {
        QByteArray Head;
        QByteArray FunctionCode;
        QByteArray SlaveAddress;
        QByteArray Data;
        QByteArray CRC;
        QByteArray Tail;
    };

    EIChangeScope::Protocol TestProtocol;
    QList<QLineSeries*> DataSeriesGroup;
    QValueAxis *ScopeX;
    QValueAxis *ScopeY;
    QChart *Chart;

    void DataReceive(QByteArray ScopeData);
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;


signals:
    // void Delete();
private slots:
    void DragMove(QPoint TargetPoint);
private:
    Ui::EIChangeScope *ui;
};

#endif // EICHANGESCOPE_H
