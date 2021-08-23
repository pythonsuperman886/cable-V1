//
// Created by explore on 2021/8/18.
//

#ifndef CABLE_DEFECT_DETECT_QT_DATASETS_H
#define CABLE_DEFECT_DETECT_QT_DATASETS_H
#include <fstream>
#include <filesystem>
#include <string>
#include <sstream>
#include <tuple>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
// For External Library
#include <torch/torch.h>
#include <opencv2/opencv.hpp>
#include "transforms.hpp"
#include <random>
#include <QFileInfo>
#include <QDateTime>
#include <QDebug>
#include <QDir>
namespace fs = std::filesystem;
using namespace std;
class ImageFolderWithPaths{
private:
    std::vector<transforms_Compose> transform_A;
    std::vector<transforms_Compose> transform_B;

    std::vector<std::string> paths, fnames;
public:
    ImageFolderWithPaths(){};
    ImageFolderWithPaths(const std::string& root, std::vector<transforms_Compose> &transform_A,std::vector<transforms_Compose> &transform_B);
    void get(const size_t idx, std::tuple<torch::Tensor, torch::Tensor, std::string,std::string> &data);
    size_t size();
    void mycollect(const std::string& root);
    int collect(const std::string& path);
    cv::Mat RGB_Loader(std::string &path);

};


#endif //CABLE_DEFECT_DETECT_QT_DATASETS_H
