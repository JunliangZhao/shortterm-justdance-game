#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>

class MyButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyButton(QWidget *parent = 0);

protected:
    void enterEvent(QEvent * event);
    void leaveEvent(QEvent * event);

 private slots:
    void cursorchange1();
    void cursorchange2();
};

#endif // MYBUTTON_H
