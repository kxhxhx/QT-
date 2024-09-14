#include "eichangescope.h"
#include "ui_eichangescope.h"

EIChangeScope::EIChangeScope(QWidget *Parent)
    : EIChangeBaseWidget(Parent, "Scope")
    , ui(new Ui::EIChangeScope)
{
    ui->setupUi(this);

    MinWidgetSize.setHeight(100);
    MinWidgetSize.setWidth(100);

    EIChangeAttribute::MenuAttribute* Delete = new EIChangeAttribute::MenuAttribute("Delete");
    Attribute->RightMenuText.append(Delete);

    EIChangeAttribute::MenuAttribute* ScreenShot = new EIChangeAttribute::MenuAttribute("ScreenShot");
    Attribute->RightMenuText.append(ScreenShot);


    EIChangeAttribute::MenuAttribute* YAxis = new EIChangeAttribute::MenuAttribute("YAxis");
    new EIChangeAttribute::MenuAttribute("Hide YAxis", EIChangeBaseMenu::Check, YAxis);
    new EIChangeAttribute::MenuAttribute("All", EIChangeBaseMenu::Check, YAxis);
    Attribute->RightMenuText.append(YAxis);

    EIChangeAttribute::MenuAttribute* XAxis = new EIChangeAttribute::MenuAttribute("XAxis");
    new EIChangeAttribute::MenuAttribute("Hide XAxis", EIChangeBaseMenu::Check, XAxis);
    Attribute->RightMenuText.append(XAxis);

    Attribute->MenuConfig();


    this->installEventFilter(this);
    ui->frame->installEventFilter(this);
    ui->frame->setMouseTracking(true);
    this->setMouseTracking(true);

    ui->label_DisplayPoints->setStyleSheet("color:green;"); // 使用颜色名称

    ui->label_BufferDataSize->setText("0");
    ui->label_BufferLength->setText("50000");
    ui->label_DisplayPoints->setText("1234");

    Chart = new QChart();
    ScopeX = new QValueAxis();
    ScopeY = new QValueAxis();


    ScopeX->setLabelFormat("%i");
    ScopeX->setRange(0, 1000);

    ScopeY->setLabelFormat("%0.2f");
    ScopeY->setRange(0, 10);

    Chart->addAxis(ScopeX, Qt::AlignBottom);
    Chart->addAxis(ScopeY, Qt::AlignLeft);

    ui->graphicsView->setChart(Chart);
    ui->graphicsView->setInteractive(true);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
}

EIChangeScope::~EIChangeScope()
{
    delete ui;
}

void EIChangeScope::DataReceive(QByteArray ScopeData)
{

}

void EIChangeScope::mousePressEvent(QMouseEvent *event)
{
    EIChangeBaseWidget::mousePressEvent(event);
    // static int count = 0;
    // qDebug() << "mousePressEvent" << count++;
}

void EIChangeScope::mouseMoveEvent(QMouseEvent *event)
{
    EIChangeBaseWidget::mouseMoveEvent(event);
    // static int count = 0;
    // qDebug() << "mouseMoveEvent" << count++;
}

void EIChangeScope::mouseReleaseEvent(QMouseEvent *event)
{
    EIChangeBaseWidget::mouseReleaseEvent(event);
    // static int count = 0;
    // qDebug() << "mouseReleaseEvent" << count++;
}

bool EIChangeScope::eventFilter(QObject *obj, QEvent *event)
{

    if(obj == ui->frame)
    {
        if(event->type() == QEvent::Enter)
        {
            setCursor(Qt::ArrowCursor);
            MouseState = EIChangeScope::Deafult;
            qDebug() << "Enter Deafult";

        }
    }
    return EIChangeBaseWidget::eventFilter(obj, event);
}

void EIChangeScope::DragMove(QPoint TargetPoint)
{
    move(TargetPoint);
}



EIChangeChartView::EIChangeChartView(QWidget *parent)
    :QChartView(parent)
{

}

EIChangeChartView::~EIChangeChartView()
{

}

void EIChangeChartView::mousePressEvent(QMouseEvent *event)
{
    QChartView::mousePressEvent(event);
}

void EIChangeChartView::mouseMoveEvent(QMouseEvent *event)
{
    QChartView::mouseMoveEvent(event);
}

void EIChangeChartView::mouseReleaseEvent(QMouseEvent *event)
{
    QChartView::mouseReleaseEvent(event);
}

void EIChangeChartView::mouseDoubleClickEvent(QMouseEvent *event)
{
    QChartView::mouseDoubleClickEvent(event);
}

void EIChangeChartView::wheelEvent(QWheelEvent *event)
{
    QChartView::wheelEvent(event);
}
