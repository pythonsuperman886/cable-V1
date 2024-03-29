#include <vector>
#include <utility>
#include <cmath>
// For External Library
#include <torch/torch.h>
#include <opencv2/opencv.hpp>
// For Original Header
#include "transforms.hpp"


// -------------------------------------------
// namespace{transforms} -> function{apply}
// -------------------------------------------
torch::Tensor transforms::apply(std::vector<transforms_Compose> &transform, cv::Mat &data_in){
    torch::Tensor data_out;
    transforms::forward<cv::Mat, torch::Tensor>(transform, data_in, data_out, transform.size());
    return data_out.contiguous().detach().clone();
}


// -------------------------------------------
// namespace{transforms} -> function{applyT}
// -------------------------------------------
torch::Tensor transforms::applyT(std::vector<transforms_Compose> &transform, torch::Tensor &data_in){
    torch::Tensor data_out;
    if (transform.size() > 0){
        transforms::forward<torch::Tensor, torch::Tensor>(transform, data_in, data_out, transform.size());
    }
    else{
        data_out = data_in;
    }
    return data_out.contiguous().detach().clone();
}


// -------------------------------------------
// namespace{transforms} -> function{forward}
// -------------------------------------------
template <typename T_in, typename T_out>
void transforms::forward(std::vector<transforms_Compose> &transform_, T_in &data_in, T_out &data_out, const int count){
    auto transform = transform_.at(count - 1);
    if (count > 1){
        auto transform2 = transform_.at(count - 2);
        if (transform2->type() == CV_MAT){
            cv::Mat data_mid;
            transforms::forward<T_in, cv::Mat>(transform_, data_in, data_mid, count - 1);
            transform->forward(data_mid, data_out);
        }
        else{
            torch::Tensor data_mid;
            transforms::forward<T_in, torch::Tensor>(transform_, data_in, data_mid, count - 1);
            transform->forward(data_mid, data_out);
        }
    }
    else{
        transform->forward(data_in, data_out);
    }
    return;
}
template void transforms::forward<cv::Mat, cv::Mat>(std::vector<transforms_Compose> &transform_, cv::Mat &data_in, cv::Mat &data_out, const int count);
template void transforms::forward<cv::Mat, torch::Tensor>(std::vector<transforms_Compose> &transform_, cv::Mat &data_in, torch::Tensor &data_out, const int count);
template void transforms::forward<torch::Tensor, cv::Mat>(std::vector<transforms_Compose> &transform_, torch::Tensor &data_in, cv::Mat &data_out, const int count);
template void transforms::forward<torch::Tensor, torch::Tensor>(std::vector<transforms_Compose> &transform_, torch::Tensor &data_in, torch::Tensor &data_out, const int count);



/*******************************************************************************/
/*                                   Data 1d                                   */
/*******************************************************************************/


// ------------------------------------------------------------------------------
// namespace{transforms} -> class{Normalize1dImpl}(ComposeImpl) -> constructor
// ------------------------------------------------------------------------------
transforms::Normalize1dImpl::Normalize1dImpl(const float mean_, const float std_){
    this->mean = torch::from_blob((float *)&mean_, {1}, torch::kFloat).clone();  // mean{1}
    this->std = torch::from_blob((float *)&std_, {1}, torch::kFloat).clone();  // std{1}
}

transforms::Normalize1dImpl::Normalize1dImpl(const float mean_, const std::vector<float> std_){
    this->mean = torch::from_blob((float *)&mean_, {1}, torch::kFloat).clone();  // mean{1}
    this->std = torch::from_blob((float *)std_.data(), {(long int)std_.size()}, torch::kFloat).clone();  // std{D}
}

transforms::Normalize1dImpl::Normalize1dImpl(const std::vector<float> mean_, const float std_){
    this->mean = torch::from_blob((float *)mean_.data(), {(long int)mean_.size()}, torch::kFloat).clone();  // mean{D}
    this->std = torch::from_blob((float *)&std_, {1}, torch::kFloat).clone();  // std{1}
}

transforms::Normalize1dImpl::Normalize1dImpl(const std::vector<float> mean_, const std::vector<float> std_){
    this->mean = torch::from_blob((float *)mean_.data(), {(long int)mean_.size()}, torch::kFloat).clone();  // mean{D}
    this->std = torch::from_blob((float *)std_.data(), {(long int)std_.size()}, torch::kFloat).clone();  // std{D}
}
//torch::Tensor Mat2tesnor_pro(cv::Mat &data_in){
//
//    Mat data_out;
//    cv::Mat float_mat, float_mat_gray;
//    data_in.convertTo(float_mat, CV_32F);  // discrete ===> continuous
//    cv::cvtColor(float_mat, float_mat_gray, cv::COLOR_RGB2GRAY);
//    float_mat_gray.convertTo(data_out, data_in.depth());  // continuous ===> discrete
//
//
//    torch::Tensor mean, std;
//    const float mean_=0.5;
//    const float std_=0.5;
//
//    cv::Mat  float_mat_resize;
//    data_out.convertTo(float_mat, CV_32F);  // discrete ===> continuous
//    cv::resize(float_mat, float_mat_resize, Size(128,128), 0.0, 0.0,  cv::INTER_LINEAR);
//    float_mat_resize.convertTo(data_out, data_in.depth());  // continuous ===> discrete
//
//    data_out.convertTo(float_mat, CV_32F);  // discrete ===> continuous
//    float_mat *= 1.0 / (std::pow(2.0, data_out.elemSize1()*8) - 1.0);  // [0,255] or [0,65535] ===> [0,1]
//    torch::Tensor data_out_src = torch::from_blob(float_mat.data, {float_mat.rows, float_mat.cols, float_mat.channels()}, torch::kFloat);  // {0,1,2} = {H,W,C}
//    data_out_src = data_out_src.permute({2, 0, 1});  // {0,1,2} = {H,W,C} ===> {0,1,2} = {C,H,W}
//    torch::Tensor data_out_tensor = data_out_src.contiguous().detach().clone();
//    mean = torch::from_blob((float *)&mean_, {1, 1, 1}, torch::kFloat).clone();  // mean{1,1,1}
//    std = torch::from_blob((float *)&std_, {1, 1, 1}, torch::kFloat).clone();  // std{1,1,1}
//
//
//
//    long int channels = data_out_tensor.size(0);
//
//    torch::Tensor meanF =mean;
//    if (channels < meanF.size(0)){
//        meanF = meanF.split(/*split_size=*/channels, /*dim=*/0).at(0);  // meanF{*,1,1} ===> {C,1,1}
//    }
//
//    torch::Tensor stdF = std;
//    if (channels < stdF.size(0)){
//        stdF = stdF.split(/*split_size=*/channels, /*dim=*/0).at(0);  // stdF{*,1,1} ===> {C,1,1}
//    }
//
//    data_out_src = (data_out_tensor - meanF.to(data_out_tensor.device())) / stdF.to(data_out_tensor.device());  // data_in{C,H,W}, meanF{*,1,1}, stdF{*,1,1} ===> data_out_src{C,H,W}
//    data_out_tensor = data_out_src.contiguous().detach().clone();
//    return data_out_tensor;
//}

// -----------------------------------------------------------------------------------
// namespace{transforms} -> class{Normalize1dImpl}(ComposeImpl) -> function{forward}
// -----------------------------------------------------------------------------------
void transforms::Normalize1dImpl::forward(torch::Tensor &data_in, torch::Tensor &data_out){

    long int dim = data_in.size(0);

    torch::Tensor meanF = this->mean;
    if (dim < meanF.size(0)){
        meanF = meanF.split(/*split_size=*/dim, /*dim=*/0).at(0);  // meanF{*} ===> {D}
    }

    torch::Tensor stdF = this->std;
    if (dim < stdF.size(0)){
        stdF = stdF.split(/*split_size=*/dim, /*dim=*/0).at(0);  // stdF{*} ===> {D}
    }
    
    torch::Tensor data_out_src = (data_in - meanF.to(data_in.device())) / stdF.to(data_in.device());  // data_in{D}, meanF{*}, stdF{*} ===> data_out_src{D}
    data_out = data_out_src.contiguous().detach().clone();

    return;
}



/*******************************************************************************/
/*                                   Data 2d                                   */
/*******************************************************************************/


// --------------------------------------------------------------------------
// namespace{transforms} -> class{GrayscaleImpl}(ComposeImpl) -> constructor
// --------------------------------------------------------------------------
transforms::GrayscaleImpl::GrayscaleImpl(const int channels_){
    this->channels = channels_;
}


// ---------------------------------------------------------------------------------
// namespace{transforms} -> class{GrayscaleImpl}(ComposeImpl) -> function{forward}
// ---------------------------------------------------------------------------------
void transforms::GrayscaleImpl::forward(cv::Mat &data_in, cv::Mat &data_out){
//    cout<<"image channels: "<<data_in.channels()<<endl;
    cv::Mat float_mat, float_mat_gray,float_mat_bgr;
    data_in.convertTo(float_mat, CV_32F);  // discrete ===> continuous
    cv::cvtColor(float_mat, float_mat_gray, cv::COLOR_RGB2GRAY);


    float_mat_gray.convertTo(data_out, data_in.depth());  // continuous ===> discrete
    if(this->channels ==3){
        cv::cvtColor(data_in, float_mat_bgr, cv::COLOR_RGB2BGR);
        data_out = float_mat_bgr.clone();
//        float_mat_bgr.convertTo(data_out, data_in.depth());  // continuous ===> discrete
    }
//    if (this->channels > 1){
//        std::vector<cv::Mat> multi(this->channels);
//        for (int i = 0; i < this->channels; i++){
//            multi.at(i) = data_out.clone();
//        }
//        cv::merge(multi, data_out);
//    }
    return;
}


// -----------------------------------------------------------------------
// namespace{transforms} -> class{ResizeImpl}(ComposeImpl) -> constructor
// -----------------------------------------------------------------------
transforms::ResizeImpl::ResizeImpl(const cv::Size size_, const int interpolation_){
    this->size = size_;
    this->interpolation = interpolation_;
}


// -----------------------------------------------------------------------------
// namespace{transforms} -> class{ResizeImpl}(ComposeImpl) -> function{forward}
// -----------------------------------------------------------------------------
void transforms::ResizeImpl::forward(cv::Mat &data_in, cv::Mat &data_out){
    cv::Mat float_mat, float_mat_resize;
    data_in.convertTo(float_mat, CV_32F);  // discrete ===> continuous
    cv::resize(float_mat, float_mat_resize, this->size, 0.0, 0.0, this->interpolation);
    float_mat_resize.convertTo(data_out, data_in.depth());  // continuous ===> discrete
    return;
}


// -----------------------------------------------------------------------------
// namespace{transforms} -> class{ConvertIndexImpl}(ComposeImpl) -> constructor
// -----------------------------------------------------------------------------
transforms::ConvertIndexImpl::ConvertIndexImpl(const int before_, const int after_){
    this->before = before_;
    this->after = after_;
}


// -----------------------------------------------------------------------------------
// namespace{transforms} -> class{ConvertIndexImpl}(ComposeImpl) -> function{forward}
// -----------------------------------------------------------------------------------
void transforms::ConvertIndexImpl::forward(cv::Mat &data_in, cv::Mat &data_out){
    size_t width = data_in.cols;
    size_t height = data_in.rows;
    data_out = cv::Mat(cv::Size(width, height), CV_32SC1);
    for (size_t j = 0; j < height; j++){
        for (size_t i = 0; i < width; i++){
            if (data_in.at<int>(j, i) == this->before){
                data_out.at<int>(j, i) = this->after;
            }
            else{
                data_out.at<int>(j, i) = data_in.at<int>(j, i);
            }
        }
    }
    return;
}


// -------------------------------------------------------------------------------
// namespace{transforms} -> class{ToTensorImpl}(ComposeImpl) -> function{forward}
// -------------------------------------------------------------------------------
void transforms::ToTensorImpl::forward(cv::Mat &data_in, torch::Tensor &data_out){
    cv::Mat float_mat;
    data_in.convertTo(float_mat, CV_32F);  // discrete ===> continuous
    float_mat *= 1.0 / (std::pow(2.0, data_in.elemSize1()*8) - 1.0);  // [0,255] or [0,65535] ===> [0,1]
    torch::Tensor data_out_src = torch::from_blob(float_mat.data, {float_mat.rows, float_mat.cols, float_mat.channels()}, torch::kFloat);  // {0,1,2} = {H,W,C}
    data_out_src = data_out_src.permute({2, 0, 1});  // {0,1,2} = {H,W,C} ===> {0,1,2} = {C,H,W}
    data_out = data_out_src.contiguous().detach().clone();
    return;
}


// ------------------------------------------------------------------------------------
// namespace{transforms} -> class{ToTensorLabelImpl}(ComposeImpl) -> function{forward}
// ------------------------------------------------------------------------------------
void transforms::ToTensorLabelImpl::forward(cv::Mat &data_in, torch::Tensor &data_out){
    torch::Tensor data_out_src = torch::from_blob(data_in.data, {data_in.rows, data_in.cols, data_in.channels()}, torch::kInt).to(torch::kLong);  // {0,1,2} = {H,W,C}
    data_out_src = data_out_src.permute({2, 0, 1});  // {0,1,2} = {H,W,C} ===> {0,1,2} = {C,H,W}
    data_out_src = torch::squeeze(data_out_src, /*dim=*/0);  // {C,H,W} ===> {H,W}
    data_out = data_out_src.contiguous().detach().clone();
    return;
}


// ----------------------------------------------------------------------------
// namespace{transforms} -> class{AddRVINoiseImpl}(ComposeImpl) -> constructor
// ----------------------------------------------------------------------------
transforms::AddRVINoiseImpl::AddRVINoiseImpl(const float occur_prob_, const std::pair<float, float> range_){
    this->occur_prob = occur_prob_;
    this->range = range_;
}


// ----------------------------------------------------------------------------------
// namespace{transforms} -> class{AddRVINoiseImpl}(ComposeImpl) -> function{forward}
// ----------------------------------------------------------------------------------
void transforms::AddRVINoiseImpl::forward(torch::Tensor &data_in, torch::Tensor &data_out){

    long int width = data_in.size(2);
    long int height = data_in.size(1);
    long int channels = data_in.size(0);

    torch::Tensor randu = torch::rand({1, height, width}).to(data_in.device());
    torch::Tensor noise_flag = (randu < this->occur_prob).to(torch::kFloat).expand({channels, height, width});
    torch::Tensor base_flag = ((randu < this->occur_prob) == false).to(torch::kFloat).expand({channels, height, width});

    torch::Tensor noise = torch::rand({channels, height, width}).to(data_in.device()) * (this->range.second - this->range.first) + this->range.first;
    torch::Tensor data_mix = data_in * base_flag + noise * noise_flag;
    data_out = data_mix.contiguous().detach().clone();

    return;
}


// ---------------------------------------------------------------------------
// namespace{transforms} -> class{AddSPNoiseImpl}(ComposeImpl) -> constructor
// ---------------------------------------------------------------------------
transforms::AddSPNoiseImpl::AddSPNoiseImpl(const float occur_prob_, const float salt_rate_, const std::pair<float, float> range_){
    this->occur_prob = occur_prob_;
    this->salt_rate = salt_rate_;
    this->range = range_;
}


// ---------------------------------------------------------------------------------
// namespace{transforms} -> class{AddSPNoiseImpl}(ComposeImpl) -> function{forward}
// ---------------------------------------------------------------------------------
void transforms::AddSPNoiseImpl::forward(torch::Tensor &data_in, torch::Tensor &data_out){
    
    long int width = data_in.size(2);
    long int height = data_in.size(1);
    long int channels = data_in.size(0);

    torch::Tensor randu = torch::rand({1, height, width}).to(data_in.device());
    torch::Tensor noise_flag = (randu < this->occur_prob).to(torch::kFloat).expand({channels, height, width});
    torch::Tensor base_flag = ((randu < this->occur_prob) == false).to(torch::kFloat).expand({channels, height, width});

    torch::Tensor randu2 = torch::rand({1, height, width}).to(data_in.device());
    torch::Tensor salt_flag = (randu2 < this->salt_rate).to(torch::kFloat).expand({channels, height, width}) * noise_flag;
    torch::Tensor pepper_flag = ((randu2 < this->salt_rate) == false).to(torch::kFloat).expand({channels, height, width}) * noise_flag;

    torch::Tensor data_mix = data_in * base_flag + this->range.first * pepper_flag + this->range.second * salt_flag;
    data_out = data_mix.contiguous().detach().clone();

    return;
}


// ------------------------------------------------------------------------------
// namespace{transforms} -> class{AddGaussNoiseImpl}(ComposeImpl) -> constructor
// ------------------------------------------------------------------------------
transforms::AddGaussNoiseImpl::AddGaussNoiseImpl(const float occur_prob_, const float mean_, const float std_, const std::pair<float, float> range_){
    this->occur_prob = occur_prob_;
    this->mean = mean_;
    this->std = std_;
    this->range = range_;
}


// ------------------------------------------------------------------------------------
// namespace{transforms} -> class{AddGaussNoiseImpl}(ComposeImpl) -> function{forward}
// ------------------------------------------------------------------------------------
void transforms::AddGaussNoiseImpl::forward(torch::Tensor &data_in, torch::Tensor &data_out){
    
    long int width = data_in.size(2);
    long int height = data_in.size(1);
    long int channels = data_in.size(0);

    torch::Tensor randu = torch::rand({1, height, width}).to(data_in.device());
    torch::Tensor noise_flag = (randu < this->occur_prob).to(torch::kFloat).expand({channels, height, width});

    torch::Tensor noise = torch::randn({channels, height, width}).to(data_in.device()) * this->std + this->mean;
    torch::Tensor data_mix = (data_in + noise * noise_flag).clamp(/*min=*/this->range.first, /*max=*/this->range.second);
    data_out = data_mix.contiguous().detach().clone();

    return;
}


// ---------------------------------------------------------------------------
// namespace{transforms} -> class{NormalizeImpl}(ComposeImpl) -> constructor
// ---------------------------------------------------------------------------
transforms::NormalizeImpl::NormalizeImpl(const float mean_, const float std_){
    this->mean = torch::from_blob((float *)&mean_, {1, 1, 1}, torch::kFloat).clone();  // mean{1,1,1}
    this->std = torch::from_blob((float *)&std_, {1, 1, 1}, torch::kFloat).clone();  // std{1,1,1}
}

transforms::NormalizeImpl::NormalizeImpl(const float mean_, const std::vector<float> std_){
    this->mean = torch::from_blob((float *)&mean_, {1, 1, 1}, torch::kFloat).clone();  // mean{1,1,1}
    this->std = torch::from_blob((float *)std_.data(), {(long int)std_.size(), 1, 1}, torch::kFloat).clone();  // std{C,1,1}
}

transforms::NormalizeImpl::NormalizeImpl(const std::vector<float> mean_, const float std_){
    this->mean = torch::from_blob((float *)mean_.data(), {(long int)mean_.size(), 1, 1}, torch::kFloat).clone();  // mean{C,1,1}
    this->std = torch::from_blob((float *)&std_, {1, 1, 1}, torch::kFloat).clone();  // std{1,1,1}
}

transforms::NormalizeImpl::NormalizeImpl(const std::vector<float> mean_, const std::vector<float> std_){
    this->mean = torch::from_blob((float *)mean_.data(), {(long int)mean_.size(), 1, 1}, torch::kFloat).clone();  // mean{C,1,1}
    this->std = torch::from_blob((float *)std_.data(), {(long int)std_.size(), 1, 1}, torch::kFloat).clone();  // std{C,1,1}
}


// --------------------------------------------------------------------------------
// namespace{transforms} -> class{NormalizeImpl}(ComposeImpl) -> function{forward}
// --------------------------------------------------------------------------------
void transforms::NormalizeImpl::forward(torch::Tensor &data_in, torch::Tensor &data_out){

    long int channels = data_in.size(0);

    torch::Tensor meanF = this->mean;
    if (channels < meanF.size(0)){
        meanF = meanF.split(/*split_size=*/channels, /*dim=*/0).at(0);  // meanF{*,1,1} ===> {C,1,1}
    }

    torch::Tensor stdF = this->std;
    if (channels < stdF.size(0)){
        stdF = stdF.split(/*split_size=*/channels, /*dim=*/0).at(0);  // stdF{*,1,1} ===> {C,1,1}
    }
    
    torch::Tensor data_out_src = (data_in - meanF.to(data_in.device())) / stdF.to(data_in.device());  // data_in{C,H,W}, meanF{*,1,1}, stdF{*,1,1} ===> data_out_src{C,H,W}
    data_out = data_out_src.contiguous().detach().clone();

    return;
}

transforms::DefectImpl::DefectImpl(int thickness_,int min_,int max_,bool is_mask_) {
     thickness = thickness_;
     min = min_;
     max = max_;
     diff = fabs(max-min);
     is_mask = is_mask_;
//     int myseed =1;
//     double diff = fabs(max-min);
//     double m1=(double)(rand()%100)/100;
//     double retval=min+m1*diff;

//     int nun = (rand()% (max-min))+max;
}
//int transforms::DefectImpl::myseed = 1;
int transforms::DefectImpl:: myseed=1;
//int transforms::TuDianDefectImpl:: myseed=1;
//srand(transforms::DefectImpl:: myseed);

//double transforms::DefectImpl:: m1=(double)(rand()%100)/100;
//double transforms::DefectImpl:: m2=(double)(rand()%100)/100;

//int transforms::DefectImpl::random_type = (int)(rand()%4);
//        static double size_ratio = min+m1*diff;
//int transforms::DefectImpl::random_color_num = rand()%200;


void transforms::DefectImpl::forward(cv::Mat &data_in, cv::Mat &data_out) {

    //    Mat target;

    if(is_mask){
        data_out = Mat::zeros(data_in.rows,data_in.cols,CV_8UC1);
        //        random_color = 255;
    }else{
        data_out = data_in;
        //        random_color = (int)(rand()%200);
    }
    srand(myseed);
    int h = data_in.rows;
    int w = data_in.cols;
    for(int i = 0;i<10;i++){
        double m1=(double)(rand()%100)/100;
        double m2=(double)(rand()%100)/100;
        //        m1 = m1+i*0.2;
        //        m2 = m2+i*0.2;
        int random_color_num = rand()%200;
        int random_type = (int)(rand()%4);
        double size_ratio = min+m1*diff;
        int random_color = (is_mask?255:random_color_num);
        Scalar c(random_color);
        //        cout<<"color: "<<random_color<<endl;


        int size = size_ratio*( h>w?w:h)*0.5;
        int x = (int)(m1*w);
        int line_thickness = (int)(rand()%4)+1;
        int circle_radius = (int)(rand()%2)+1;

        //        cout<<"x: "<<m1<<endl;
        int y = (int)(m2*h);

        circle(data_out, Point(x,y), 6, c,thickness);

        if(random_type ==0){
            circle(data_out, Point(x,y), circle_radius, c,thickness);

        }else if(random_type == 1){
            //            ellipse(data_out,Point(x, y),Size(size, size),30,0,360,c,thickness);

        }else if(random_type == 2){
            rectangle(data_out,Rect(x,y,x+size*0.5,y+size*0.2), c, thickness);

        }else if(random_type == 3){
            line(data_out, Point(x, y), Point(x+size, y+size), c, line_thickness);

        }
    }
    //    std::cout<<"myseed: "<< transforms::DefectImpl::myseed<<std::endl;
    //    if(is_mask)
    //        myseed++;
    //        myseed = myseed %1000;
    //    data_out = data_in.clone();
    //    imwrite("./1.png",data_out);

}

transforms::TuDianDefectImpl::TuDianDefectImpl(bool is_mask_) {
    is_mask = is_mask_;
}
int transforms::TuDianDefectImpl::myseed=1;
void transforms::TuDianDefectImpl::forward(Mat &data_in,Mat &data_out){
    int h = data_in.rows;
    int w = data_in.cols;



    data_out = Mat::zeros(data_in.rows,data_in.cols,CV_8UC1);
    //        Mat mask = Mat::zeros(Size(w,h), CV_8UC1);


    srand(myseed);


    for(int i = 0;i<5;i++){
        double l1=(double)(rand()%60)/100;
        double l2=(double)(rand()%60)/100;
        double l3=(double)(rand()%60)/100;
        double l4=(double)(rand()%60)/100;
        //                m1 = m1+i*0.2;
        //                m2 = m2+i*0.2;
        int random_color_125 = 200;
        int random_color_63 = 20;
        int x_left = l1*w;
        int y_left = l2*h;
        int x_right = l3*w;
        int y_right = l4*h;

        double r1 = (double)(rand()%100)/100;
        double r2 = (double)(rand()%100)/100;
        double r3 = (double)(rand()%100)/100;
        double r4 = (double)(rand()%100)/100;

        int ratio = (double)(rand()%100)/100;
        int size = 0.05*( h>w?w:h)*ratio;
        int x_left_r = r1*w;
        int y_left_r = r2*h;
        int width_r = r3*w;
        int height_r = r4*h;

        double c1 = (double)(rand()%100)/100;
        double c2 = (double)(rand()%100)/100;
        int x_center_c = c1*w;
        int y_center_c = c2*h;
        int radius = (int)(rand()%(h/10))+1;


        if(is_mask){
            line(data_out, Point(x_left,y_left), Point(x_left+size,y_left+size), Scalar(255), 5, LINE_8);//线段绘制
            line(data_out, Point(x_left,y_left), Point(x_left+size,y_left+size), Scalar(0), 2, LINE_8);//线段绘制


            rectangle(data_out, Rect(x_left_r,y_left_r,x_left_r+size*0.3,y_left_r*0.2), Scalar(255), -1, LINE_8);//矩形绘制
            rectangle(data_out, Rect(x_left_r,y_left_r,(x_left_r+size*0.3)/2,y_left_r*0.2), Scalar(0), -1, LINE_8);//矩形绘制

            circle(data_out, Point(x_center_c, y_center_c), radius, Scalar(255), -1, LINE_8);//圆绘制
            ellipse(data_out,Point(x_center_c,y_center_c),Size(radius,radius),0,-90,-270,Scalar(0),-1);

            rectangle(data_out, Rect(0,h/2-h/6,w,h/3+h/20), Scalar(0), -1, LINE_8);//矩形绘制

        }else{
            line(data_out, Point(x_left,y_left), Point(x_right,y_right), Scalar(random_color_125), 5, LINE_8);//线段绘制
            line(data_out, Point(x_left,y_left), Point(x_right,y_right), Scalar(random_color_63), 2, LINE_8);//线段绘制


            rectangle(data_out, Rect(x_left_r,y_left_r,x_left_r+size*0.3,y_left_r*0.2), Scalar(random_color_125), -1, LINE_8);//矩形绘制
            rectangle(data_out, Rect(x_left_r,y_left_r,(x_left_r+size*0.3)/2,y_left_r*0.2), Scalar(random_color_63), -1, LINE_8);//矩形绘制

            circle(data_out, Point(x_center_c, y_center_c), radius, Scalar(random_color_125), -1, LINE_8);//圆绘制
            ellipse(data_out,Point(x_center_c,y_center_c),Size(radius,radius),0,-90,-270,Scalar(random_color_63),-1);
            blur(data_out,data_out,Size(13,13));

        }
    }
    if(!is_mask){
        for (int i = 0; i < data_out.rows; ++i) {
            for (int j = 0; j < data_out.cols; ++j) {
                int b=data_out.at<uchar>(i,j);
                float rat=pow((b/50.0),3)+1;
                data_in.at<Vec3b>(i,j)[0]=min(255,int(data_in.at<Vec3b>(i,j)[0]*rat));
                data_in.at<Vec3b>(i,j)[1]=min(255,int(data_in.at<Vec3b>(i,j)[1]*rat));
                data_in.at<Vec3b>(i,j)[2]=min(255,int(data_in.at<Vec3b>(i,j)[2]*rat));
            }
        }
        data_out = data_in.clone();
    }
}
//void transforms::DefectImpl::forward(cv::Mat &data_in, cv::Mat &data_out) {
//
////    Mat target;
//
//    if(is_mask){
//        data_out = Mat::zeros(data_in.rows,data_in.cols,CV_8UC1);
////        random_color = 255;
//    }else{
//        data_out = data_in;
////        random_color = (int)(rand()%200);
//    }
//    srand(myseed);
//    int h = data_in.rows;
//    int w = data_in.cols;
//    for(int i = 0;i<10;i++){
//        double m1=(double)(rand()%100)/100;
//        double m2=(double)(rand()%100)/100;
////        m1 = m1+i*0.2;
////        m2 = m2+i*0.2;
//        int random_color_num = rand()%200;
//        int random_type = (int)(rand()%4);
//        double size_ratio = min+m1*diff;
//        int random_color = (is_mask?255:random_color_num);
//        Scalar c(random_color);
////        cout<<"color: "<<random_color<<endl;
//
//
//        double size = size_ratio*( h>w?w:h)*0.3;
//        int x = (int)(m1*w);
//        int line_thickness = (int)(rand()%10)+1;
//        int circle_radius = (int)(rand()%10)+1;
//        double random_y_size = (double)(rand()%10)/10;
//
////        cout<<"x: "<<m1<<endl;
//        int y = (int)(m2*h);
//
////        circle(data_out, Point(x,y), 6, c,thickness);
//
//        if(random_type ==0){
//            circle(data_out, Point(x,y), circle_radius, c,thickness);
//
//        }else if(random_type == 1){
////            ellipse(data_out,Point(x, y),Size(size, size),30,0,360,c,thickness);
//
//        }else if(random_type == 2){
////            rectangle(data_out,Rect(x,y,x+size*0.05,y+size*0.02), c, thickness);
//
//        }else if(random_type == 3){
//            line(data_out, Point(x, y), Point(x+size, y+size*random_y_size), c, line_thickness);
//
//        }
//    }
////    std::cout<<"myseed: "<< transforms::DefectImpl::myseed<<std::endl;
////    if(is_mask)
////        myseed++;
////        myseed = myseed %1000;
////    data_out = data_in.clone();
////    imwrite("./1.png",data_out);
//
//}