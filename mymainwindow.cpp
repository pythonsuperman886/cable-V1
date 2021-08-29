//
// Created by explore on 2021/8/22.
//

#include "mymainwindow.h"
MyMainWindow::MyMainWindow(QWidget *parent):
        QMainWindow(parent),
        ui(new Ui::MainWindow),
        timer(new QTimer(this)),
        trainer(new Trainer),
        tester(new Testnet),
        textStream(new QTextStream(stdout)),
        qfile("../checkpoints/loss.txt"){

    ui->setupUi(this);
    ui->label_camera_image->setStyleSheet("QLabel{background:#000000;}");
    ui->label_test_camera_image->setStyleSheet("QLabel{background:#000000;}");
    ui->label_defect_result->setStyleSheet("QLabel{background:#000000;}");
    ui->label_train_result->setStyleSheet("QLabel{background:#000000;}");

//    ui->label_camera_image->setStyleSheet("QLabel{background:#000000;}");

    width_camera_label = ui->label_camera_image->width();
    height_camera_label= ui->label_camera_image->height();


    width_defect_label = ui->label_defect_result->width();
    height_defect_label = ui->label_defect_result->height();

    width_test_image_label = ui->label_test_camera_image->width();
    height_test_image_label = ui->label_test_camera_image->height();

    width_train_image_label = ui->label_train_result->width();
    height_train_image_label = ui->label_train_result->height();

    ui->pushButton_grab->setStyleSheet("background-color:rgb(0,200,0)");
    ui->pushButton_train_flag->setStyleSheet("background-color:rgb(0,200,0)");
    ui->pushButton_test->setStyleSheet("background-color:rgb(0,200,0)");

//    ui->lcdNumber_save_total_num->sema
    connect(timer,&QTimer::timeout,this,&MyMainWindow::time_out);
    connect(ui->lineEdit_data_path,&QLineEdit::editingFinished,this,&MyMainWindow::set_save_path);
    connect(ui->lineEdit_model_path,&QLineEdit::editingFinished,this,&MyMainWindow::set_model_path);

    connect(ui->pushButton_grab,&QPushButton::clicked,this,&MyMainWindow::change_save_flag);
    connect(ui->pushButton_train_flag,&QPushButton::clicked,this,&MyMainWindow::change_train_flag);
    connect(ui->pushButton_test,&QPushButton::clicked,this,&MyMainWindow::change_test_flag);
    connect(this,&MyMainWindow::train,this,&MyMainWindow::start_train);
    connect(this,&MyMainWindow::test,this,&MyMainWindow::init_test);
//    connect(ui->spinBox_defect_threshold, SIGNAL(valueChanged(int)),this,SLOT(change_defect_threshold(int)));
    ui->spinBox_defect_threshold->setValue(30);
    ui->spinBox_block_size->setValue(31);
    ui->spinBox_block_size->setSingleStep(2);
    ui->spinBox_block_size->setRange(3,127);
    timer->start(frequency);
//    (stdout);//绑定cout到标准输出

}
void MyMainWindow::time_out(){
    camera_mat = camera.readFrame();
//    cout<<"get frame"<<endl;
    if(!camera_mat.empty()){

        camera_qt = Mat2QImage(camera_mat).scaled(width_camera_label,height_camera_label);
        ui->label_camera_image->setPixmap(QPixmap::fromImage(camera_qt));

        if(Is_save){
            string path = save_path_image+"/"+to_string(frame_num)+".png";
            imwrite(path,camera_mat);
            ui->textEdit_save_image_lists->append(QString::fromStdString(path));
            save_data_nums++;
            ui->label_data_counts->setNum(save_data_nums);
        }
        if(Is_test){
            vector<Mat> real_defect_rectangle_image = tester->Test(camera_mat);
            defect_qt = Mat2QImage(real_defect_rectangle_image[1]).scaled(width_defect_label,height_defect_label);
            ui->label_defect_result->setPixmap(QPixmap::fromImage(defect_qt));

            test_camera_qt = Mat2QImage(real_defect_rectangle_image[0]).scaled(width_test_image_label,height_test_image_label);
            ui->label_test_camera_image->setPixmap(QPixmap::fromImage(test_camera_qt));

        }
        if(Is_train){

            QByteArray t = qfile.readAll();
            ui->textEdit_train_log->append(QString(t));
            train_result = Mat2QImage(trainer->combine).scaled(width_train_image_label,height_train_image_label);
            ui->label_train_result->setPixmap(QPixmap::fromImage(train_result));

//            cout.
//            cout.flush();
//            stdcout<<"train"<<endl;
//            textStream->flush();

//            ui->textEdit_train_log->append(textStream->readAll());
        }


        frame_num++;
    }else{
        cout<<"image empty!"<<endl;
    }
}

void MyMainWindow::set_save_path(){
    save_path_image= ui->lineEdit_data_path->text().toStdString();
    save_data_nums=0;
    cout<<save_path_image<<endl;
};

void MyMainWindow::set_model_path(){
    tester->model_path= ui->lineEdit_model_path->text().toStdString();

//    save_data_nums=0;
    cout<<tester->model_path<<endl;
};
void MyMainWindow::init_test(){
    tester->init();
};

void MyMainWindow::change_save_flag(){
    if(!Is_save){
        Is_save = true;
        ui->pushButton_grab->setStyleSheet("background-color:rgb(200,0,0)");


    }else{
        Is_save = false;
        ui->pushButton_grab->setStyleSheet("background-color:rgb(0,200,0)");

    }
}
void MyMainWindow::on_spinBox_defect_threshold_valueChanged(int i){
    int num = ui->spinBox_defect_threshold->value();
    tester->defect_threhold = num;
//    algorithm.set_threshold(num);
    cout<<"defect threshold: "<<num<<endl;
};

void MyMainWindow::start_train(){
    trainer->init(save_path_image);
//    thread t1()
//    file.open("../loss.txt");
    trainer->train();
}


void MyMainWindow::change_train_flag(){
    if(!Is_train){
        Is_train = true;
        qfile.open(QIODevice::ReadOnly | QIODevice::Text);

        ui->pushButton_train_flag->setStyleSheet("background-color:rgb(200,0,0)");
        emit train();


    }else{
        Is_train = false;
        trainer->stop_train();
        qfile.close();
        ui->pushButton_train_flag->setStyleSheet("background-color:rgb(0,200,0)");

    }
}

MyMainWindow::~MyMainWindow(){
//    delete ui;
    delete trainer;
    delete tester;

}

void MyMainWindow::change_test_flag() {
    if(!Is_test){
        Is_test = true;
        ui->pushButton_test->setStyleSheet("background-color:rgb(200,0,0)");
        emit test();


    }else{
        Is_test = false;
//        trainer->stop_train();
        ui->pushButton_test->setStyleSheet("background-color:rgb(0,200,0)");

    }
}

void MyMainWindow::on_spinBox_block_size_valueChanged(int i) {
    int num = ui->spinBox_block_size->value();
    tester->threshold_blocksize = num;
    //    algorithm.set_threshold(num);
    cout<<"threshold_blocksize: "<<num<<endl;
}
