//
// Created by explore on 2021/8/23.
//

#include "mysplashscreen.h"
MySplashScreen::MySplashScreen(QPixmap & pixmap,int time):
        QSplashScreen(pixmap),
        elapse_time(time){
    progress_bar = new QProgressBar(this);
//    progress_bar->move(100,60);
    progress_bar->setOrientation(Qt::Horizontal);  // 水平方向
    progress_bar->setGeometry(0,pixmap.height()-50,pixmap.width(),30);
//    progress_bar->setStyleSheet("QProgressBar{color:black;font:30px;text-align:center;}QProgressBar::chunk{background-color:rgb(0,255,200);}");
    QFont font;
    font.setPointSize(20);
    progress_bar->setFont(font);
    progress_bar->setRange(0,100);
    progress_bar->setValue(0);
//    generate_randon_number();
    set_progeress();
};

void MySplashScreen::set_progeress(){
    double temp_time = elapse_time/10;
    for(int i = 0;i<10;i++){
        number_list.append(i*temp_time);
        QTimer::singleShot(temp_time+i,this,SLOT(slot_update_progress()));
//        progress_bar->setValue(i);
        cout<<"shot: "<<i*temp_time<<endl;

    }
    cout<<"close"<<endl;
    QTimer::singleShot(elapse_time,this,SLOT(close()));
}

void MySplashScreen::generate_randon_number(){
//    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    for(int i=0;i<10;i++){
        number_list.append(qrand()%101);
    }
    qSort(number_list.begin(),number_list.end());
}
void MySplashScreen::slot_update_progress(){
    progress_bar->setValue(number_list[num]);
    cout<<number_list[num]<<endl;
    num+=1;
//    QSplashScreen::repaint();
};

MySplashScreen::~MySplashScreen(){

};

