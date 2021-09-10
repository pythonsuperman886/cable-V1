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
#endif //CABLE_V1_COMMON_H
