#ifndef PLAYINTERFACE2_H
#define PLAYINTERFACE2_H
#include <QMainWindow>
#include <QLabel>
#include <QTimer>
#include <opencv2/highgui/highgui.hpp>
#include<iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <QSoundEffect>
#include <QPixmap>
using namespace std;
using namespace cv;
//QLabel *labelpig = new QLabel();
namespace Ui {
class playinterface2;
}

class playinterface2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit playinterface2(QWidget *parent = 0);
    ~playinterface2();
    QSoundEffect *s=new QSoundEffect(this);
    QSoundEffect *login=new QSoundEffect(this);

public slots:
    void slotTimeout();
    void slotTimeout2();
    void slotTimeout3();
    void slotTimeout4();
    void slotTimeout5();
    void slotTimeoutscore();
    void yundong();
private:
    Ui::playinterface2 *ui;
    QLabel *labelpig = new QLabel();
    QPixmap pl;
    QPixmap pr;
    int score=1500;
    int life=0;
    int t=0;
    QTimer *timer2 = new QTimer(this);
    QLabel *labelshock = new QLabel(this);
    QPixmap *pshock = new QPixmap;
    QLabel *labelright = new QLabel(this);
    QPixmap *pright = new QPixmap();
    int s1=0;
    int s2=0;
    int s3=0;
    int s4=0;
    int s5=0;
};

#endif // PLAYINTERFACE2_H
