#include <QApplication>
#include "mymainwindow.h"
#include "mysplashscreen.h"
#include "trainer.h"
#include "testnet.h"
#include <numeric>
int cable(int argc,char* argv[]){
    QApplication a(argc, argv);
    QPixmap pixmap("../icon/icon.png");//绑定一个图片
    MySplashScreen splash(pixmap,100);


    splash.show();
    //    QSplashScreen splash(pixmap);
//    splash.show();                            //显示启动画面
    a.processEvents();
    std::cout << "Hello, World!" << std::endl;
    MyMainWindow w;
    w.show();
    return a.exec();
}

Mat Max_deal_pic(string path){
//    string path = "/home/explore/data/28/18149.png";
    Mat image = imread(path);
    Mat gray_image;
    cvtColor(image,gray_image,CV_BGR2GRAY);
    Size kernel_size(3,3);
    Mat blur;
    GaussianBlur(gray_image,blur,kernel_size,19);
    Mat binary;
    cv::threshold(blur, binary, 40, 255, CV_THRESH_BINARY);/**/
    Canny(binary,binary,150,255);




    Mat element = getStructuringElement(MORPH_RECT,
                                        Size(17, 17));
    //闭运算
    Mat close_result;
    morphologyEx(binary, close_result, MORPH_CLOSE,element);


    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(close_result,contours,hierarchy,RETR_TREE,CHAIN_APPROX_SIMPLE,Point());
    cv::Rect stRect;

    vector<int> my_x;
    for (int i = 0; i < contours.size(); i++)
    {
//        cv::Rect stRect = cv::Rect(0, 0, 0, 0);
        int sfarea;
        stRect = cv::boundingRect(contours[i]);
//        cout<< stRect.x<<endl;
//        cout<< stRect.y<<endl;

//        if (stRect.area() < 2000) continue;
//        sRect = sfRect | stRect;
//        sfRect = cv::Rect(stRect);
            for(int j = 0 ;j<contours[i].size();j++){
                int x = contours[i][j].x;
                my_x.push_back(x);
            }
    }
    vector<int>::iterator p = min_element(my_x.begin(), my_x.end());

    int min_c = *p;

    vector<int>::iterator q = max_element(my_x.begin(), my_x.end());

    int max_c = *q;
//    cv::rectangle(image, Point (min_c, 20), Point (max_c, 20), cv::Scalar(0, 0, 255), 2, 8, 0);
    cv::rectangle(image, Point (min_c, 0), Point (min_c, image.rows), cv::Scalar(0, 0, 200), 2, 8, 0);
    cv::rectangle(image, Point (max_c, 0), Point (max_c, image.rows), cv::Scalar(0, 0, 200), 2, 8, 0);

    return image;

//    namedWindow("image",0);
//    imshow("image",image);
//    waitKey(0);
//    return 0;
}

Mat min_edge_out(string path,Mat max_image){
//    string path = "/home/explore/data/28/18149.png";
    Mat image = imread(path);
    Mat gray_image;
    cvtColor(image,gray_image,CV_BGR2GRAY);
    Size kernel_size(5,5);
    Mat blur;
    GaussianBlur(gray_image,blur,kernel_size,11);
    Mat binary;
    cv::threshold(blur, binary, 25, 255, CV_THRESH_BINARY);/**/


    Mat dilate_element = getStructuringElement(MORPH_RECT,
                                        Size(15, 15));
    //闭运算
    Mat dilate_result;
    dilate(binary,dilate_result,dilate_element);

    Mat close_element = getStructuringElement(MORPH_RECT,
                                        Size(17, 17));
    //闭运算
    Mat close_result;
    morphologyEx(dilate_result, close_result, MORPH_CLOSE,close_element);

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(close_result,contours,hierarchy,RETR_TREE,CHAIN_APPROX_SIMPLE);
    cv::Rect stRect;
    vector<int> my_x;
    for(int i = 0;i<contours.size();i++){
        for(int j = 0 ;j<contours[i].size();j++){
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
    cout<<"max: "<<max_per_c<<endl;
    cout<<"min: "<<min_rear_c<<endl;

//    rectangle(max_image,Point(max_per_c,10),Point(min_rear_c,10),cv::Scalar(0,255,0),3);
    cv::rectangle(max_image, Point (max_per_c, 0), Point (max_per_c, image.rows), cv::Scalar(0, 200, 0), 2, 8, 0);
    cv::rectangle(max_image, Point (min_rear_c, 0), Point (min_rear_c, image.rows), cv::Scalar(0, 200, 0), 2, 8, 0);


//    namedWindow("image",0);
//    imshow("image",image);
//    waitKey(0);
    return max_image;

//    return 0;

}

int main(){
    cable(0,nullptr);
//    min_edge_out();
//    string path ="/home/explore/data/28/18318.png";
//    Mat max_image = Max_deal_pic(path);
//    Mat result = min_edge_out(path,max_image);
//    namedWindow("image",0);
//    imshow("image",result);
//    waitKey(0);
//    return 0;

}
//int test() {
//    std::cout << "Hello, World!" << std::endl;
//    string image_path = "/home/explore/Data/origin/39739.png";
//    Mat image = imread(image_path,0);
//    string data_path = "/home/explore/project/mycpp/cable_defect_detect_qt/epoch_latest_gen.pth";
//    Testnet tester();
//
//    tester.Test(image);
//    return 0;
//}
