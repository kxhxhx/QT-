#ifndef EICHANGELINEEDIT_H
#define EICHANGELINEEDIT_H

#include <QApplication>
#include <QLineEdit>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QKeyEvent>
#include <QDebug>


class EIChangeLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    EIChangeLineEdit(QWidget *Parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // EICHANGELINEEDIT_H
