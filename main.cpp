#include <QApplication>
#include "mymainwindow.h"
#include "mysplashscreen.h"
#include "trainer.h"
#include "testnet.h"
int main(int argc,char* argv[]){
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
