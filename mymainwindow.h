//
// Created by explore on 2021/8/22.
//

#ifndef CABLE_V1_MYMAINWINDOW_H
#define CABLE_V1_MYMAINWINDOW_H
#include <QMainWindow>
#include <QtDebug>
#include <QTimer>
#include "ui_mainwindow.h"
#include "camera.h"
#include "trainer.h"
#include "testnet.h"
#include <thread>
#include <QTextStream>
#include <QFile>
#include "preprocess.h"
#include <QtCharts>
#include <QTableView>
#include <QStandardItemModel>

namespace Ui {
    class MainWindow;
}
class MyMainWindow:public QMainWindow {

    Q_OBJECT
public:
    explicit MyMainWindow(QWidget *parent = nullptr);
    ~MyMainWindow() override;
    void time_out();
    void set_save_path();
    void set_model_path();
    void change_save_flag();
    void change_train_flag();
    void start_train();
    void change_test_flag();
    void init_test();
    void change_defect_threshold(int i);
    void set_group_id();
    Rect get_rect(int w,int h);
    void add_defect_num(int pic_num,int num, const vector<int>& diameter_nums);

signals:
    void train();
    void test();


private:
    QFile qfile;
    QTextStream *textStream;
    Ui::MainWindow * ui;
    string save_path_image;
    string model_path;
    QTimer *timer;
    Camera camera;
    Trainer *trainer;
    Testnet * tester;

    Preprocess preprocess;
    Mat preprocess_mat;
    QImage preprocess_qt;

    int frame_num = 0;
    Mat camera_mat;
    QImage camera_qt;
    vector<Rect> defect_rect_lists;


    QChart *line_chart;
    QLineSeries *series_defect;
    QValueAxis *axisX;
    QValueAxis *axisY;
    QList<QPointF> point_lists;

    QStandardItemModel *model;
    int model_count = 0;

    Mat re_rect_mat;
    QImage test_camera_qt;
    QImage defect_qt;
    QImage train_result;

    bool Is_save=false;
    bool Is_train=false;
    bool Is_test=false;

    int frequency = 40;
    int save_data_nums=0;
    int width_camera_label;
    int height_camera_label;
    int width_defect_label;
    int height_defect_label;

    int width_test_image_label;
    int height_test_image_label;

    int width_train_image_label;
    int height_train_image_label;
    public slots:
    void on_spinBox_defect_threshold_valueChanged(int i);
    void on_spinBox_block_size_valueChanged(int i);
    void on_spinBox_blur_num_valueChanged(int i);
    void on_buttonGroup_blur_toggled(int id,bool type);


};


#endif //CABLE_V1_MYMAINWINDOW_H
