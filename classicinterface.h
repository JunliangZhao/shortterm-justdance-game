#ifndef CLASSICINTERFACE_H
#define CLASSICINTERFACE_H

#include <QMainWindow>
#include<QPushButton>

class classicInterface : public QMainWindow
{
    Q_OBJECT
public:
    explicit classicInterface(QWidget *parent = nullptr);
    QPushButton* button1;
    QPushButton* button2;

signals:

public slots:
};

#endif // CLASSICINTERFACE_H
