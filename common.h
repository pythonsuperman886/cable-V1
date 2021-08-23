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
using namespace at;
QImage Mat2QImage( const cv::Mat& InputMat);
Tensor Mat2Tensor(Mat camera_frame);
Tensor denorm(const torch::Tensor& tensor);
Mat Tensor2Mat(const Tensor& tensor);


#endif //CABLE_V1_COMMON_H
