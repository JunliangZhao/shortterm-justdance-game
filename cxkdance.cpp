//#include "cxkdance.h"
//#include "ui_cxkdance.h"
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/core/core.hpp>
//#include<opencv/highgui.h>
//#include <string>
//#include<QLabel>
//#include<QTimer>
//#include<QImage>
//#include<QDebug>
//#include<QPixmap>
//#include<QVector>
//#include<QMovie>
//#include<fstream>
//#include<QFont>
//#include<QDesktopWidget>
//#include<iostream>
//using namespace std;
//using namespace cv;

//extern  VideoCapture cap;
//     Mat cxkImg;
//    string gifname[NUM];
//    string jpgname[NUM+1];
//    string pngname[NUM+1];
//    double a0[3]={1,1,1};

//    int flashnum=0;
//    int moveloca=0;

//    int score=0;


//   int deal1=0;
//   int deal2=1;



//   int num1=0;

//   int shuju=0;

//  int location[13]={-2230,-80,90,-550,120,-480,100,-440,-270,-190};

//   Mat  Hsv_dete(Mat src)
//   {
//       Mat hsv_image;

//       int h = 0;
//       int s = 1;
//       int v = 2;
//       int a = 0;
//       int b = 20;
//       int c = 48;
//       int d =50;
//       cvtColor(src, hsv_image, CV_BGR2HSV);
//       Mat output_mask = Mat::zeros(src.size(), CV_8UC1);

//       for (int i = 0; i < src.rows; i++)
//       {
//           for (int j = 0; j < src.cols; j++)
//           {
//               uchar *p_mask = output_mask.ptr<uchar>(i, j);
//               uchar *p_src = hsv_image.ptr<uchar>(i, j);
//               if (p_src[h] >= a && p_src[h] <= b && p_src[s] >= c && p_src[v] >= d)
//               {


//                   src.at<Vec3b>(i, j)[0] = 0;
//                   src.at<Vec3b>(i, j)[1] = 0;
//                   src.at<Vec3b>(i, j)[2] = 0;

//                   p_mask[0] = 1;
//               }
//               else p_mask[0] = 0;
//           }
//       }

//       int recor1=1000;
//       int recor2=0;

//       for (int i = 0; i < src.rows; i++)
//       {
//           for (int j = 0; j < src.cols; j++)
//           {
//               uchar *p_src = hsv_image.ptr<uchar>(i, j);
//               if (p_src[h] >= a && p_src[h] <= b && p_src[s] >= c && p_src[v] >= d)
//               {
//                   if (j < recor1)
//                   {
//                       recor1 = j;
//                   }

//               }

//           }
//       }

//       for (int i = 0; i < src.rows; i++)
//       {
//           for (int j = src.cols-1;j>=0; j--)
//           {
//               uchar *p_src = hsv_image.ptr<uchar>(i, j);
//               if (p_src[h] >= a && p_src[h] <= b && p_src[s] >= c && p_src[v] >= d)
//               {
//                   if (j > recor2)
//                   {
//                       recor2 = j;
//                   }


//               }

//           }
//       }


//       for (int i = 0; i < src.rows; i++)
//       {
//           for (int j = recor1;j<recor2; j++)
//           {
//               uchar *p_mask = output_mask.ptr<uchar>(i, j);
//               p_mask[0] = 1;
//           }
//       }
//       for (int i = 0; i < 60; i++)
//       {
//           for (int j = 0; j < src.cols; j++)
//           {
//               uchar *p_mask = output_mask.ptr<uchar>(i, j);
//               p_mask[0] = 0;
//           }
//       }
//       for (int i = src.rows - 1; i > src.rows - 75; i--)
//       {
//           for (int j = 0; j < src.cols; j++)
//           {
//               uchar *p_mask = output_mask.ptr<uchar>(i, j);
//               p_mask[0] = 0;
//           }
//       }
//       Mat dete(src.size(), CV_8UC3, Scalar(255,255,255));
//       src.copyTo(dete, output_mask);


//       return dete;
//   }
//   void judge(Mat  templateImg)
//   {

//       cap.read(cxkImg);
//       cxkImg=Hsv_dete(cxkImg);


//       cvtColor(cxkImg,cxkImg, CV_BGR2GRAY);
//       medianBlur(cxkImg, cxkImg, 5);
//       //Canny
//       bitwise_not(cxkImg, cxkImg);
//       threshold(cxkImg, cxkImg, 150, 255,CV_THRESH_BINARY);
//       vector<vector<Point>> contours1;
//       findContours(cxkImg, contours1, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
//       for (auto it = contours1.begin(); it != contours1.end();)
//       {
//           if (contourArea(*it) < 300.0)
//           {

//               it = contours1.erase(it);
//           }
//           else
//           {

//               it++;
//           }
//       }
//       //drawContours(copyImg1, contours1, -1, Scalar(0, 255, 0), 2, 8);

//       cv::resize(templateImg, templateImg,Size(),0.2,0.2);
//      // Mat copyImg2 = templateImg.clone();
//       cvtColor(templateImg, templateImg, CV_BGR2GRAY);
//       threshold(templateImg, templateImg, 100, 255, CV_THRESH_BINARY);

//       vector<vector<Point>> contours2;
//       findContours(templateImg, contours2, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
//       //drawContours(copyImg2, contours2, -1, Scalar(0, 255, 0), 2, 8);


//      double a2=1.0;
//       double a1 = 1.0;
//       for (unsigned int i = 0; i < contours1.size(); i++)
//       {
//           a1 = matchShapes(contours1[i], contours2[0], CV_CONTOURS_MATCH_I1, 0.0);
//           if (a1 <a2)
//           {
//               a2 = a1;
//           }


//       }

//        a0[2]=a0[1];
//        a0[1]=a0[0];
//       a0[0]=a2;
//       shuju++;


//      // cout << "simalar" << a2<<endl;


//   }

//cxkdance::cxkdance(QWidget *parent) :
//    QMainWindow(parent),
//    ui(new Ui::cxkdance)
//{
//    ui->setupUi(this);

// QRect rec = QApplication::desktop()->screenGeometry();
//   this->setFixedSize(rec.width(),rec.height());
//     setWindowFlags (Qt::FramelessWindowHint);



//    fstream file;
//    file.open("../justswing/cxk/path.txt",ios::in);


//   for(int i=0;i<NUM;i++)
//   {
//       getline(file,gifname[i]);

//   }
//   file.close();
//   file.open("../justswing/cxk/picpath.txt",ios::in);

//   for(int i=0;i<NUM+1;i++)
//   {
//       getline(file,jpgname[i]);

//   }
//   file.close();
//   file.open("../justswing/cxk/Tpicpath.txt",ios::in);

//   for(int i=0;i<NUM+1;i++)
//   {
//       getline(file,pngname[i]);

//   }
//   file.close();



//   temp=new QLabel(this);


//   QLinearGradient linearGrad(QPointF(0,120), QPointF(500,200));
//   linearGrad.setColorAt(0, Qt::red);
//   linearGrad.setColorAt(0.5, Qt::yellow);
//   linearGrad.setColorAt(1, Qt::green);

//   QBrush brush(linearGrad);
//   QPalette palette;
//   palette.setBrush(QPalette::WindowText, brush);




//       temp->setFont(QFont("方正苏新诗柳楷简体",20));
//      temp->setGeometry(0,this->height()/2,300,200);
//      temp->setPalette(palette);
//      temp->setText("CXKNB");
//      temptime=new QTimer(this);
//      connect(temptime,SIGNAL(timeout()),temp,SLOT(clear()));
//      connect(temptime,SIGNAL(timeout()),temptime,SLOT(stop()));
//      temptime->start(500);






//   flashlabel=new QLabel(this);
//   flashlabel->setGeometry(this->width()/3+400,this->height()/3+400,250,100);
//   QPixmap temppix;

//   temppix.load("C:\\Users\\zjl\\Desktop\\24k demo resource\\flash.png");
//   flashlabel->setPixmap(temppix.scaled(200,80));








//   movelabel=new QLabel(this);
//   QPixmap movepix;
//      movelabel->setGeometry(this->width(),this->height()/3+300,120,200);
//   movepix.load(QString::fromStdString(pngname[0]));
//    movelabel->setPixmap(movepix.scaled(movelabel->size()));
//   movelabel->raise();
//   movelabel->show();
//   moveloca=location[num];





//   bklabel=new QLabel(this);
//   bklabel->setGeometry(this->width()/4,-50,this->width()/2,this->height()/3*2);
//   movie=new QMovie(QString::fromStdString(gifname[0]));
//   movie->setScaledSize(bklabel->size());
//   bklabel->setMovie(movie);

//   bklabel->show();
//    connect(movie,SIGNAL(finished()),this,SLOT(change()));
//    movie->start();



//   QTimer *flashtime=new QTimer(this);
//   connect(flashtime,SIGNAL(timeout()),this,SLOT(flash()));
//   flashtime->start(400);
//   QTimer *movetime=new QTimer(this);
//   connect(movetime,SIGNAL(timeout()),this,SLOT(labelmove()));
//   movetime->start(30);
//   QTimer *goaltime=new QTimer(this);
//   connect(goaltime,SIGNAL(timeout()),this,SLOT(goal()));
//   goaltime->start(30);

//}

//cxkdance::~cxkdance()
//{
//    delete ui;
//}
//void cxkdance::change()
//{
//    if(num<NUM)
//    {

//    num++;
//    movie->setFileName(QString::fromStdString(gifname[num]));
//    bklabel->setMovie(movie);

//    movie->start();
//    cout<<moveloca<<endl;

//    moveloca=location[num];
//    QPixmap movepix;
//    movepix.load(QString::fromStdString(pngname[num]));
//     movelabel->setPixmap(movepix.scaled(movelabel->size()));
//     if(deal1)
//     {
//         temp->setText("Chree on");


//         score=0;

//     }
//     deal1=0;
//     deal2=1;
//     shuju=0;



//    }
//    else
//    {
//        this->close();
//    }




//}

//void cxkdance::flash()
//{
//    if(flashnum%2==0)
//    {
//        flashlabel->raise();



//         flashlabel->show();
//    }
//    else
//    {
//        flashlabel->hide();
//     }


//    flashnum++;


//}

//void cxkdance::labelmove()
//{

//    movelabel->setGeometry(this->width()-moveloca,this->height()/3+300,120,200);

//     movelabel->raise();
//     movelabel->show();


//     if(moveloca>=700 &&deal2)
//     {

//         deal1=1;
//         deal2=0;
//         cout<<"work"<<endl;

//     }






//      moveloca+=10;

//    // cout<<moveloca<<endl;


//}
//void cxkdance::goal()
//{

//    if(deal1)
//    {
//        Mat img;
//        img=imread(jpgname[num]);
//        judge(img);


//    }



//    if(a0[2]-a0[1]>0.4 && a0[1]-a0[0]<0.1 && deal1 &&shuju>=4)
//    {

//        score=4;
//    }
//    else if(a0[2]-a0[1]>0.3 && a0[1]-a0[0]<0.1 && deal1 && shuju>=4)
//    {

//        score=3;
//    }
//    else if(a0[2]-a0[1]>0.2 && a0[1]-a0[0]<0.1 && deal1 && shuju>=4)
//    {

//        score=2;
//    }
//    else if(a0[2]-a0[1]>0.1 && a0[1]-a0[0]<0.1 && deal1 && shuju>=4)
//    {

//        score=1;
//    }
//    else
//    {
//        score=0;
//    }
//    if(score==4 && deal1)
//   {
//       shuju=0;
//          score=-1;


//        deal1=0;

//        temp->setText("Perfect");








//    }
//    else if(score==3 && deal1)
//    {
//         shuju=0;
//           score=0;

//        deal1=0;
//        temp->setText("Great");





//    }
//    else if(score==2 && deal1)
//    {
//      shuju=0;
//           score=0;

//        deal1=0;
//        temp->setText("Good");








//      }
//    else if(score==1 && deal1)
//    {
//        shuju=0;
//           score=0;

//        deal1=0;
//        temp->setText("Pass");





//      }

//else
//    {

//    }

//}


