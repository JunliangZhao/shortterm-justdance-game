#ifndef SONGS_H
#define SONGS_H

#include<QLabel>
#include<QObject>
#include<QSoundEffect>
#include<QFont>

class songs:public QObject
{
    Q_OBJECT

public:
    explicit songs(QWidget *parent = 0);
    QLabel *song[6];

    QString centersong();  //中心歌曲（当前选中的歌曲）
    int t=4;
    int x,y,w=140,h=140,d=260;

    QFont font1=QFont("方正苏新诗柳楷简体",20);

    QSoundEffect *qiehuan;

signals:
    void sendcentersong(QString);

public slots:
    void leftSelect();
    void rightSelect();


};

#endif // SONGS_H
