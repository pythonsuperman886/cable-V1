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

void Preprocess ::get_camera_mat(Mat camera){
    camera_mat = camera;
}

Mat Preprocess ::series_process(){
    //    cv::cvtColor(camera_mat, gray_mat, CV_BGR2GRAY);
    Mat element = getStructuringElement(0, Size(dilate_kernel_width, dilate_kernel_height),Point(-1, -1)); //第一个参数MORPH_RECT表示矩形的卷积核，当然还可以选择椭圆形的、交叉型的

    cv::resize(camera_mat, resize_mat, cv::Size(resize_value, resize_value));

    blur_mat = blur_image(resize_mat,blur_size,blur_type);
    //    medianBlur(resize_mat,blur_mat,blur_size);
    //    GaussianBlur(resize_mat,blur_mat,Size(blur_size,blur_size),0);
    //    blur( src_gray, detected_edges, Size(3,3) );
//    binary_mat = binary_image(blur_mat,threshold_value,binary_type);
    /// 运行Canny算子
    //    Canny( blur_mat, binary_mat, threshold_value, 200, 3 );
    //    cv::threshold(blur_mat, binary_mat, threshold_value, 255, threshold_type);/**/
    //    cv::adaptiveThreshold(blur_mat,binary_mat,255,0,THRESH_BINARY,31,0);
//    morphologyEx(binary_mat, dilate_mat, CV_MOP_CLOSE, element);//闭操作
    //    dilate(binary_mat, dilate_mat, element);
//    thin_mat = binary_mat;
    //    dilate_mat = binary_mat;
    //    cv::resize(binary_image, binary_image, cv::Size(image_size, image_size));

    //    thin_mat = thinimage(binary_mat.clone());
    //    cout<<"time: "<<tm.getTimeSec()<<endl;
    //        cv::cvtColor(frame, frame, CV_GRAY2RGB);
    //        erode(result, result, element);
    //    dilate(thin_mat, dilate_mat, element);
    return blur_mat;
}
Mat Preprocess::thinimage(Mat srcimage)//单通道、二值化后的图像
{
    vector<Point> deletelist1;
    int Zhangmude[9];
    int nl = srcimage.rows;
    int nc = srcimage.cols;
    while (true) {
        for (int j = 1; j < (nl - 1); j++) {
            uchar *data_last = srcimage.ptr<uchar>(j - 1);
            uchar *data = srcimage.ptr<uchar>(j);
            uchar *data_next = srcimage.ptr<uchar>(j + 1);
            for (int i = 1; i < (nc - 1); i++) {
                if (data[i] == 255) {
                    Zhangmude[0] = 1;
                    if (data_last[i] == 255) Zhangmude[1] = 1;
                    else Zhangmude[1] = 0;
                    if (data_last[i + 1] == 255) Zhangmude[2] = 1;
                    else Zhangmude[2] = 0;
                    if (data[i + 1] == 255) Zhangmude[3] = 1;
                    else Zhangmude[3] = 0;
                    if (data_next[i + 1] == 255) Zhangmude[4] = 1;
                    else Zhangmude[4] = 0;
                    if (data_next[i] == 255) Zhangmude[5] = 1;
                    else Zhangmude[5] = 0;
                    if (data_next[i - 1] == 255) Zhangmude[6] = 1;
                    else Zhangmude[6] = 0;
                    if (data[i - 1] == 255) Zhangmude[7] = 1;
                    else Zhangmude[7] = 0;
                    if (data_last[i - 1] == 255) Zhangmude[8] = 1;
                    else Zhangmude[8] = 0;
                    int whitepointtotal = 0;
                    for (int k = 1; k < 9; k++) {
                        whitepointtotal = whitepointtotal + Zhangmude[k];
                    }
                    if ((whitepointtotal >= 2) && (whitepointtotal <= 6)) {
                        int ap = 0;
                        if ((Zhangmude[1] == 0) && (Zhangmude[2] == 1)) ap++;
                        if ((Zhangmude[2] == 0) && (Zhangmude[3] == 1)) ap++;
                        if ((Zhangmude[3] == 0) && (Zhangmude[4] == 1)) ap++;
                        if ((Zhangmude[4] == 0) && (Zhangmude[5] == 1)) ap++;
                        if ((Zhangmude[5] == 0) && (Zhangmude[6] == 1)) ap++;
                        if ((Zhangmude[6] == 0) && (Zhangmude[7] == 1)) ap++;
                        if ((Zhangmude[7] == 0) && (Zhangmude[8] == 1)) ap++;
                        if ((Zhangmude[8] == 0) && (Zhangmude[1] == 1)) ap++;
                        if (ap == 1) {
                            if ((Zhangmude[1] * Zhangmude[7] * Zhangmude[5] == 0) &&
                            (Zhangmude[3] * Zhangmude[5] * Zhangmude[7] == 0)) {
                                deletelist1.push_back(Point(i, j));
                            }
                        }
                    }
                }
            }
        }
        if (deletelist1.size() == 0) break;
        for (size_t i = 0; i < deletelist1.size(); i++) {
            Point tem;
            tem = deletelist1[i];
            uchar *data = srcimage.ptr<uchar>(tem.y);
            data[tem.x] = 0;
        }
        deletelist1.clear();

        for (int j = 1; j < (nl - 1); j++) {
            uchar *data_last = srcimage.ptr<uchar>(j - 1);
            uchar *data = srcimage.ptr<uchar>(j);
            uchar *data_next = srcimage.ptr<uchar>(j + 1);
            for (int i = 1; i < (nc - 1); i++) {
                if (data[i] == 255) {
                    Zhangmude[0] = 1;
                    if (data_last[i] == 255) Zhangmude[1] = 1;
                    else Zhangmude[1] = 0;
                    if (data_last[i + 1] == 255) Zhangmude[2] = 1;
                    else Zhangmude[2] = 0;
                    if (data[i + 1] == 255) Zhangmude[3] = 1;
                    else Zhangmude[3] = 0;
                    if (data_next[i + 1] == 255) Zhangmude[4] = 1;
                    else Zhangmude[4] = 0;
                    if (data_next[i] == 255) Zhangmude[5] = 1;
                    else Zhangmude[5] = 0;
                    if (data_next[i - 1] == 255) Zhangmude[6] = 1;
                    else Zhangmude[6] = 0;
                    if (data[i - 1] == 255) Zhangmude[7] = 1;
                    else Zhangmude[7] = 0;
                    if (data_last[i - 1] == 255) Zhangmude[8] = 1;
                    else Zhangmude[8] = 0;
                    int whitepointtotal = 0;
                    for (int k = 1; k < 9; k++) {
                        whitepointtotal = whitepointtotal + Zhangmude[k];
                    }
                    if ((whitepointtotal >= 2) && (whitepointtotal <= 6)) {
                        int ap = 0;
                        if ((Zhangmude[1] == 0) && (Zhangmude[2] == 1)) ap++;
                        if ((Zhangmude[2] == 0) && (Zhangmude[3] == 1)) ap++;
                        if ((Zhangmude[3] == 0) && (Zhangmude[4] == 1)) ap++;
                        if ((Zhangmude[4] == 0) && (Zhangmude[5] == 1)) ap++;
                        if ((Zhangmude[5] == 0) && (Zhangmude[6] == 1)) ap++;
                        if ((Zhangmude[6] == 0) && (Zhangmude[7] == 1)) ap++;
                        if ((Zhangmude[7] == 0) && (Zhangmude[8] == 1)) ap++;
                        if ((Zhangmude[8] == 0) && (Zhangmude[1] == 1)) ap++;
                        if (ap == 1) {
                            if ((Zhangmude[1] * Zhangmude[3] * Zhangmude[5] == 0) &&
                            (Zhangmude[3] * Zhangmude[1] * Zhangmude[7] == 0)) {
                                deletelist1.push_back(Point(i, j));
                            }
                        }
                    }
                }
            }
        }
        if (deletelist1.size() == 0) break;
        for (size_t i = 0; i < deletelist1.size(); i++) {
            Point tem;
            tem = deletelist1[i];
            uchar *data = srcimage.ptr<uchar>(tem.y);
            data[tem.x] = 0;
        }
        deletelist1.clear();
    }
    return srcimage;

}

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
