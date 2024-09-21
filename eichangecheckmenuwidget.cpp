#include "eichangecheckmenuwidget.h"

EIChangeCheckMenuWidget::EIChangeCheckMenuWidget(QWidget *Parent, QMenu *Menu, QString Text, int Type, QString Data)
    :EIChangeBaseMenuWidget(Parent)
{
    this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    this->setMinimumHeight(30);

    Layout = new QHBoxLayout(this);
    Layout->setContentsMargins(1, 1, 20, 1);
    Spacer = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Fixed);
    QSpacerItem *CheckButtonSpacer = new QSpacerItem(10, 30, QSizePolicy::Fixed, QSizePolicy::Fixed);
    CheckType = Type;
    if(CheckType == EIChangeBaseMenu::CheckandInput)
    {
        InputEdit = new EIChangeLineEdit(this);
        InputEdit->setVisible(false);
        InputEdit->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        Button = new QPushButton(Data, this);
    }

    CheckButton = new QRadioButton(Text, this);
    CheckButton->installEventFilter(this);

    Layout->addItem(CheckButtonSpacer);
    Layout->addWidget(CheckButton);


    if(CheckType == EIChangeBaseMenu::CheckandInput)
    {
        Layout->addWidget(Button);
        Layout->addWidget(InputEdit, 1);
        Layout->addItem(Spacer);
    }



    if(CheckType == EIChangeBaseMenu::CheckandInput)
    {
        DefaultTextInputWidth = InputEdit->width();

        ChildMenu = Menu;
        ChildMenu->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

        this->adjustSize();
        ChildMenu->setMinimumWidth(this->width());



        connect(InputEdit, SIGNAL(editingFinished()), this, SLOT(DisplayCheckButtonText()));
        connect(InputEdit, SIGNAL(textChanged(QString)), this, SLOT(DisplayTextChange(QString)));
        connect(Button, SIGNAL(clicked()), this, SLOT(DisplayInput()));
    }

}

bool EIChangeCheckMenuWidget::eventFilter(QObject *obj, QEvent *event)
{
    if((InputEdit != obj || obj != Button)&&(event->type() == QEvent::MouseButtonPress))
    {
        if(CheckType == EIChangeBaseMenu::CheckandInput)
        {
            if (InputEdit->hasFocus())
            {
                DisplayCheckButtonText();
                return true;
            }
        }
        return true;
    }
    return EIChangeBaseMenuWidget::eventFilter(obj, event);
}

void EIChangeCheckMenuWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(CheckType == EIChangeBaseMenu::CheckandInput)
    {
        if (InputEdit->hasFocus())
        {
            DisplayCheckButtonText();
            return;
        }
    }


    if(CheckButton->isChecked())
    {
        CheckButton->setChecked(false);

    }
    else
    {
        CheckButton->setChecked(true);
    }
    EIChangeBaseMenuWidget::mouseReleaseEvent(event);
}

void EIChangeCheckMenuWidget::DisplayInput()
{
    InputEdit->setText(Button->text());
    InputEdit->setVisible(true);
    InputEdit->setFocus();
    Button->setVisible(false);
}

void EIChangeCheckMenuWidget::DisplayCheckButtonText()
{
    Button->setVisible(true);
    Button->setFocus();
    InputEdit->setVisible(false);
    Button->setGeometry(InputEdit->x(), InputEdit->y(), InputEdit->width(), InputEdit->height());
    Button->setText(InputEdit->text());
}

void EIChangeCheckMenuWidget::DisplayTextChange(QString Text)
{
    QFontMetrics metrics(InputEdit->font());
    int textWidth = metrics.boundingRect(InputEdit->text()).width() + 20;
    if(DefaultTextInputWidth >= textWidth)
    {
        InputEdit->setFixedWidth(DefaultTextInputWidth);
    }
    else
    {
        InputEdit->setFixedWidth(textWidth);
    }


    int MenuMinWidth = 0;
    for(QAction *Action : ChildMenu->actions())
    {
        if (QWidgetAction *widgetAction = qobject_cast<QWidgetAction*>(Action))
        {
            QWidget *widget = widgetAction->defaultWidget();
            if (widget)
            {
                MenuMinWidth = qMax(MenuMinWidth, widget->sizeHint().width());
            }
        }
        else
        {
            MenuMinWidth = qMax(MenuMinWidth, Action->text().size());

        }
    }

    ChildMenu->setFixedWidth(MenuMinWidth);
    ChildMenu->adjustSize();

}

void EIChangeCheckMenuWidget::CheckInterLocked()
{
    // qDebug() << "CheckInterLocked";
    // qDebug() << CheckButton->text();
    CheckButton->setChecked(false);
}
