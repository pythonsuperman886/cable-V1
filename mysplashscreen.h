//
// Created by explore on 2021/8/23.
//

#ifndef CABLE_V1_MYSPLASHSCREEN_H
#define CABLE_V1_MYSPLASHSCREEN_H
#include <QSplashScreen>
#include <QPixmap>
#include <QProgressBar>
#include <QList>
#include <QtGlobal>
#include <QTime>
#include <QTimer>
#include "common.h"
class MySplashScreen:public QSplashScreen {
    Q_OBJECT
public:
    MySplashScreen(QPixmap &pixmap,int time);
    ~MySplashScreen();

private:
    void set_progeress();
    void generate_randon_number();
    int num = 0;


    QProgressBar * progress_bar;
    QList<int> number_list;
    double elapse_time;

private slots:
    void slot_update_progress();
};


#endif //CABLE_V1_MYSPLASHSCREEN_H
