#include "eichangeinputmenuwidget.h"


EIChangeInputMenuWidget::EIChangeInputMenuWidget(QWidget *Parent, EIChangeBaseMenu *Menu, QString Name, QString Data)
    :EIChangeBaseMenuWidget(Parent)
{
    this->installEventFilter(this);
    // this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    this->setMinimumHeight(30);

    Layout = new QHBoxLayout(this);
    Layout->setContentsMargins(1, 1, 20, 1);
    Label = new QLabel(Name, this);
    Label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    Spacer = new QSpacerItem(10, 30, QSizePolicy::Expanding, QSizePolicy::Fixed);
    IconSpacer = new QSpacerItem(33, 30, QSizePolicy::Fixed, QSizePolicy::Fixed);

    QWidget *Line = new QWidget(this);
    Line->setFixedWidth(2);  // 设置宽度
    Line->setStyleSheet("background-color: white;");  // 设置背景颜色


    InputEdit = new QLineEdit(this);
    InputEdit->setVisible(false);
    InputEdit->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    Button = new QPushButton(Data, this);

    Layout->addItem(IconSpacer);
    Layout->addWidget(Line);
    Layout->addWidget(Label);

    QHBoxLayout *Layout1 = new QHBoxLayout();

    Layout1->addWidget(Button);
    Layout1->addWidget(InputEdit);

    Layout->addLayout(Layout1);

    Layout->addItem(Spacer);


    DefaultTextInputWidth = InputEdit->width();

    ChildMenu = Menu;
    ChildMenu->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    this->adjustSize();
    ChildMenu->setMinimumWidth(this->width());
    ChildMenu->adjustSize();


    connect(InputEdit, SIGNAL(editingFinished()), this, SLOT(DisplayCheckButtonText()));
    connect(InputEdit, SIGNAL(textChanged(QString)), this, SLOT(DisplayTextChange(QString)));
    connect(Button, SIGNAL(clicked()), this, SLOT(DisplayInput()));


}

bool EIChangeInputMenuWidget::eventFilter(QObject *obj, QEvent *event)
{
    if((event->type() == QEvent::MouseButtonPress))
    {
        QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent*>(event);
        if (InputEdit->hasFocus())
        {
            DisplayCheckButtonText();
        }
        return true;
    }
    return EIChangeBaseMenuWidget::eventFilter(obj, event);
}

void EIChangeInputMenuWidget::mouseReleaseEvent(QMouseEvent *event)
{

    EIChangeBaseMenuWidget::mouseReleaseEvent(event);
}

void EIChangeInputMenuWidget::DisplayInput()
{
    Button->setVisible(false);
    // InputEdit->setGeometry(Button->x(), Button->y(), InputEdit->width(), InputEdit->height());
    InputEdit->setText(Button->text());
    InputEdit->setVisible(true);
    InputEdit->setFocus();
}

void EIChangeInputMenuWidget::DisplayCheckButtonText()
{
    InputEdit->setVisible(false);
    Button->setGeometry(InputEdit->x(), InputEdit->y(), InputEdit->width(), InputEdit->height());
    Button->setText(InputEdit->text());

    Button->setVisible(true);
}

void EIChangeInputMenuWidget::DisplayTextChange(QString Text)
{
    // QFontMetrics metrics(InputEdit->font());
    // int textWidth = metrics.boundingRect(InputEdit->text()).width() + 20;
    // qDebug() << textWidth << DefaultTextInputWidth << Label->width() << ChildMenu->width();
    // if(DefaultTextInputWidth >= textWidth)
    // {
    //     InputEdit->setFixedWidth(DefaultTextInputWidth);
    // }
    // else
    // {
    //     InputEdit->setFixedWidth(textWidth);
    // }
    // this->adjustSize();
    QSize LineEditLength = QSize(InputEdit->fontMetrics().horizontalAdvance(Text) + 20, 30);
    InputEdit->setFixedSize(LineEditLength);
    qDebug() << this->width();
    int MenuMinWidth = 0;
    for(QAction *Action : ChildMenu->actions())
    {
        if (QWidgetAction *widgetAction = qobject_cast<QWidgetAction*>(Action))
        {
            QWidget *widget = widgetAction->defaultWidget();
            if (widget)
            {
                MenuMinWidth = qMax(MenuMinWidth, widget->sizeHint().width());
                qDebug() << " widget " << widget->sizeHint().width();
                qDebug() << widgetAction->text();
            }
        }
        else
        {
            MenuMinWidth = qMax(MenuMinWidth, Action->text().size());
            qDebug() << " Action "<< Action->text().size();
        }
        // qDebug() << this->width() << MenuMinWidth << textWidth;
    }

    ChildMenu->setFixedWidth(MenuMinWidth);
    ChildMenu->adjustSize();
    // qDebug() << this->width() << MenuMinWidth << textWidth;
}