//
// Created by explore on 2021/8/21.
//

#include "testnet.h"

#include <utility>
Testnet::Testnet():
            cuda_available (torch::cuda::is_available() ),
            device(Device(cuda_available ? torch::kCUDA : torch::kCPU)),
            G(UNet_Generator(1,1)),rectangle_color(255){

}
void Testnet::init(){
    cout<<"load model..."<<endl;
//    model_path=std::move(model_path_);
    torch::load(G, model_path);
    G->to(device);
    G->eval();
};
vector<Mat> Testnet::rectangle_cable_defect( Mat& fake_image,Mat &real_image) {

    cv::Mat   labels,  stats,centroids;

    cv::adaptiveThreshold(fake_image,fake_image,255,0,THRESH_BINARY,threshold_blocksize,0);

    Mat rectangle_image_fake = fake_image.clone();
    Mat rectangle_image_real = real_image.clone();




    cvtColor(rectangle_image_real,rectangle_image_real,CV_GRAY2BGR);
    cvtColor(rectangle_image_fake,rectangle_image_fake,CV_GRAY2BGR);
    int nccomps = cv::connectedComponentsWithStats (
            fake_image, labels,
            stats, centroids
            );
    for( int y = 0; y < fake_image.rows; y++ )
        for( int x = 0; x < fake_image.cols; x++ )
        {
            int label = labels.at<int>(y, x);
            CV_Assert(0 <= label && label <= nccomps);
            if( stats.at<int>(label, cv::CC_STAT_AREA) >defect_threhold && label !=0){
                Is_save = true;
                int x_l = stats.at<int>(label, cv::CC_STAT_LEFT);
                int y_l = stats.at<int>(label, cv::CC_STAT_TOP);
                int w = stats.at<int>(label, cv::CC_STAT_WIDTH);
                int h = stats.at<int>(label, cv::CC_STAT_HEIGHT);
                rectangle(rectangle_image_fake,Point(x_l,y_l),Point(x_l+w,y_l+h),cv::Scalar(0,0,200));
                rectangle(rectangle_image_real,Point(x_l,y_l),Point(x_l+w,y_l+h), cv::Scalar(0,0,200));
//                cv::imwrite("../checkpoints/test_results/defect"+to_string(test_num)+".jpg",rectangle_image_real);
            }
        }
    vector<Mat> rectangle_images={rectangle_image_real,
                                  rectangle_image_fake};

        return rectangle_images;
        //        cv::imwrite("fake"+to_string(i)+".jpg",imgbin);
}
vector<Rect> Testnet::get_defect_rect_list( Mat fake_image,Mat &resize_to_origin_image_net_out) {

    cv::Mat labels,  stats,centroids;
    Mat border_image_to_origin;
    Mat resize_image_to_rect;

    cv::adaptiveThreshold(fake_image,fake_image,255,0,THRESH_BINARY,threshold_blocksize,0);
//    cv::threshold(fake_image, fake_image, 25, 255, CV_THRESH_BINARY);

    resize(fake_image,resize_image_to_rect,Size(rect_image_width,rect_image_height));


    copyMakeBorder(resize_image_to_rect,border_image_to_origin,0,0,copy_border_left,copy_border_right,BORDER_CONSTANT,cv::Scalar(0));

//    Mat rectangle_image_fake = fake_image.clone();
//    Mat rectangle_image_real = real_image.clone();
    resize_to_origin_image_net_out = border_image_to_origin;

    vector<Rect> rect_lists;

    double ratio_w = double(border_image_to_origin.cols)/double(fake_image.cols);
    double ratio_h = double(border_image_to_origin.rows)/double(fake_image.rows);
//    double ratio = ratio_w/ratio_h;
    cout<<"ratio_w: "<<ratio_w<<endl;
    cout<<"ratio_h: "<<ratio_h<<endl;
//    cout<<"ratio: "<<ratio<<endl;
//    cout<<"ratio_w: "<<ratio_w<<endl;

//    cvtColor(rectangle_image_real,rectangle_image_real,CV_GRAY2BGR);
//    cvtColor(rectangle_image_fake,rectangle_image_fake,CV_GRAY2BGR);
    int nccomps = cv::connectedComponentsWithStats (
            fake_image, labels,
            stats, centroids
            );
    for( int y = 0; y < fake_image.rows; y++ )
        for( int x = 0; x < fake_image.cols; x++ )
        {
            int label = labels.at<int>(y, x);
            CV_Assert(0 <= label && label <= nccomps);
            if( stats.at<int>(label, cv::CC_STAT_AREA) >defect_threhold && label !=0){
                Is_save = true;
                int x_l = double(stats.at<int>(label, cv::CC_STAT_LEFT)*ratio_w);
                int y_l = double(stats.at<int>(label, cv::CC_STAT_TOP)*ratio_h);
                int w = double(stats.at<int>(label, cv::CC_STAT_WIDTH)*ratio_w);
                int h = double(stats.at<int>(label, cv::CC_STAT_HEIGHT)*ratio_h);
                rect_lists.emplace_back(x_l,y_l,w,h);
//                rectangle(rectangle_image_fake,Point(x_l,y_l),Point(x_l+w,y_l+h),cv::Scalar(0,0,200));
//                rectangle(rectangle_image_real,Point(x_l,y_l),Point(x_l+w,y_l+h), cv::Scalar(0,0,200));
                //                cv::imwrite("../checkpoints/test_results/defect"+to_string(test_num)+".jpg",rectangle_image_real);
            }
        }

//    vector<Mat> rectangle_images={rectangle_image_real,
//                                  rectangle_image_fake};
//
    return rect_lists;
        //        cv::imwrite("fake"+to_string(i)+".jpg",imgbin);
}

Mat Testnet::rectangle_cable_defect(Mat fake_image,const vector<Rect>& lists) {

    if(fake_image.channels()==1){
        cvtColor(fake_image,fake_image,CV_GRAY2BGR);

    }
    tm.reset();
    tm.start();

    for(const auto& Rect:lists){
        rectangle(fake_image,Rect, cv::Scalar(0,0,200),3);
    }
    tm.stop();
    cout<<"list size: "<<lists.size()<<endl;
    cout<<"rectangle forward: "<<tm.getTimeMilli()<<endl;

    return fake_image;

}

Mat Testnet::Test(const Mat& image,vector<Rect> &lists){

    Mat resize_image;
    resize(image,resize_image,Size(128,128));
    //    TickMeter tm;
    //    cout<<"forward..."<<endl;
    //    torch::AutoGradMode enable_grad(false);
    Is_save = false;
    Mat out;
    //    for(int i =1;i<15;i++){
    tm.reset();
    tm.start();
    Tensor input = Mat2Tensor(resize_image);
    input = input.to(device);

    Tensor fake_B;
    fake_B = G->forward(input);
    out = Tensor2Mat(fake_B);
    Mat out2origin_size;
    lists = get_defect_rect_list(out,out2origin_size);
    cout<<"lists size: "<<lists.size()<<endl;

//    vector<Mat> rectangle_mat = rectangle_cable_defect(out,resize_image);
    tm.stop();
    cout<<"time forward: "<<tm.getTimeMilli()<<endl;
    //    cout<<" grade "<<fake_B.requires_grad()<<endl;


    //    vector<Mat> ouputs = {
    //            rectangle_mat[0],rectangle_mat[1]
    //    };

//    Mat combine;
//    hconcat(rectangle_mat,combine);
//    if(Is_save)
//        imwrite("../checkpoints/test_results/"+to_string(test_num)+".png",combine.clone());

    //    }
    //    fake_B = fake_B.mul(255).add(0.5).clamp(0, 255).permute({0,3,1,2}).to(torch::kU8);
    //    fake_B = fake_B.to(torch::kCPU);
    //    cv::Mat imgbin(cv::Size(image_resize_num, image_resize_num), CV_8U, fake_B.data_ptr());
    test_num++;
    return out2origin_size;

}

vector<Mat> Testnet::Test(const Mat& image){

    Mat resize_image;
    resize(image,resize_image,Size(128,128));
//    TickMeter tm;
//    cout<<"forward..."<<endl;
//    torch::AutoGradMode enable_grad(false);
    Is_save = false;
    Mat out;
//    for(int i =1;i<15;i++){
    tm.reset();
    tm.start();
    Tensor input = Mat2Tensor(resize_image);
    input = input.to(device);

    Tensor fake_B;
    fake_B = G->forward(input);
    out = Tensor2Mat(fake_B);
    vector<Mat> rectangle_mat = rectangle_cable_defect(out,resize_image);
    tm.stop();
    cout<<"time forward: "<<tm.getTimeMilli()<<endl;
//    cout<<" grade "<<fake_B.requires_grad()<<endl;


//    vector<Mat> ouputs = {
//            rectangle_mat[0],rectangle_mat[1]
//    };

    Mat combine;
    hconcat(rectangle_mat,combine);
    if(Is_save)
        imwrite("../checkpoints/test_results/"+to_string(test_num)+".png",combine.clone());

//    }
//    fake_B = fake_B.mul(255).add(0.5).clamp(0, 255).permute({0,3,1,2}).to(torch::kU8);
//    fake_B = fake_B.to(torch::kCPU);
//    cv::Mat imgbin(cv::Size(image_resize_num, image_resize_num), CV_8U, fake_B.data_ptr());
    test_num++;
    return rectangle_mat;

}

Testnet::~Testnet() {
//    delete G;

}


