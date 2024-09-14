#include "eichangelineedit.h"

EIChangeLineEdit::EIChangeLineEdit(QWidget *Parent)
    :QLineEdit(Parent)
{
    QRegularExpression regex("[A-Za-z0-9 ]*");
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(regex, this);
    this->setValidator(validator);
}

void EIChangeLineEdit::keyPressEvent(QKeyEvent *event)
{
    QLineEdit::keyPressEvent(event);
}

