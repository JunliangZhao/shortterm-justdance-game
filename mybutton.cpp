#include "mybutton.h"

MyButton::MyButton(QWidget *parent) :
    QPushButton(parent)
{


    connect(this,SIGNAL(pressed()),this,SLOT(cursorchange1()));
    connect(this,SIGNAL(released()),this,SLOT(cursorchange2()));
}

void MyButton::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    this->setCursor(QCursor(Qt::OpenHandCursor));

}

void MyButton::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    this->setCursor(QCursor(Qt::ArrowCursor));
}

void MyButton::cursorchange1()
{

    this->setCursor(QCursor(Qt::ClosedHandCursor));
}

void MyButton::cursorchange2()
{
    this->setCursor(QCursor(Qt::OpenHandCursor));
}

