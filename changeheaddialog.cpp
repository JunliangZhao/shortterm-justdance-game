#include "changeheaddialog.h"
#include "ui_changeheaddialog.h"
#include<QLabel>
#include<QPushButton>
#include<QPalette>

changeHeadDialog::changeHeadDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changeHeadDialog)
{
    ui->setupUi(this);

    this->setGeometry(390,50,1200,900);
    QPalette pal = this->palette();
    pal.setColor(QPalette::Window,QColor(255,220,234));
    this->setPalette(pal);


    leftbutton = new QPushButton(this);
    leftbutton->setStyleSheet(
                "border: 2px solid #8f8f91;"
                "border-radius:10px;"
                "font-family:'Magneto';"
                "color:rgb(255,140,140);"
                );
    leftbutton->setGeometry(50,350,50,200);
    leftbutton->setText("上一张");
    rightbutton = new QPushButton(this);
    rightbutton->setStyleSheet(
                "border: 2px solid #8f8f91;"
                "border-radius:10px;"
                "font-family:'Magneto';"
                "color:rgb(255,140,140);"
                );
    rightbutton->setGeometry(1100,350,50,200);
    rightbutton->setText("下一张");
    bottombutton = new QPushButton(this);
    bottombutton->setStyleSheet(
                "border: 2px solid #8f8f91;"
                "border-radius:10px;"
                "font-family:'Magneto';"
                "color:rgb(255,140,140);"
                );
    bottombutton->setGeometry(400,800,400,50);
    bottombutton->setText("确定");



    this->show();
}

changeHeadDialog::~changeHeadDialog()
{
    delete ui;
}
