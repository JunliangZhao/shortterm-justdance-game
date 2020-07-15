#include "keeptime.h"
#include<QTimer>
#include<QObject>

keeptime::keeptime()
{
    ;
}


void keeptime::timestart()
{

    extern int timenumber;
    extern int signalflag;
    extern link();
    extern link2();
    if(timenumber == 1)
    {
        QTimer* timer = new QTimer();
        QObject::connect(timer,&QTimer::timeout,&link);
        QObject::connect(timer,&QTimer::timeout,timer,&QTimer::stop);
        QObject::connect(timer,&QTimer::timeout,&link2);
        timer->start(3000);
        signalflag = 0;
        timenumber = 0;
    }
    else
    {
        ;
    }
}
