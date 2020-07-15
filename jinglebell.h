#ifndef JINGLEBELL_H
#define JINGLEBELL_H
#include <QMainWindow>
#include<QLabel>
#include<QMovie>
#include<string>
#define jingelbellNUM 22
using namespace std;
namespace Ui {
class jinglebell;
}

class  jinglebell: public QMainWindow
{
    Q_OBJECT

public:
    explicit jinglebell(QWidget *parent = 0);
    ~jinglebell();
    QLabel *bklabel;
    QMovie *movie;
    QLabel *flashlabel;
    QLabel *movelabel;
    QLabel *temp;
    QTimer *temptime;
    string gifname[jingelbellNUM];
    string jpgname[jingelbellNUM+1];
    string pngname[jingelbellNUM+1];



private:
    Ui::jinglebell *ui;
private slots:
    void change();
    void  flash();
    void labelmove();
   void goal();
};

#endif // CXKDANCE_H
