#include "eichangeslider.h"
#include "ui_eichangeslider.h"

EIChangeSlider::EIChangeSlider(QWidget *Parent)
    : EIChangeBaseWidget(Parent, "Slider")
    , ui(new Ui::EIChangeSlider)
{
    ui->setupUi(this);

    this->installEventFilter(this);
    this->setMouseTracking(true);
    ui->frame->installEventFilter(this);
    ui->frame->setMouseTracking(true);

    ui->label_Data->installEventFilter(this);
    ui->label_Name->installEventFilter(this);

    EIChangeAttribute::MenuAttribute* Delete = new EIChangeAttribute::MenuAttribute("Delete");
    Attribute->RightMenuText.append(Delete);

    EIChangeAttribute::MenuAttribute* Name = new EIChangeAttribute::MenuAttribute("Name");
    new EIChangeAttribute::MenuAttribute("BindProtocolName", EIChangeBaseMenu::Text, Name);
    new EIChangeAttribute::MenuAttribute("CustomName: ", EIChangeBaseMenu::Input, Name, "Name");
    Attribute->RightMenuText.append(Name);

    EIChangeAttribute::MenuAttribute* Settings = new EIChangeAttribute::MenuAttribute("Settings");
    new EIChangeAttribute::MenuAttribute("Reset", EIChangeBaseMenu::Text, Settings);
    new EIChangeAttribute::MenuAttribute("Max: ", EIChangeBaseMenu::Input, Settings, "1000");
    new EIChangeAttribute::MenuAttribute("Min: ", EIChangeBaseMenu::Input, Settings, "0");
    new EIChangeAttribute::MenuAttribute("Step: ", EIChangeBaseMenu::Input, Settings, "1");
    Attribute->RightMenuText.append(Settings);

    EIChangeAttribute::MenuAttribute* Actions = new EIChangeAttribute::MenuAttribute("Actions");
    new EIChangeAttribute::MenuAttribute("Move: ", EIChangeBaseMenu::CheckandInput, Actions, "00 00 00 00");
    new EIChangeAttribute::MenuAttribute("Release: ", EIChangeBaseMenu::CheckandInput, Actions, "00 00 00 00");
    new EIChangeAttribute::MenuAttribute("Edited: ", EIChangeBaseMenu::CheckandInput, Actions, "00 00 00 00");
    Attribute->RightMenuText.append(Actions);

    // EIChangeAttribute::MenuAttribute* TestMenu0 = new EIChangeAttribute::MenuAttribute("TestMenu0");
    // EIChangeAttribute::MenuAttribute* TestMenu1 = new EIChangeAttribute::MenuAttribute("TestMenu1", EIChangeBaseMenu::CheckandInput, TestMenu0);
    // EIChangeAttribute::MenuAttribute* TestMenu2 = new EIChangeAttribute::MenuAttribute("TestMenu2", EIChangeBaseMenu::CheckandInput, TestMenu1);
    // EIChangeAttribute::MenuAttribute* TestMenu3 = new EIChangeAttribute::MenuAttribute("TestMenu3", EIChangeBaseMenu::CheckandInput, TestMenu2);
    // EIChangeAttribute::MenuAttribute* TestMenu4 = new EIChangeAttribute::MenuAttribute("TestMenu4", EIChangeBaseMenu::CheckandInput, TestMenu3);
    // Attribute->RightMenuText.append(TestMenu0);

    connect(this->Attribute, SIGNAL(Click(QAction*)), this, SLOT(RightClick(QAction*)));
    connect(this, SIGNAL(DoubleSpinBoxEditingFinished(int)), this, SLOT(SliderAction(int)));
    Attribute->MenuConfig();

    ui->label_Data->setAlignment(Qt::AlignCenter);
    ui->doubleSpinBox_Data->setDecimals(5);
    ui->horizontalSlider_Data->setMaximum(10000000);
    ui->doubleSpinBox_Data->setMaximum(10000000);
    ui->doubleSpinBox_Data->setKeyboardTracking(false);

}

EIChangeSlider::~EIChangeSlider()
{
    delete ui;
}
bool EIChangeSlider::eventFilter(QObject *obj, QEvent *event)
{
    // if((obj == ui->label_Data || obj == ui->label_Name) && ((event->type() == QEvent::MouseButtonPress)||(event->type() == QEvent::MouseButtonDblClick)))
    // {
    //     return true;
    // }

    // if((obj == ui->label_Data || obj == ui->label_Name) && ((event->type() == QEvent::MouseButtonRelease)))
    // {
    //     qDebug()<<"release";
    // }
    if(obj == ui->frame && event->type() == QEvent::Enter)
    {
        MouseState = EIChangeBaseWidget::Deafult;
        setCursor(Qt::ArrowCursor);
        qDebug() << "Enter Deafult";

    }
    return EIChangeBaseWidget::eventFilter(obj, event);
}
void EIChangeSlider::SliderAction(int SignalSource)
{
    if(SignalSource == EIChangeSlider::DoubleSpinBox)
    {
        ui->label_Data->setText(QString::number(ui->doubleSpinBox_Data->value(), 'f', ui->doubleSpinBox_Data->decimals()));
        ui->horizontalSlider_Data->setValue(ui->doubleSpinBox_Data->value());
    }
    else if(SignalSource == EIChangeSlider::Slider)
    {
        ui->label_Data->setText(QString::number(ui->horizontalSlider_Data->value(), 'f', ui->doubleSpinBox_Data->decimals()));
        ui->doubleSpinBox_Data->setValue(ui->horizontalSlider_Data->value());
    }

}

void EIChangeSlider::RightClick(QAction *Action)
{
    if(Action)
    {
        QList<QString> ActionMenu;
        ActionMenu.append(Action->text());
        QMenu *RootMenu = qobject_cast<QMenu*>(Action->parent());
        while(RootMenu)
        {
            QString LastTitle = RootMenu->title();
            ActionMenu.append(LastTitle);
            // qDebug() << "Action belongs to QMenu:" << LastTitle;
            QAction *AssociatedAction = RootMenu->menuAction();
            RootMenu = qobject_cast<QMenu*>(AssociatedAction->parent());
            if(LastTitle == RootMenu->title())
                break;
        }

        if(ActionMenu[ActionMenu.size() - 1] == Attribute->RightMenuText[0]->Name)
        {
            this->deleteLater();
            return;

        }
        // else if (ActionMenu[ActionMenu.size() - 1] == Attribute->RightMenuText[1]->Text)
        // {
        //     if(ActionMenu[ActionMenu.size() - 2] == Attribute->RightMenuText[1]->Child[0]->Text)
        //     {

        //     }
        //     else if(ActionMenu[ActionMenu.size() - 2] == Attribute->RightMenuText[1]->Child[1]->Text)
        //     {

        //     }

        // }
        // else if (ActionMenu[ActionMenu.size() - 1] == Attribute->RightMenuText[3]->Text)
        // {

        // }
        // else if (ActionMenu[ActionMenu.size() - 1] == Attribute->RightMenuText[4]->Text)
        // {

        // }
    }



}
void EIChangeSlider::on_horizontalSlider_Data_sliderMoved(int position)
{
    emit DoubleSpinBoxEditingFinished(EIChangeSlider::Slider);
}
void EIChangeSlider::on_doubleSpinBox_Data_editingFinished()
{
    emit DoubleSpinBoxEditingFinished(EIChangeSlider::DoubleSpinBox);

}
void EIChangeSlider::on_doubleSpinBox_Data_valueChanged(double arg1)
{
    emit DoubleSpinBoxEditingFinished(EIChangeSlider::DoubleSpinBox);
}

