#include "songs.h"
#include<QString>

songs::songs(QWidget *parent):
    QObject(parent)
{


    x=(parent->width()-w/2)-2*d;
    y=parent->height()/3;

    qiehuan=new QSoundEffect(this);
    qiehuan->setSource(QUrl::fromLocalFile(":/切换.wav"));

    for(int i=0;i<6;i++)
    {
        if(i==0)
            song[i]=new QLabel("STW",parent);
        else if(i==1)
            song[i]=new QLabel("Rise",parent);
        else if(i==2)
            song[i]=new QLabel("JingelBells",parent);
        else if(i==3)
            song[i]=new QLabel("24K",parent);
        else if(i==4)
            song[i]=new QLabel("鸡你太美",parent);
        else
            song[i]=new QLabel("暂无歌曲",parent);
        song[i]->setGeometry(x+(i-3)*d,y,w,h);
        song[i]->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        song[i]->setFrameShape (QFrame::Box);
        song[i]->setStyleSheet("border: 5px solid  #ff0000");
        song[i]->setFont(font1);

        QPalette p=song[i]->palette();
        p.setColor(QPalette::WindowText,Qt::white);
        song[i]->setPalette(p);

        if(i<t-2||i>t)
        {
            song[i]->hide();
        }
    }

}

QString songs::centersong()
{
    for(int i=0;i<6;i++)
    {
        if(song[i]->geometry().x()==x+d)
        {
            return song[i-1]->text();
        }

    }
    return " ";


}

void songs::leftSelect()
{
    qiehuan->play();
    if(t==2)
    {
        t--;
        for(int j=0;j<2;j++)
        {
            song[j]->setGeometry(x+(j)*d,y,w,h);
        }
        song[2]->hide();
    }
    else if(t==1)
    {
    }
    else
    {
        t--;

        //显示所有歌曲
        int i=0;
        for(;i<6;i++)
        {
            song[i]->show();
        }

        //将范围外的歌曲隐藏
        for(i=0;i<t-2;i++)
        {
            song[i]->hide();
        }

        //调整歌曲位置整体左移
        int j=0;
        for(;i<=t;i++,j++)
        {
            song[i]->setGeometry(x+(j-1)*d,y,w,h);
        }

        //将范围外的歌曲隐藏
        for(;i<6;i++)
        {
            song[i]->hide();
        }



    }
    //发射信号传出中心歌曲（选中歌曲）
    emit sendcentersong(song[t-1]->text());

}

void songs::rightSelect()
{

    qiehuan->play();
    if(t==5)
    {
        t++;
        int j=4;
        for(;j<6;j++)
        {
            song[j]->setGeometry(x+(j-5)*d,y,w,h);
        }
        song[3]->hide();
    }
    else if(t==6)
    {}
    else
    {
        t++;

        //显示所有歌曲
        int i=0;
        for(;i<6;i++)
        {
            song[i]->show();
        }

        //将整体歌曲位置右移
        for(i=0;i<t-2;i++)
        {
            song[i]->hide();
        }
        int j=0;
        for(;i<=t;i++,j++)
        {
            song[i]->setGeometry(x+(j-1)*d,y,w,h);
        }

        //隐藏范围外歌曲
        for(;i<6;i++)
        {
            song[i]->hide();
        }

    }
    //发射信号传出中心歌曲（选中歌曲）
    emit sendcentersong(song[t-1]->text());
}
