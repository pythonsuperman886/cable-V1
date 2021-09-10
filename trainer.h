//
// Created by explore on 2021/8/21.
//

#ifndef CABLE_V1_TRAINER_H
#define CABLE_V1_TRAINER_H
#include "common.h"
#include "datasets.h"
#include "datasets.h"
#include "transforms.hpp"
#include "networks.hpp"
#include "dataloader.h"
class Trainer {
public:
    Trainer();
    ~Trainer();
    void init(string data_path);
    void train();
    void stop_train();
    Mat combine;
    int64_t batch_size = 1;

private:
    std::ofstream ofs;
    bool Is_continue_train =true;
    bool cuda_available;

    torch::Device device;
    const std::string sample_output_dir_path = "../output/";
    string input_dir;

    const size_t num_epochs = 2000;
    const double learning_rate = 0.0002;
    int image_resize_num = 128;
    bool train_shuffle = true;  // whether to shuffle the training dataset
    size_t train_workers = 4;  //
    int thickiness = -1;
    int min = 0;
    int max = 1;
    int lambda_L1 = 100;

    int num_samples;
    std::tuple<torch::Tensor, torch::Tensor, std::vector<std::string>, std::vector<std::string>> mini_batch;

    ImageFolderWithPaths dataset;
    Dataloader dataloader;

    std::vector<transforms_Compose> transform_A;
    std::vector<transforms_Compose> transform_B;

    UNet_Generator G;
    PatchGAN_Discriminator D;

    torch::optim::Adam optimizer_D;
    torch::optim::Adam optimizer_G;

    torch::nn::MSELoss criterion_GAN ;
    torch::nn::L1Loss criterion_L1 ;


    torch::Tensor loss_D, loss_D_real, loss_D_fake;
    torch::Tensor loss_G, loss_G_L1, loss_G_GAN;
    torch::Tensor pred_real;
    torch::Tensor real_AB;

};


#endif //CABLE_V1_TRAINER_H
