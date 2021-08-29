//
// Created by explore on 2021/8/29.
//

#ifndef CABLE_V1_PREPROCESS_H
#define CABLE_V1_PREPROCESS_H
#include "common.h"

class Preprocess {

public:
    Preprocess();
    //    explicit Preprocess(QObject *parent = nullptr);
    ~Preprocess();
    void reset_parameters();
    Mat series_process(Mat input_image);

    void Preprocess2Save(Mat image,string path);

    void set_binary_parameters(int threshold_vaule,ThresholdTypes type=THRESH_BINARY);
    void set_dilate_parameters(int kernel_size,MorphShapes shape = MORPH_RECT);
    void set_blur_parameters(int kernel_size);


    Mat blur_image(Mat input,int size,int type);
    Mat binary_image(Mat input,int threshold,int type);

    Mat get_binary_mat();
    Mat get_thin_mat();
    Mat get_dilate_mat();
    Mat get_blur_mat();
    Mat get_gray_mat();




private:
    Mat blur_mat;
    Mat resize_mat;
    Mat binary_mat;
    Mat thin_mat;
    Mat dilate_mat;

    int blur_size;
    int threshold_value;
    ThresholdTypes threshold_type;
    int resize_value;
    int dilate_kernel_width;
    int dilate_kernel_height;
    MorphShapes kernel_shape;
public:
    string test_image_save_path=".";

    int blur_type;
    int binary_type;
    int dilate_type;
};


#endif //CABLE_V1_PREPROCESS_H
