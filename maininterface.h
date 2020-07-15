#ifndef MAININTERFACE_H
#define MAININTERFACE_H

#include <QMainWindow>
#include<QPushButton>
#include<adventureinterface.h>
#include<classicinterface.h>
#include<QTimer>
class mainInterface : public QMainWindow
{
    Q_OBJECT
public:
    QPushButton* button1;
    QPushButton* button2;
    QPushButton* returnbutton;
    classicInterface* face1;
    adventureInterface* face2;
   int open;
    QTimer *maketime;

    explicit mainInterface(QWidget *parent = nullptr);
    ~mainInterface();

signals:

private slots:
    void make();
};

#endif // MAININTERFACE_H
