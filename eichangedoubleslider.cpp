#include "eichangedoubleslider.h"
#include "ui_eichangedoubleslider.h"

EIChangeDoubleSlider::EIChangeDoubleSlider(QWidget *Parent)
    : QWidget(Parent)
    , ui(new Ui::EIChangeDoubleSlider)
{
    ui->setupUi(this);

    ui->horizontalSlider1->raise();
    ui->horizontalSlider2->lower();
    GrooveStyle1 = "background: transparent;"
                   "border: 1px solid #bbb;"
                   "height: 10px;"
                   "border-radius: 5px;";

    HandleStyle1 = "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 255, 255, 255), stop:0.495 rgba(100, 100, 100, 255), stop:0.505 rgba(82, 82, 82, 255), stop:1 rgba(255, 255, 255, 255));"
                   "border: 1px solid #777;"
                   "width: 13px;"
                   "margin-top: -2px;"
                   "margin-bottom: -2px;"
                   "border-radius: 7px;";

    GrooveStyle2 = "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(55, 155, 255, 255), stop:1 rgba(55, 155, 255, 255));"
                   "border: 1px solid #bbb;"
                   "height: 10px;"
                   "border-radius: 5px;";

    HandleStyle2 = "background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 255, 255, 255), stop:0.495 rgba(100, 100, 100, 255), stop:0.505 rgba(82, 82, 82, 255), stop:1 rgba(255, 255, 255, 255));"
                   "border: 1px solid #777;"
                   "width: 13px;"
                   "margin-top: -2px;"
                   "margin-bottom: -2px;"
                   "border-radius: 7px;";

    StyleSheet1 = QString("QSlider::groove:horizontal {%1} "
                          "QSlider::handle:horizontal {%2} "
                          "QSlider::add-page:horizontal {%3} "
                          "QSlider::sub-page:horizontal {%4}").arg(GrooveStyle1).arg(HandleStyle1).arg(AddpageStyle1).arg(SubpageStyle1);

    StyleSheet2 = QString("QSlider::groove:horizontal {%1} "
                          "QSlider::handle:horizontal {%2} "
                          "QSlider::add-page:horizontal {%3} "
                          "QSlider::sub-page:horizontal {%4}").arg(GrooveStyle2).arg(HandleStyle2).arg(AddpageStyle2).arg(SubpageStyle2);

    ui->horizontalSlider1->setStyleSheet(StyleSheet1);
    ui->horizontalSlider2->setStyleSheet(StyleSheet2);

    ui->horizontalSlider1->move(0, ui->horizontalSlider1->pos().y());
    ui->horizontalSlider2->move(0, ui->horizontalSlider1->pos().y());
    ui->horizontalSlider1->setFixedWidth(this->width());
    ui->horizontalSlider2->setFixedWidth(this->width());

    SetRange(1, 5000);

    ui->horizontalSlider1->setValue(1);
    ui->horizontalSlider2->setValue(5000);

    ui->horizontalSlider1->installEventFilter(this);
    ui->horizontalSlider2->installEventFilter(this);

    SliderStatus = Upper;
    SliderMinDidstance = 200;


    ui->label1->clear();
    ui->label2->clear();
    ui->label3->clear();
    ui->label1->setStyleSheet("background: #e1e1e1;"
                              "border: 1px solid #bbb;"
                              "height: 10px;"
                              "border-radius: 5px;");

    ui->label2->setStyleSheet("background: #e1e1e1;"
                              "border: 1px solid #bbb;"
                              "height: 10px;"
                              "border-radius: 5px;");

    ui->label3->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #a1c4fd, stop:1 #c2e9fb);");


    ui->label1->setFixedSize(0, ui->horizontalSlider1->height());
    ui->label2->setFixedSize(0, ui->horizontalSlider2->height());

    ui->label3->setFixedSize(0, ui->horizontalSlider1->height() * 0.35);

    ui->label1->move(ui->horizontalSlider1->pos().x(), ui->horizontalSlider1->pos().y() + ui->horizontalSlider1->height() * 0.24);
    ui->label2->move(ui->horizontalSlider1->pos().x() + ui->horizontalSlider1->size().width(), ui->label1->pos().y());
    ui->label3->move(ui->horizontalSlider1->pos().x() + ui->horizontalSlider1->width() * 0.01, ui->horizontalSlider1->pos().y() - ui->label3->height() * 0.85);

}

EIChangeDoubleSlider::~EIChangeDoubleSlider()
{
    delete ui;
}

int EIChangeDoubleSlider::GetSliderDidstance()
{
    return ui->horizontalSlider2->value() - ui->horizontalSlider1->value();
}

void EIChangeDoubleSlider::SetRange(int Min, int Max)
{
    ui->horizontalSlider1->setMinimum(Min);
    ui->horizontalSlider1->setMaximum(Max);

    ui->horizontalSlider2->setMinimum(Min);
    ui->horizontalSlider2->setMaximum(Max);

}

bool EIChangeDoubleSlider::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->horizontalSlider1 || obj == ui->horizontalSlider2)
    {

        if (event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            int value = QStyle::sliderValueFromPosition(ui->horizontalSlider1->minimum(), ui->horizontalSlider1->maximum(), mouseEvent->pos().x(), ui->horizontalSlider1->width());
            int Slider1value = ui->horizontalSlider1->sliderPosition();
            int Slider2value = ui->horizontalSlider2->sliderPosition();
            int diff1 = qAbs(value - Slider1value);
            int diff2 = qAbs(value - Slider2value);

            if (diff1 < diff2)
            {
                if(SliderStatus == Upper)
                {

                }
                else if(SliderStatus == Lower)
                {
                    SliderStatus = Upper;
                    ui->horizontalSlider1->setStyleSheet(StyleSheet1);
                    ui->horizontalSlider2->setStyleSheet(StyleSheet2);
                    ui->horizontalSlider1->raise();
                    ui->horizontalSlider2->lower();
                    emit ui->horizontalSlider2->sliderPressed();
                    return true;
                }
            }
            else
            {
                if(SliderStatus == Lower)
                {

                }
                else if(SliderStatus == Upper)
                {
                    SliderStatus = Lower;
                    ui->horizontalSlider1->setStyleSheet(StyleSheet2);
                    ui->horizontalSlider2->setStyleSheet(StyleSheet1);
                    ui->horizontalSlider2->raise();
                    ui->horizontalSlider1->lower();
                    emit ui->horizontalSlider1->sliderPressed();
                    return true;
                }
            }

        }
        else if (event->type() == QEvent::MouseButtonRelease)
        {

        }
        else if(event->type() == QEvent::MouseMove)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            int value = QStyle::sliderValueFromPosition(ui->horizontalSlider1->minimum(), ui->horizontalSlider1->maximum(), mouseEvent->pos().x(), ui->horizontalSlider1->width());
            if(SliderStatus == Lower)
            {

                if(ui->horizontalSlider1->value() <= value - SliderMinDidstance)
                {

                    int Slider1MoveDistance = ui->horizontalSlider1->value() + value - ui->horizontalSlider2->value();
                    if(Slider1MoveDistance > 0)
                    {
                        emit ui->horizontalSlider1->sliderMoved(Slider1MoveDistance);
                        emit ui->horizontalSlider2->sliderMoved(value);
                    }
                }

            }
            else if(SliderStatus == Upper)
            {
                if(value + SliderMinDidstance <= ui->horizontalSlider2->value())
                {
                    emit ui->horizontalSlider1->sliderMoved(value);
                }
            }
            return true;
        }

    }
    return QObject::eventFilter(obj, event);
}
void EIChangeDoubleSlider::resizeEvent(QResizeEvent *event)
{
    int width = event->size().width();
    int height = event->size().height();


    ui->horizontalSlider1->setFixedWidth(width);
    ui->horizontalSlider2->setFixedWidth(width);

    QWidget::resizeEvent(event);

}

void EIChangeDoubleSlider::SetProcess(int position)
{
    ui->label3->setFixedWidth(float(position *  ui->horizontalSlider1->width()/ ui->horizontalSlider1->maximum()));
}

void EIChangeDoubleSlider::on_horizontalSlider1_sliderMoved(int position)
{
    ui->horizontalSlider1->setValue(position);
    float LabelMoveDistance = ui->horizontalSlider1->size().width() * ui->horizontalSlider1->value() / ui->horizontalSlider1->maximum() - 3;
    if(LabelMoveDistance > 0) ui->label1->setFixedSize(LabelMoveDistance, 12);

}


void EIChangeDoubleSlider::on_horizontalSlider2_sliderMoved(int position)
{
    ui->horizontalSlider2->setValue(position);
    ui->label2->move(float(ui->horizontalSlider1->pos().x() + ui->horizontalSlider1->size().width() * ui->horizontalSlider2->value() / ui->horizontalSlider1->maximum()), float(ui->horizontalSlider1->pos().y() + 2));
    ui->label2->setFixedSize(float(ui->horizontalSlider1->size().width() * (ui->horizontalSlider1->maximum() - ui->horizontalSlider2->value()) / ui->horizontalSlider1->maximum()), 12);

}

