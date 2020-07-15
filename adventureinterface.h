#ifndef ADVENTUREINTERFACE_H
#define ADVENTUREINTERFACE_H

#include <QMainWindow>
#include<QPushButton>


class adventureInterface : public QMainWindow
{
    Q_OBJECT
public:
    explicit adventureInterface(QWidget *parent = nullptr);
    QPushButton* button1;
    QPushButton* button2;


signals:

public slots:
};

#endif // ADVENTUREINTERFACE_H
