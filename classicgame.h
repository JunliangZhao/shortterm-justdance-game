#ifndef CLASSICGAME_H
#define CLASSICGAME_H

#include <QMainWindow>
//#include <playinterface2.h>
namespace Ui {
class classicgame;
}

class classicgame : public QMainWindow
{
    Q_OBJECT

public:
    explicit classicgame(QWidget *parent = 0);
    ~classicgame();
public slots:
    void ClickButton();
    void ClickButton2();
    void ClickButton4();
    void ClickButton3();
private:
    Ui::classicgame *ui;
};

#endif // CLASSICGAME_H
