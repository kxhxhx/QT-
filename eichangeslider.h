#ifndef EICHANGESLIDER_H
#define EICHANGESLIDER_H

#include <QWidget>
#include "eichangebasewidget.h"

namespace Ui {
class EIChangeSlider;
}

class EIChangeSlider : public EIChangeBaseWidget
{
    Q_OBJECT

public:
    explicit EIChangeSlider(QWidget *Parent = nullptr);
    ~EIChangeSlider();

    enum SignalSource {
        DoubleSpinBox = 0,
        Slider,
    };

    bool eventFilter(QObject *obj, QEvent *event) override;

signals:
    void DoubleSpinBoxEditingFinished(int DoubleSpinBoxSend);

private slots:
    void SliderAction(int SignalSource);
    void RightClick(QAction *Action);
    void on_horizontalSlider_Data_sliderMoved(int position);
    void on_doubleSpinBox_Data_editingFinished();
    void on_doubleSpinBox_Data_valueChanged(double arg1);

private:
    Ui::EIChangeSlider *ui;
};

#endif // EICHANGESLIDER_H
