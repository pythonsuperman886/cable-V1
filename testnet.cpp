//
// Created by explore on 2021/8/21.
//

#include "testnet.h"
Testnet::Testnet():
            cuda_available (torch::cuda::is_available() ),
            device(Device(cuda_available ? torch::kCUDA : torch::kCPU)),
            G(UNet_Generator(1,1)){

}
void Testnet::init(string model_path_){
    cout<<"load model..."<<endl;
    model_path=model_path_;
    torch::load(G, model_path);
    G->to(device);
    G->eval();
};

Mat Testnet::Test(Mat image){

    Mat resize_image;
    resize(image,resize_image,Size(128,128));
//    TickMeter tm;
//    cout<<"forward..."<<endl;
//    torch::AutoGradMode enable_grad(false);

    Mat out;
//    for(int i =1;i<15;i++){
    tm.reset();
    tm.start();
    Tensor input = Mat2Tensor(resize_image);
    input = input.to(device);

    Tensor fake_B;
    fake_B = G->forward(input);
    out = Tensor2Mat(fake_B);

    tm.stop();
    cout<<"time forward: "<<tm.getTimeMilli()<<endl;
//    cout<<" grade "<<fake_B.requires_grad()<<endl;


    vector<Mat> ouputs={
            resize_image,out
    };

    Mat combine;
    hconcat(ouputs,combine);
//    }
//    fake_B = fake_B.mul(255).add(0.5).clamp(0, 255).permute({0,3,1,2}).to(torch::kU8);
//    fake_B = fake_B.to(torch::kCPU);
//    cv::Mat imgbin(cv::Size(image_resize_num, image_resize_num), CV_8U, fake_B.data_ptr());
    imwrite("../checkpoints/test_results/"+to_string(test_num)+".png",combine);
    test_num++;
    return out.clone();

}

Testnet::~Testnet() {
//    delete G;

};
