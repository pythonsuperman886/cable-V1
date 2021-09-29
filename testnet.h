//
// Created by explore on 2021/8/21.
//

#ifndef CABLE_V1_TESTNET_H
#define CABLE_V1_TESTNET_H
#include "common.h"
#include "networks.hpp"
#include "transforms.hpp"

class Testnet {
public:
    Testnet();
    void init();
    ~Testnet();
    vector<Mat> Test(const Mat& image);
    Mat Test( Mat& image,vector<Rect> &lists);
    Mat rectangle_cable_defect(Mat fake_image,const vector<Rect>& lists);

    vector<Mat> rectangle_cable_defect( Mat& fake_image,Mat &real_image);
    vector<Rect> get_defect_rect_list( Mat fake_image,Mat &resize_to_origin_image_net_out);

    int defect_threhold = 30;
    int threshold_blocksize = 31;
    string model_path = "../checkpoints/model/epoch_latest_gen.pth";
    int copy_border_left=0;
    int copy_border_right=0;
    int rect_image_width=640;
    int rect_image_height=480;
    int test_num=0;

private:
    int image_resize_num = 128;
    std::vector<transforms_Compose> transform_A;
    bool Is_save=false;
//    Scalar rectangle_color;
//    int color;
    cv::Scalar rectangle_color;
    bool cuda_available;
    torch::Device device;
    UNet_Generator G;
//    torch::NoGradGuard no_grad;
    TickMeter tm;
//    torch::Device device(cuda_available ? torch::kCUDA : torch::kCPU);
//    std::cout << (cuda_available ? "CUDA available. Training on GPU." : "Training on CPU.") << '\n';

};


#endif //CABLE_V1_TESTNET_H
