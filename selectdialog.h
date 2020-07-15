#ifndef SELECTDIALOG_H
#define SELECTDIALOG_H

#include <QDialog>
#include<QSoundEffect>
#include"mybutton.h"
#include<QFont>

namespace Ui {
class selectDialog;
}

class selectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit selectDialog(QWidget *parent = 0);
    ~selectDialog();
    QString *selectedSong;

    MyButton *OKBtn,*cancelBtn,*leftBtn,*rightBtn;
    QFont font2=QFont("方正苏新诗柳楷简体",20);
    void setBackgroundImage(QString path);
    QSoundEffect *select;


signals:
    void sendSongName(QString);

private slots:

    void reccentersong(QString);

    void emitsong();

    void quxiao();

private:
    Ui::selectDialog *ui;
};

#endif // SELECTDIALOG_H
