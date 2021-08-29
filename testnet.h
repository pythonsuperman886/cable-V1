//
// Created by explore on 2021/8/21.
//

#ifndef CABLE_V1_TESTNET_H
#define CABLE_V1_TESTNET_H
#include "common.h"
#include "networks.hpp"
class Testnet {
public:
    Testnet();
    void init();
    ~Testnet();
    vector<Mat> Test(const Mat& image);
    vector<Mat> rectangle_cable_defect( Mat& fake_image,Mat &real_image);

    int defect_threhold = 30;
    int threshold_blocksize = 31;
    string model_path = "../checkpoints/model/epoch_latest_gen.pth";

private:
    bool Is_save=false;
//    Scalar rectangle_color;
//    int color;
    cv::Scalar rectangle_color;
    int test_num=0;
    bool cuda_available;
    torch::Device device;
    UNet_Generator G;
//    torch::NoGradGuard no_grad;
    TickMeter tm;
//    torch::Device device(cuda_available ? torch::kCUDA : torch::kCPU);
//    std::cout << (cuda_available ? "CUDA available. Training on GPU." : "Training on CPU.") << '\n';

};


#endif //CABLE_V1_TESTNET_H
