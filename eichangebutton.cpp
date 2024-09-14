// #include "eichangebutton.h"

// EIChangeButton::EIChangeButton(const QString &text, QWidget *Parent)
//     :QPushButton(text, Parent)
//     ,Attribute(new EIChangeBaseWidget(Parent))
// {

//     this->installEventFilter(this);
//     this->setMouseTracking(true);

//     EIChangeBaseWidget::MenuText* Delete = new EIChangeBaseWidget::MenuText("Delete");
//     Attribute->RightMenuText.append(Delete);

//     EIChangeBaseWidget::MenuText* Name = new EIChangeBaseWidget::MenuText("Name");
//     EIChangeBaseWidget::MenuText* BindProtocol = Attribute->MenTextAddChild(Name, EIChangeBaseMenu::Text, "BindProtocol");
//     EIChangeBaseWidget::MenuText* CustomName = Attribute->MenTextAddChild(Name, EIChangeBaseMenu::Text, "CustomName");

//     Attribute->RightMenuText.append(Name);


//     connect(this->Attribute, SIGNAL(MovePose(QPoint)), this, SLOT(DragMove(QPoint)));
//     connect(this->Attribute, SIGNAL(Click(QAction*)), this, SLOT(RightClick(QAction*)));

//     Attribute->MenuConfig();

//     // qDebug()<<this->styleSheet();
//     // this->deleteLater();

// }

// void EIChangeButton::mousePressEvent(QMouseEvent *event)
// {
//     Attribute->mousePressEvent(event, QPushButton::pos());
//     QPushButton::mousePressEvent(event);

// }

// void EIChangeButton::mouseMoveEvent(QMouseEvent *event)
// {
//     if(Attribute->FlagAdjust)
//     {
//         QRect Rect = this->rect();
//         QRect ExtendedButtonRect = Rect.adjusted(this->height() * 0.05, this->width() * 0.05, -this->height() * 0.05, -this->width() * 0.05);
//         QRect DragButtonRect = Rect.adjusted(this->height() * 0.1, this->width() * 0.1, -this->height() * 0.1, -this->width() * 0.1);
//         QPoint LocalMousePos = this->mapFromGlobal(event->globalPos());


//         if(Rect.contains(LocalMousePos))
//         {

//             if(ExtendedButtonRect.contains(LocalMousePos))
//             {
//                 if(DragButtonRect.contains(LocalMousePos))
//                 {
//                     if(this->cursor().shape() != Qt::ArrowCursor)
//                     {
//                         setCursor(Qt::ArrowCursor);
//                     }
//                 }
//                 else
//                 {
//                     if(this->cursor().shape() != Qt::OpenHandCursor)
//                     {
//                         setCursor(Qt::OpenHandCursor);
//                     }
//                     Attribute->mouseMoveEvent(event);

//                 }
//             }
//             else
//             {
//                 if(LocalMousePos.x() == this->height() && LocalMousePos.y() == this->width())
//                 {
//                     if(this->cursor().shape() != Qt::SizeFDiagCursor)
//                     {
//                         setCursor(Qt::SizeFDiagCursor);
//                     }
//                     // youxia
//                 }
//                 else if(LocalMousePos.x() == 0 && LocalMousePos.y() == 0)
//                 {
//                     if(this->cursor().shape() != Qt::SizeFDiagCursor)
//                     {
//                         setCursor(Qt::SizeFDiagCursor);
//                     }
//                     // zuoshang
//                 }
//                 else if(LocalMousePos.x() == 0 && LocalMousePos.y() == this->width())
//                 {
//                     if(this->cursor().shape() != Qt::SizeBDiagCursor)
//                     {
//                         setCursor(Qt::SizeBDiagCursor);
//                     }
//                 }
//                 else if(LocalMousePos.x() == this->height() && LocalMousePos.y() == 0)
//                 {
//                     if(this->cursor().shape() != Qt::SizeBDiagCursor)
//                     {
//                         setCursor(Qt::SizeBDiagCursor);
//                     }
//                 }
//             }
//         }
//     }

//     QPushButton::mouseMoveEvent(event);
// }

// void EIChangeButton::mouseReleaseEvent(QMouseEvent *event)
// {
//     Attribute->mouseReleaseEvent(event);
//     QPushButton::mouseReleaseEvent(event);
// }

// bool EIChangeButton::eventFilter(QObject *obj, QEvent *event)
// {
//     if(event->type() == QEvent::MouseMove)
//     {

//     }
//     return QObject::eventFilter(obj, event);
// }

// void EIChangeButton::DragMove(QPoint TargetPoint)
// {
//     move(TargetPoint);
// }

// void EIChangeButton::RightClick(QAction *Action)
// {
//     if(Action->text() == "Delete")
//     {
//         this->setFixedSize(300,150);
//     }
// }
