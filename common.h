//
// Created by explore on 2021/8/21.
//

#ifndef CABLE_V1_COMMON_H
#define CABLE_V1_COMMON_H
#undef slots
#include <torch/torch.h>
#define slots Q_SLOTS
//#endif
#include <QCoreApplication>
#include <torch/script.h>
#include <torch/torch.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>
#include <vector>
#include <map>
#include <QImage>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>
#include <vector>
#include <map>
#include "QString"
#include "QThread"
#include "QStringList"
#include "QProcess"
#include <iostream>
#include <QDebug>
#include "MvCameraControl.h"
#include <QImage>
#include <cstring>
#include <iostream>
#include <QtCharts>
#include <QTableView>
#include <QStandardItemModel>
using namespace cv;
using namespace std;
using at::Tensor;
using at::Device;
QImage Mat2QImage( const cv::Mat& InputMat);
at::Tensor Mat2Tensor(Mat camera_frame);
at::Tensor denorm(const torch::Tensor& tensor);
Mat Tensor2Mat(const at::Tensor& tensor);
vector<int> min_edge_out(const Mat& image);
vector<int> Max_deal_pic(const Mat& image);
vector<int> get_diameter_nums(const Mat& image);
void draw_line_diameter(Mat &image, vector<int> nums);
typedef struct mytime{
    int hour=0;
    int minu=0;
    int sec =0;
    bool Is_start = false;
    void init(){
        hour=0;
        minu=0;
        sec =0;
        Is_start = false;
    }

} My_Time;

typedef struct my_loss_info{
    int epoch;
    double g_loss;
    double d_loss;
}My_LOSS;
typedef struct mychart{
    QChart *line_chart;
    QLineSeries *series_g;
    QLineSeries *series_d;
    QValueAxis *axisX;
    QValueAxis *axisY;
    QList<QPointF> point_g;
    QList<QPointF> point_d;

    mychart(){}
    void init( QChartView *graphicsView_train_loss){
        line_chart = new QChart();
        line_chart->setTheme(QChart::ChartThemeDark);
        line_chart->setTitle("Net loss");
        series_g = new QLineSeries(line_chart);
        series_d = new QLineSeries(line_chart);

        line_chart->addSeries(series_g);
        line_chart->addSeries(series_d);

        series_g->setName(QString("g loss"));
        series_d->setName(QString("d loss"));
        series_g->setUseOpenGL(true);
        series_d->setUseOpenGL(true);

        graphicsView_train_loss->setRubberBand(QChartView::HorizontalRubberBand);
        graphicsView_train_loss->setRenderHint(QPainter::Antialiasing);
        line_chart->createDefaultAxes();
        axisX = new QValueAxis;
        axisY = new QValueAxis;
        axisX->setRange(0,20);
        axisX->setTitleText("epoch");
        axisY->setRange(0,10);
        axisY->setTitleText("loss");

        //    axisX->setTickCount(100);
        axisY->setTickCount(20);
        axisX->setTickCount(20);
        //    line_chart->addAxis(axisX,Qt::AlignBottom);

        //    series_defect->append(QPointF(1,100));
        //    series_defect->append(QPointF(2,200));
        //    series_defect->append(QPointF(3,300));
        //    series_defect->append(QPointF(4,400));
        line_chart->setAxisY(axisY,series_g);
        line_chart->setAxisY(axisY,series_d);
        line_chart->setAxisX(axisX,series_g);
        line_chart->setAxisX(axisX,series_d);
        line_chart->legend()->hide();
        graphicsView_train_loss->setChart(line_chart);


        line_chart->setAnimationOptions(QChart::SeriesAnimations);
        line_chart->legend()->setVisible(true);
        point_g.append(QPointF(0,0));
        point_d.append(QPointF(0,0));

    }


    void add_loss_info(My_LOSS loss_info) {


        line_chart->removeSeries(series_g);
        line_chart->removeSeries(series_d);

//        model->insertRow(model_count++,list);
        if(loss_info.epoch>20){
            axisX->setRange(loss_info.epoch-10,loss_info.epoch+10);
            point_g.pop_front();
            point_d.pop_front();
        }
//        cout<<"point"<<endl;
//        cout<<"point : "<<point_g[point_g.size()-1].x()<<endl;
        if(loss_info.epoch!=point_g[point_g.size()-1].x()){
            point_g.append(QPointF(loss_info.epoch,loss_info.g_loss));
            point_d.append(QPointF(loss_info.epoch,loss_info.d_loss));
        }else{
            point_g.pop_back();
            point_d.pop_back();
            point_g.push_back(QPointF(loss_info.epoch,loss_info.g_loss));
            point_d.push_back(QPointF(loss_info.epoch,loss_info.d_loss));

        }


        series_g->replace(point_g);
        series_d->replace(point_d);

        line_chart->addSeries(series_g);
        line_chart->addSeries(series_d);

        line_chart->setAxisY(axisY,series_g);
        line_chart->setAxisY(axisY,series_d);
        line_chart->setAxisX(axisX,series_g);
        line_chart->setAxisX(axisX,series_d);


    }
} Train_loss_chart;



typedef struct my_pie_chart{

    QPieSeries *series;
    								//每个分区label显示
    QChart *pie_chart;





    my_pie_chart(){

    }

    void init(QChartView *graphicsView_pie_chart){
        series = new QPieSeries();
        series->append("合格", 0.8)->setColor(QColor(0, 200, 200));	// 构造两个饼状分区
        series->append("不合格", 0.2)->setColor(QColor(200, 150, 0));//设置每个分区的占比与颜色
        series->setLabelsVisible();									//每个分区label显示
        pie_chart = new QChart();
        pie_chart->addSeries(series);
        pie_chart->setTitle("Defect%");
        pie_chart->legend()->hide();									//是否显示图例
        pie_chart->setAnimationOptions(QChart::AllAnimations); // 设置显示时的动画效果
        pie_chart->setTheme(QChart::ChartThemeBlueIcy);
        series->setUseOpenGL(true);

//        QChartView *chartView;										//构造图表视图
//        chartView = new QChartView(pie_chart);
        graphicsView_pie_chart->setChart(pie_chart);

        graphicsView_pie_chart->setRenderHint(QPainter::Antialiasing); //抗锯齿处理
        //chartView->chart()->setTheme(QChart::ChartThemeBlueCerulean);

    }

    void add_pie_info(double good,double bad) {
        pie_chart->removeSeries(series);

        series->clear();

        series->append("合格", good)->setColor(QColor(0, 200, 0));	// 构造两个饼状分区
        series->append("不合格", bad)->setColor(QColor(200, 0, 0));//设置每个分区的占比与颜色

        pie_chart->addSeries(series);
    }

}My_test_pie_chart;
#endif //CABLE_V1_COMMON_H
