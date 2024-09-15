#include "eichangecheckmenuwidget.h"

EIChangeCheckMenuWidget::EIChangeCheckMenuWidget(QWidget *Parent, QMenu *Menu, QString Text, int Type, QString Data)
    :EIChangeBaseMenuWidget(Parent)
{
    this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    this->setMinimumHeight(30);

    Layout = new QHBoxLayout(this);
    Layout->setContentsMargins(1, 1, 20, 1);
    Spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Fixed);
    QSpacerItem *CheckButtonSpacer = new QSpacerItem(5, 30, QSizePolicy::Fixed, QSizePolicy::Fixed);
    CheckType = Type;
    if(CheckType == EIChangeBaseMenu::CheckandInput)
    {
        InputEdit = new EIChangeLineEdit(this);
        InputEdit->setVisible(false);
        InputEdit->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        Button = new QPushButton(Data, this);
    }

    CheckButton = new QRadioButton(this);
    CheckButton->setFixedSize(20, 30);
    CheckButton->installEventFilter(this);


    QWidget *Line = new QWidget(this);
    Line->setFixedWidth(2);  // 设置宽度
    Line->setStyleSheet("background-color: white;");  // 设置背景颜色
    Layout->addItem(CheckButtonSpacer);
    Layout->addWidget(CheckButton);

    Layout->addWidget(Line);


    if(CheckType == EIChangeBaseMenu::CheckandInput)
    {
        Layout->addWidget(Button);
        Layout->addWidget(InputEdit, 1);
        Layout->addItem(Spacer);
    }



    if(CheckType == EIChangeBaseMenu::CheckandInput)
    {
        DefaultTextInputWidth = InputEdit->width();
            // DefaultMenuWidth = TestMenu->width();

        TestMenu = Menu;
        TestMenu->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

        this->adjustSize();
        TestMenu->setMinimumWidth(this->width());



        connect(InputEdit, SIGNAL(editingFinished()), this, SLOT(DisplayCheckButtonText()));
        connect(InputEdit, SIGNAL(textChanged(QString)), this, SLOT(DisplayTextChange(QString)));
        connect(Button, SIGNAL(clicked()), this, SLOT(DisplayInput()));
    }

}

bool EIChangeCheckMenuWidget::eventFilter(QObject *obj, QEvent *event)
{
    if((InputEdit != obj || obj != Button)&&(event->type() == QEvent::MouseButtonPress))
    {
        // QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent*>(event);
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
    Button->setVisible(false);

    InputEdit->setText(Button->text());
    InputEdit->setVisible(true);
    InputEdit->setFocus();
}

void EIChangeCheckMenuWidget::DisplayCheckButtonText()
{
    InputEdit->setVisible(false);
    Button->setText(InputEdit->text());
    Button->setVisible(true);
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
    for(QAction *Action : TestMenu->actions())
    {
        if (QWidgetAction *widgetAction = qobject_cast<QWidgetAction*>(Action))
        {
            QWidget *widget = widgetAction->defaultWidget();
            if (widget)
            {
                MenuMinWidth = qMax(MenuMinWidth, widget->sizeHint().width());
                qDebug() << " widget " << widget->sizeHint().width();
            }
        }
        else
        {
            MenuMinWidth = qMax(MenuMinWidth, Action->text().size());
            qDebug() << " Action " << Action->text().size();
        }
    }

    TestMenu->setFixedWidth(MenuMinWidth);
    TestMenu->adjustSize();
    qDebug() << this->width() << MenuMinWidth << textWidth;
}
