//
// Created by explore on 2021/8/21.
//

#include "common.h"
QImage Mat2QImage( const cv::Mat& InputMat)
{

    cv::Mat TmpMat;

    if (InputMat.channels() == 1)

    {
        cv::cvtColor(InputMat, TmpMat, CV_GRAY2RGB);
    }

    else

    {
        cv::cvtColor(InputMat, TmpMat, CV_BGR2RGB);
    }


    // construct the QImage using the data of the mat, while do not copy the data

    QImage Result = QImage((const uchar*)(TmpMat.data), TmpMat.cols, TmpMat.rows,

                           QImage::Format_RGB888);

    // deep copy the data from mat to QImage

    Result.bits();

    return Result;
}

Tensor Mat2Tensor(Mat camera_frame) {
    int h = camera_frame.rows;
    int w = camera_frame.cols;
    Mat origin_image = std::move(camera_frame);
    Mat std_image;

    origin_image.convertTo(std_image, CV_32FC1, 1.0 / 255);
    float mean = 0.50;
    float std = 0.50;

    auto input_tensor = torch::from_blob(std_image.data, {1, h, w, 1});
    input_tensor = input_tensor.sub_(mean).div_(std);

    input_tensor = input_tensor.permute({0, 3, 1, 2});
    auto img_var = torch::autograd::make_variable(input_tensor, false); //不需要梯度

    return img_var;
}
Tensor denorm(const torch::Tensor& tensor) {
    return tensor.add(1).div_(2).clamp_(0, 1);
};
Mat Tensor2Mat(const Tensor& tensor){
    int h = tensor.size(2);
    int w = tensor.size(3);
    auto out_tensor = denorm(tensor);
    out_tensor = out_tensor.mul(255).add(0.5).clamp(0, 255).permute({0,3,1,2}).to(torch::kU8);
    out_tensor = out_tensor.to(torch::kCPU);
    cv::Mat Mat_out(cv::Size(h, w), CV_8U, out_tensor.data_ptr());
    Mat out = Mat_out.clone();
    return out;
};
