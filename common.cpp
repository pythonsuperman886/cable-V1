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
vector<int> Max_deal_pic(const Mat& image)
{
    //    string path = "/home/explore/data/28/18149.png";
//    Mat image = imread(path);
    // 灰度处理
//    Mat gray_image;
//    cvtColor(image,gray_image,CV_BGR2GRAY);
    // 高斯滤波
    Size kernel_size(3,3);
    Mat blur;
    GaussianBlur(image,blur,kernel_size,19);
    // 二值化
    Mat binary;
    cv::threshold(blur, binary, 40, 255, CV_THRESH_BINARY);
    // 查找图片边缘
    Canny(binary,binary,150,255);
    // 闭运算
    Mat element = getStructuringElement(MORPH_RECT,
                                        Size(17, 17));
    Mat morphology_result;
    morphologyEx(binary, morphology_result, MORPH_CLOSE,element);
    // 查找边界
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(morphology_result,contours,hierarchy,
                 RETR_TREE,CHAIN_APPROX_SIMPLE,Point());
    vector<int> my_x;
    for (int i = 0; i < contours.size(); i++)
    {
        for(int j = 0 ;j<contours[i].size();j++)
        {
            int x = contours[i][j].x;
            my_x.push_back(x);
        }
    }
    // 利用最值画出对应的竖线
    vector<int>::iterator p = min_element(my_x.begin(), my_x.end());
    int min_c = *p;
    vector<int>::iterator q = max_element(my_x.begin(), my_x.end());
    int max_c = *q;
    //    cv::rectangle(image, Point (min_c, 20), Point (max_c, 20), cv::Scalar(0, 0, 255), 2, 8, 0);
    //    cv::rectangle(image, Point (min_c, 0), Point (min_c, image.rows),
    //                  cv::Scalar(0, 0, 200), 2, 8, 0);
    //    cv::rectangle(image, Point (max_c, 0), Point (max_c, image.rows),
    //                  cv::Scalar(0, 0, 200), 2, 8, 0);
    // 将处理好的图片返回
    //    return image;
    // 将最大直径的两个横坐标返回
    vector<int> x_max = {min_c, max_c};
    return x_max;

}

vector<int> min_edge_out(const Mat& image)
{
    //    string path = "/home/explore/data/28/18149.png";
//    Mat image = imread(path);
//    Mat gray_image;
    // 灰度转换
//    cvtColor(image,gray_image,CV_BGR2GRAY);
    // 高斯滤波
    Size kernel_size(5,5);
    Mat blur;
    GaussianBlur(image,blur,kernel_size,11);
    // 二值化
    Mat binary;
    cv::threshold(blur, binary, 25, 255, CV_THRESH_BINARY);
    // 膨胀
    Mat dilate_element = getStructuringElement(MORPH_RECT,
                                               Size(15, 15));
    Mat dilate_pic;
    dilate(binary,dilate_pic,dilate_element);
    // 闭运算
    Mat close_element = getStructuringElement(MORPH_RECT,
                                              Size(17, 17));
    Mat morphology_pic;
    morphologyEx(dilate_pic, morphology_pic, MORPH_CLOSE,close_element);
    // 查找边界
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(morphology_pic,contours,hierarchy,RETR_TREE,CHAIN_APPROX_SIMPLE);
    //    cv::Rect stRect;
    // 处理边缘数组
    vector<int> my_x;
    for(int i = 0;i<contours.size();i++)
    {
        for(int j = 0 ;j<contours[i].size();j++)
        {
            int x = contours[i][j].x;
            my_x.push_back(x);
        }
    }
    double sum = std::accumulate(begin(my_x),end(my_x),0.0);
    double mean = sum/my_x.size();
    int count = 0;
    for(auto & value:my_x){
        if(value<mean){
            count++;
        }
    }

    vector<int>::iterator p = max_element(my_x.begin(), my_x.begin()+count);

    int max_per_c = *p;
    int min_rear_c;
    if(count == my_x.size()){
        min_rear_c = 255;
    }else{
        vector<int>::iterator q = min_element( my_x.begin()+count,my_x.end());
        min_rear_c = *q;
    }
    //    cout<<"max: "<<max_per_c<<endl;
    //    cout<<"min: "<<min_rear_c<<endl;

    //    rectangle(max_image,Point(max_per_c,10),Point(min_rear_c,10),cv::Scalar(0,255,0),3);
    //    cv::rectangle(max_image, Point (max_per_c, 0), Point (max_per_c, image.rows),
    //                  cv::Scalar(0, 200, 0), 2, 8, 0);
    //    cv::rectangle(max_image, Point (min_rear_c, 0), Point (min_rear_c, image.rows),
    //                  cv::Scalar(0, 200, 0), 2, 8, 0);
    // // 将最小直径的两个横坐标返回
    vector<int> x_min = {max_per_c, min_rear_c};
    return x_min;
}

vector<int> get_diameter_nums(const Mat& image)
{

    // 定义四个大小的vector存放四个极值的横坐标
    vector<int> x_max = Max_deal_pic(image);
    vector<int> x_min = min_edge_out(image);
    // 将最小值坐标插入到最大值坐标的容器之后
    // 前两个是最大值左右边缘横坐标
    // 后两个是最小值左右边缘横坐标
    x_max.insert(x_max.end(), x_min.begin(), x_min.end());
    vector<int> four_x = x_max;
    return four_x;
}
void draw_line_diameter(Mat &image, vector<int> nums){
    rectangle(image,Point(nums[0],0),Point(nums[0],image.rows), cv::Scalar(0,200,0));
    rectangle(image,Point(nums[1],0),Point(nums[1],image.rows), cv::Scalar(0,200,0));
    rectangle(image,Point(nums[2],0),Point(nums[2],image.rows), cv::Scalar(200,0,0));
    rectangle(image,Point(nums[3],0),Point(nums[3],image.rows), cv::Scalar(200,0,0));

}