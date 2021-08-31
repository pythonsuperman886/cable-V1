//
// Created by explore on 2021/8/29.
//

#include "preprocess.h"
Preprocess::Preprocess(){
    reset_parameters();
}

Preprocess::~Preprocess(){

}

void Preprocess::reset_parameters(){
    blur_size = 7;
    threshold_value=100;
    threshold_type=THRESH_BINARY;
    resize_value = 256;
    dilate_kernel_width=2;
    dilate_kernel_height=2;
    kernel_shape=MORPH_RECT;
}


Mat Preprocess ::series_process(Mat input_image){

    blur_mat = blur_image(std::move(input_image),blur_size,blur_type);

    return blur_mat;
}
Mat Preprocess ::rect_image(Mat input,const Rect& rect){
    int new_width;
    if(rect.width+rect.x>input.cols){
        int yu = rect.width+rect.x -input.cols;
        new_width = rect.width-yu;
    }else{
        new_width =  rect.width;
    }
    Rect new_rect(rect.x,0,new_width,rect.height);

    Mat roiImg = input(new_rect);
    return roiImg;
};

void Preprocess::set_binary_parameters(int value,ThresholdTypes type) {
    threshold_value = value;
    threshold_type = type;

}

void Preprocess::set_dilate_parameters(int kernel_size,MorphShapes shape) {
    dilate_kernel_height =kernel_size;
    dilate_kernel_width = kernel_size;
    kernel_shape = shape;
}

Mat Preprocess::get_binary_mat() {
    return binary_mat;
}

Mat Preprocess::get_thin_mat() {
    return thin_mat;
}

Mat Preprocess::get_dilate_mat() {
    return dilate_mat;
}

void Preprocess::set_blur_parameters(int kernel_size) {
    blur_size = kernel_size;
}

Mat Preprocess::get_blur_mat() {
    return blur_mat;
}


Mat Preprocess::get_gray_mat() {
    return resize_mat;
}

Mat Preprocess::blur_image(Mat input,int size,int type) {
    Mat output;
    Size kernel_size(size,size);
    switch(type)
    {
        case 0:
            blur( input, output, kernel_size);
            break;
            case 1:
                medianBlur(input,output,size);
                break;
                case 2:
                    GaussianBlur(input,output,kernel_size,0);
                    break;
                    case 3:
                        GaussianBlur(input,output,kernel_size,0);
                        break;
                        default:
                            output = input;
                            //         break;
    }
    return output;

}

Mat Preprocess::binary_image(Mat input,int threshold,int type) {
    Mat output;
    //    Size kernel_size(size,size);
    switch(type)
    {
        case 0:
            cv::threshold(input, output, threshold, 255, type);/**/
            break;
            case 1:
                cv::threshold(input, output, threshold, 255, type);/**/
                break;
                case 2:
                    cv::threshold(input, output, threshold, 255, type);/**/
                    break;
                    case 3:
                        cv::adaptiveThreshold(input,output,255,0,THRESH_BINARY,31,0);
                        break;
                        default:
                            output = input;
                            //                            cv::threshold(input, output, threshold, 255, type);/**/
                            //                            break;
    }
    return output;
}

void Preprocess::Preprocess2Save(Mat image, string num) {
    cv::imwrite(test_image_save_path+"/"+num+".png",image);
}
