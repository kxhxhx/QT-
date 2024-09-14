#ifndef EICHANGEDOUBLESLIDER_H
#define EICHANGEDOUBLESLIDER_H

#include <QWidget>
#include <QMouseEvent>
#include <QDebug>
#include <QStyle>
#include <QStyleOptionSlider>
#include "eichangebasewidget.h"
namespace Ui {
class EIChangeDoubleSlider;
}

class EIChangeDoubleSlider : public QWidget
{
    Q_OBJECT

public:
    explicit EIChangeDoubleSlider(QWidget *Parent = nullptr);
    ~EIChangeDoubleSlider();
    QString StyleSheet1;
    QString StyleSheet2;
    QString GrooveStyle1;
    QString HandleStyle1;
    QString GrooveStyle2;
    QString HandleStyle2;
    QString AddpageStyle1;
    QString SubpageStyle1;
    QString AddpageStyle2;
    QString SubpageStyle2;
    enum SliderMode
    {
        Lower,
        Upper
    };
    int SliderStatus;
    int SliderMinDidstance;
    int GetSliderDidstance(void);

    void SetRange(int Min, int Max);

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
private slots:
    void SetProcess(int position);
    void on_horizontalSlider1_sliderMoved(int position);
    void on_horizontalSlider2_sliderMoved(int position);

private:
    Ui::EIChangeDoubleSlider *ui;
};

#endif // EICHANGEDOUBLESLIDER_H
