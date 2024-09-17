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
    EIChangeAttribute::MenuAttribute* BindProtocolName = new EIChangeAttribute::MenuAttribute("BindProtocolName", EIChangeBaseMenu::Check, Name);
    BindProtocolName->CheckInterLock = true;
    EIChangeAttribute::MenuAttribute* CustomName = new EIChangeAttribute::MenuAttribute("CustomName: ", EIChangeBaseMenu::CheckandInput, Name, "Name");
    CustomName->CheckInterLock = true;
    Attribute->RightMenuText.append(Name);

    EIChangeAttribute::MenuAttribute* BindProtocol = new EIChangeAttribute::MenuAttribute("BindProtocol");
    // new EIChangeAttribute::MenuAttribute("Reset", EIChangeBaseMenu::Text, BindProtocol);
    // new EIChangeAttribute::MenuAttribute("Move: ", EIChangeBaseMenu::CheckandInput, Actions, "00 00 00 00");
    // new EIChangeAttribute::MenuAttribute("Release: ", EIChangeBaseMenu::CheckandInput, Actions, "00 00 00 00");
    // new EIChangeAttribute::MenuAttribute("Edited: ", EIChangeBaseMenu::CheckandInput, Actions, "00 00 00 00");
    Attribute->RightMenuText.append(BindProtocol);

    EIChangeAttribute::MenuAttribute* Actions = new EIChangeAttribute::MenuAttribute("Actions");
    new EIChangeAttribute::MenuAttribute("Reset", EIChangeBaseMenu::Text, Actions);
    new EIChangeAttribute::MenuAttribute("Move: ", EIChangeBaseMenu::CheckandInput, Actions, "00 00 00 00");
    new EIChangeAttribute::MenuAttribute("Release: ", EIChangeBaseMenu::CheckandInput, Actions, "00 00 00 00");
    new EIChangeAttribute::MenuAttribute("Edited: ", EIChangeBaseMenu::CheckandInput, Actions, "00 00 00 00");
    Attribute->RightMenuText.append(Actions);

    EIChangeAttribute::MenuAttribute* Settings = new EIChangeAttribute::MenuAttribute("Settings");
    new EIChangeAttribute::MenuAttribute("Reset", EIChangeBaseMenu::Text, Settings);
    new EIChangeAttribute::MenuAttribute("Max: ", EIChangeBaseMenu::Input, Settings, "1000");
    new EIChangeAttribute::MenuAttribute("Min: ", EIChangeBaseMenu::Input, Settings, "0");
    new EIChangeAttribute::MenuAttribute("Step: ", EIChangeBaseMenu::Input, Settings, "1");
    Attribute->RightMenuText.append(Settings);

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
        QList<QAction*> ActionList;
        ActionList.append(Action);

        EIChangeBaseMenu *RootMenu = qobject_cast<EIChangeBaseMenu*>(Action->parent());
        while(RootMenu)
        {
            QString LastTitle = RootMenu->title();
            QAction *AssociatedAction = RootMenu->menuAction();
            ActionList.append(AssociatedAction);
            RootMenu = qobject_cast<EIChangeBaseMenu*>(AssociatedAction->parent());
            if(LastTitle == RootMenu->title())
                break;
        }

        // for (QAction *action : ActionList) {
        //     if (action) {
        //         qDebug() << action->text(); // 输出 QAction 的文本
        //     }
        // }
        if(ActionList[ActionList.size() - 2]->text() == Attribute->RightMenuText[0]->Name)
        {
            this->deleteLater();
            return;
        }
        else if (ActionList[ActionList.size() - 2]->text() == Attribute->RightMenuText[1]->Name)
        {
            if(ActionList[ActionList.size() - 3]->text() == Attribute->RightMenuText[1]->Child[0]->Name)
            {
                EIChangeBaseMenu *ChildMenu = qobject_cast<EIChangeBaseMenu*>(ActionList[ActionList.size() - 3]->parent());
                ActionList[ActionList.size() - 3]->setProperty("PressCheck", true);
                emit ChildMenu->CheckInterLocked();
            }
            else if(ActionList[ActionList.size() - 3]->text() == Attribute->RightMenuText[1]->Child[1]->Name)
            {
                EIChangeBaseMenu *ChildMenu = qobject_cast<EIChangeBaseMenu*>(ActionList[ActionList.size() - 3]->parent());
                ActionList[ActionList.size() - 3]->setProperty("PressCheck", true);
                emit ChildMenu->CheckInterLocked();
            }
        }

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

