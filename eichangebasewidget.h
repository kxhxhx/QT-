#ifndef EICHANGEBASEWIDGET_H
#define EICHANGEBASEWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QMouseEvent>
#include "eichangeattribute.h"

class EIChangeBaseWidget : public QWidget
{
    Q_OBJECT

public:
    EIChangeBaseWidget(QWidget *Parent = nullptr, QString Name = "Widget");

    enum MouseStateEum
    {
        Deafult = 0,
        Drag,
        StretchTop,
        StretchBottom,
        StretchLeft,
        StretchRight,
        StretchTopLeft,
        StretchTopRight,
        StretchBottomLeft,
        StretchBottomRight,
    };
    EIChangeAttribute *Attribute;
    EIChangeBaseWidget::MouseStateEum MouseState;

    bool FlagAdjust;
    bool isPress;

    QPoint DragStart;
    QRect StretchStart;
    QSize MinWidgetSize;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;

};

#endif // EICHANGEBASEWIDGET_H
