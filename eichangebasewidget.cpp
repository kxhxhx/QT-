#include "eichangebasewidget.h"

EIChangeBaseWidget::EIChangeBaseWidget(QWidget *Parent, QString Name)
    :QWidget(Parent)
    ,Attribute(new EIChangeAttribute(Parent, Name))
    ,isPress(false)
    ,FlagAdjust(true)
    ,MouseState(EIChangeBaseWidget::Deafult)
{
    this->installEventFilter(this);
}
void EIChangeBaseWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton && MouseState == Deafult)
    {
        Attribute->RClickMenu->exec(QCursor::pos());
    }
    if(FlagAdjust)
    {
        if(event->button() == Qt::LeftButton)
        {
            isPress = true;
            DragStart = event->globalPos() - this->pos();
            StretchStart = this->geometry();
            if(MouseState == Deafult)
            {
                setCursor(Qt::ClosedHandCursor);
                MouseState = EIChangeBaseWidget::Drag;
            }
            qDebug() << "pressed";

            grabMouse();
        }


        // if(event->button() == Qt::LeftButton && MouseState == StretchTop)
    }
    QWidget::mousePressEvent(event);

}

void EIChangeBaseWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(FlagAdjust)
    {
        if(MouseState == Deafult)
        {
            QPoint WidgetMousePos = this->mapFromGlobal(event->globalPos());
            QPoint LocalMousePos;
            LocalMousePos.rx() = WidgetMousePos.x() - 5;
            LocalMousePos.ry() = WidgetMousePos.y() - 5;
            int FrameWidth = this->width() - 10;
            int FrameHeight = this->height() - 10;
            float topLeft = LocalMousePos.x() * LocalMousePos.x() + LocalMousePos.y() * LocalMousePos.y();
            float bottomRight = (LocalMousePos.x() - FrameWidth) * (LocalMousePos.x() - FrameWidth) + (LocalMousePos.y() - FrameHeight) * (LocalMousePos.y() - FrameHeight);
            float topRight = (LocalMousePos.x() - FrameWidth) * (LocalMousePos.x() - FrameWidth) + (LocalMousePos.y()) * (LocalMousePos.y());
            float bottomLeft = (LocalMousePos.x()) * (LocalMousePos.x()) + (LocalMousePos.y() - FrameHeight) * (LocalMousePos.y() - FrameHeight);
            if((LocalMousePos.y() > FrameHeight)&&(LocalMousePos.x() >= 25 && LocalMousePos.x() <= FrameWidth - 25))
            {
                setCursor(Qt::SizeVerCursor);
                MouseState = EIChangeBaseWidget::StretchBottom;
                //qDebug() << "StretchBottom";
            }
            else if((LocalMousePos.y() < 0)&&(LocalMousePos.x() >= 25 && LocalMousePos.x() <= FrameWidth - 25))
            {
                setCursor(Qt::SizeVerCursor);
                MouseState = EIChangeBaseWidget::StretchTop;
                //qDebug() << "StretchTop" << LocalMousePos.y();
            }
            else if((LocalMousePos.x() < 0)&&(LocalMousePos.y() >= 25 && LocalMousePos.y() <= FrameHeight - 25))
            {
                setCursor(Qt::SizeHorCursor);
                MouseState = EIChangeBaseWidget::StretchLeft;
                //qDebug() << "StretchLeft";
            }
            else if((LocalMousePos.x() > FrameWidth)&&(LocalMousePos.y() >= 25 && LocalMousePos.y() <= FrameHeight - 25))
            {
                setCursor(Qt::SizeHorCursor);
                MouseState = EIChangeBaseWidget::StretchRight;
                //qDebug() << "StretchRight";
            }
            else if(topLeft <= 25)
            {
                setCursor(Qt::SizeFDiagCursor);
                MouseState = EIChangeBaseWidget::StretchTopLeft;
                //qDebug() << "StretchTopLeft";
            }
            else if(bottomRight <= 25)
            {
                setCursor(Qt::SizeFDiagCursor);
                MouseState = EIChangeBaseWidget::StretchBottomRight;
                //qDebug() << "StretchBottomRight";
            }
            else if(topRight <= 25)
            {
                setCursor(Qt::SizeBDiagCursor);
                MouseState = EIChangeBaseWidget::StretchTopRight;
                //qDebug() << "StretchTopRight";
            }
            else if(bottomLeft <= 25)
            {
                setCursor(Qt::SizeBDiagCursor);
                MouseState = EIChangeBaseWidget::StretchBottomLeft;
                //qDebug() << "StretchBottomLeft";
            }
        }

        if(isPress)
        {

            switch(MouseState)
            {
                case EIChangeBaseWidget::Deafult:break;
                case EIChangeBaseWidget::Drag:
                {
                    move(event->globalPos() - DragStart);
                    break;
                }

                case EIChangeBaseWidget::StretchTop:
                {
                    int DeltaY = event->globalPos().y() - DragStart.y();
                    int NewHeight = StretchStart.height() + StretchStart.y() - DeltaY;
                    if(NewHeight >= MinWidgetSize.height())
                        setGeometry(StretchStart.x(), DeltaY, StretchStart.width(), NewHeight);
                    break;
                }
                case EIChangeBaseWidget::StretchBottom:
                {
                    int DeltaY = event->globalPos().y() - DragStart.y();
                    int NewHeight = StretchStart.height() + DeltaY - StretchStart.y();
                    //qDebug() << NewHeight;
                    if(NewHeight >= MinWidgetSize.height())
                        setGeometry(StretchStart.x(), StretchStart.y(), StretchStart.width(), NewHeight);
                    break;
                }
                case EIChangeBaseWidget::StretchLeft:
                {
                    int DeltaX = event->globalPos().x() - DragStart.x();
                    int NewWidth = StretchStart.width() + StretchStart.x() - DeltaX;
                    //qDebug() << DeltaX;
                    if(NewWidth >= MinWidgetSize.width())
                        setGeometry(DeltaX, StretchStart.y(), NewWidth, StretchStart.height());
                    break;
                }
                case EIChangeBaseWidget::StretchRight:
                {
                    int DeltaX = event->globalPos().x() - DragStart.x();
                    int NewWidth = StretchStart.width() + DeltaX - StretchStart.x();
                    //qDebug() << NewWidth;
                    if(NewWidth >= MinWidgetSize.width())
                        setGeometry(StretchStart.x(), StretchStart.y(), NewWidth, StretchStart.height());
                    break;
                }
                case EIChangeBaseWidget::StretchTopLeft:
                {
                    QPoint DeltaXY = event->globalPos() - DragStart;
                    QPoint NewPoint;
                    NewPoint.rx() = StretchStart.x() - DeltaXY.x();
                    NewPoint.ry() = StretchStart.y() - DeltaXY.y();
                    int NewWidth = StretchStart.width() + NewPoint.x();
                    int NewHeight = StretchStart.height() + NewPoint.y();

                    if(NewWidth >= MinWidgetSize.width() && NewHeight >= MinWidgetSize.height())
                        setGeometry(DeltaXY.x(), DeltaXY.y(), NewWidth, NewHeight);
                    break;
                }
                case EIChangeBaseWidget::StretchTopRight:
                {
                    QPoint DeltaXY = event->globalPos() - DragStart;
                    QPoint NewPoint;
                    NewPoint.rx() = DeltaXY.x() - StretchStart.x();
                    NewPoint.ry() = StretchStart.y() - DeltaXY.y();
                    int NewWidth = StretchStart.width() + NewPoint.x();
                    int NewHeight = StretchStart.height() + NewPoint.y();

                    if(NewWidth >= MinWidgetSize.width() && NewHeight >= MinWidgetSize.height())
                        setGeometry(StretchStart.x(), DeltaXY.y(), NewWidth, NewHeight);
                    break;
                }
                case EIChangeBaseWidget::StretchBottomLeft:
                {
                    QPoint DeltaXY = event->globalPos() - DragStart;
                    QPoint NewPoint;
                    NewPoint.rx() = StretchStart.x() - DeltaXY.x();
                    NewPoint.ry() = DeltaXY.y() - StretchStart.y();
                    int NewWidth = StretchStart.width() + NewPoint.x();
                    int NewHeight = StretchStart.height() + NewPoint.y();

                    if(NewWidth >= MinWidgetSize.width() && NewHeight >= MinWidgetSize.height())
                        setGeometry(DeltaXY.x(), StretchStart.y(), NewWidth, NewHeight);
                    break;
                }
                case EIChangeBaseWidget::StretchBottomRight:
                {
                    QPoint DeltaXY = event->globalPos() - DragStart;
                    QPoint NewPoint;
                    NewPoint.rx() = StretchStart.width() + DeltaXY.x() - StretchStart.x();
                    NewPoint.ry() = StretchStart.height() + DeltaXY.y() - StretchStart.y();
                    //qDebug() << NewPoint;
                    if(NewPoint.x() >= MinWidgetSize.width() && NewPoint.y() >= MinWidgetSize.height())
                        setGeometry(StretchStart.x(), StretchStart.y(), NewPoint.x(), NewPoint.y());
                    break;
                }

            }
        }
    }

    QWidget::mouseMoveEvent(event);
}
void EIChangeBaseWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        MouseState = EIChangeBaseWidget::Deafult;
        setCursor(Qt::ArrowCursor);
        isPress = false;
        qDebug() << "notpress";
        releaseMouse();
    }

    QWidget::mouseReleaseEvent(event);
}

bool EIChangeBaseWidget::eventFilter(QObject *obj, QEvent *event)
{
    return QWidget::eventFilter(obj, event);
}
