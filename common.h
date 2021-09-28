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
vector<int> min_edge_out(const Mat& image,int threshold);
vector<int> Max_deal_pic(const Mat& image,int threshold);
vector<int> get_diameter_nums(const Mat& image,int threshold);
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
        axisX->setRange(0,200);
        axisX->setTitleText("epoch");
        axisY->setRange(0,10);
        axisY->setTitleText("loss");

        //    axisX->setTickCount(100);
        axisY->setTickCount(10);
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
        line_chart->setAnimationOptions(QChart::SeriesAnimations);
        line_chart->legend()->setVisible(true);
        graphicsView_train_loss->setChart(line_chart);



        line_chart->legend()->setAlignment(Qt::AlignTop);

        point_g.append(QPointF(0,0));
        point_d.append(QPointF(0,0));

    }


    void add_loss_info(My_LOSS loss_info) {


        line_chart->removeSeries(series_g);
        line_chart->removeSeries(series_d);

//        model->insertRow(model_count++,list);
        if(loss_info.epoch>500){
            axisX->setRange(loss_info.epoch-20,loss_info.epoch+5);
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

    QChartView *graphicsView_test_pie_chart;
    QPieSlice *slice;

    double sum=0;
    double good_percent=0;
    double bad_percent=0;

    my_pie_chart(){

    }

    void init(QChartView *graphicsView_pie_chart){
        series = new QPieSeries();
        series->append("合格", 0.1)->setColor(QColor(0, 200, 0));	// 构造两个饼状分区
        series->append("不合格", 0.0)->setColor(QColor(200, 0, 0));//设置每个分区的占比与颜色
        series->setLabelsVisible();
        series->setHoleSize(0.25);//每个分区label显示
        pie_chart = new QChart();
        pie_chart->addSeries(series);
        pie_chart->setTitle("Defect Pie");
        pie_chart->legend()->setAlignment(Qt::AlignBottom);
        series->setPieSize(0.5);
        //是否显示图例
//        pie_chart->setAnimationOptions(QChart::AllAnimations); // 设置显示时的动画效果
        pie_chart->setTheme(QChart::ChartThemeBlueCerulean);
        series->setUseOpenGL(true);
//        series->setLabelsVisible();
//        chart->legend()->hide();
//        QChartView *chartView;										//构造图表视图
//        chartView = new QChartView(pie_chart);
        graphicsView_pie_chart->setChart(pie_chart);

        graphicsView_pie_chart->setRenderHint(QPainter::Antialiasing); //抗锯齿处理
        //chartView->chart()->setTheme(QChart::ChartThemeBlueCerulean);
        graphicsView_test_pie_chart = graphicsView_pie_chart;
    }

    void add_pie_info(double good,double bad) {
        pie_chart->removeSeries(series);

        series->clear();
//        series->setUseOpenGL(true);
        sum = good+bad;
        good_percent = (good/sum)*100;
        bad_percent = (bad/sum)*100;
        series->append("good  "+QString::number(good_percent,'f',1)+"%", good)->setColor(QColor(0, 200, 0));	// 构造两个饼状分区
//        series->append("不合格", bad)->setColor(QColor(200, 0, 0));//设置每个分区的占比与颜色

        slice = series->append("bad"+QString::number(bad_percent,'f',1)+"%", bad);//增加一个分块，占比30%，并实例化一个QPieSlice指向该分块
        slice->setExploded(true);//让该弧形块与主圆环分开
        slice->setLabelVisible(true);//显示该弧形块的标签
        slice->setColor(QColor(200,0,0));
//        series->setLabelsVisible();

        pie_chart->addSeries(series);
//        graphicsView_test_pie_chart->setChart(pie_chart);
    }

}My_test_pie_chart;
#endif //CABLE_V1_COMMON_H
