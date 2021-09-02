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
    set_group_id();
    ui->label_camera_image->setStyleSheet("QLabel{background:#000000;}");
    ui->label_test_camera_image->setStyleSheet("QLabel{background:#000000;}");
    ui->label_defect_result->setStyleSheet("QLabel{background:#000000;}");
    ui->label_train_result->setStyleSheet("QLabel{background:#000000;}");




    ui->spinBox_blur_num->setRange(1, 71);//设置范围
    ui->spinBox_blur_num->setValue(1); //设置当前值
    ui->spinBox_blur_num->setSingleStep(2);
    int val_2 = ui->spinBox_blur_num->value(); //获取值
//    ui->label_preprocess_blur_value_num->setText(QString::number(val_2));//把获取到的值显示在文本框

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

    connect(ui->buttonGroup_blur, SIGNAL(buttonToggled(int, bool)), this, SLOT(on_buttonGroup_blur_toggled(int, bool)));

//    connect(this,&MyMainWindow::test,this,&MyMainWindow::init_test);



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
        preprocess_mat = preprocess.series_process(camera_mat);

        preprocess_qt = Mat2QImage(preprocess_mat).scaled(width_camera_label,height_camera_label);
        ui->label_camera_image->setPixmap(QPixmap::fromImage(preprocess_qt));
        re_rect_mat = preprocess_mat.clone();
        if(ui->label_camera_image->Is_finish){

            Rect rect = get_rect(preprocess_mat.cols,preprocess_mat.rows);

            re_rect_mat = preprocess.rect_image(preprocess_mat,rect);
            tester->rect_image_width = re_rect_mat.cols;
            tester->rect_image_height = re_rect_mat.rows;
        }



        if(Is_save){
            string path = save_path_image+"/"+to_string(frame_num)+".png";
            imwrite(path,re_rect_mat);
            ui->textEdit_save_image_lists->append(QString::fromStdString(path));
            save_data_nums++;
            ui->label_data_counts->setNum(save_data_nums);
        }
        if(Is_test){
            vector<Rect> rect_lists;
            Mat net_out = tester->Test(re_rect_mat,rect_lists);
            Mat camera_mat_test = camera_mat.clone();
            camera_mat_test = tester->rectangle_cable_defect(camera_mat_test,rect_lists);
            net_out = tester->rectangle_cable_defect(net_out,rect_lists);

            vector<int> diameter_nums = get_diameter_nums(camera_mat);
            draw_line_diameter(camera_mat_test,diameter_nums);

//            vector<Mat> real_defect_rectangle_image = tester->Test(re_rect_mat);




            defect_qt = Mat2QImage(net_out).scaled(width_defect_label,height_defect_label);
            ui->label_defect_result->setPixmap(QPixmap::fromImage(defect_qt));

            test_camera_qt = Mat2QImage(camera_mat_test).scaled(width_test_image_label,height_test_image_label);
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
Rect MyMainWindow::get_rect(int w,int h){
    QPoint p1 = ui->label_camera_image->getStartPoint();
    QPoint p2 = ui->label_camera_image->getEndPoint();
    int x1 = p1.x();
    int x2 = p2.x();

    tester->copy_border_left = x1;
    tester->copy_border_right = w - x2;


    Rect rect(x1,0,x2-x1,h);
    cout<<"x1: "<<x1<<endl;
    cout<<"x2: "<<x2<<endl;

    return rect;
}

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

void MyMainWindow::on_buttonGroup_blur_toggled(int id,bool type){
    preprocess.blur_type = ui->buttonGroup_blur->checkedId();
    cout<<" blur id :"<<ui->buttonGroup_blur->checkedId()<<endl;
}

void MyMainWindow::on_spinBox_defect_threshold_valueChanged(int i){
    int num = ui->spinBox_defect_threshold->value();
    tester->defect_threhold = num;
//    algorithm.set_threshold(num);
    cout<<"defect threshold: "<<num<<endl;
}

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

void MyMainWindow::on_spinBox_blur_num_valueChanged(int i) {
    int num = ui->spinBox_blur_num->value();
    preprocess.set_blur_parameters(num);
    cout<<"blur size: "<<num<<endl;
//    ui->label_preprocess_blur_value_num->setText(QString::number(num));

}

void MyMainWindow::set_group_id() {
    ui->buttonGroup_blur->setId(ui->radioButton_blur,0);
    ui->buttonGroup_blur->setId(ui->radioButton_gaussianBlur,1);
    ui->buttonGroup_blur->setId(ui->radioButton_bilateraFilter,2);
    ui->buttonGroup_blur->setId(ui->radioButton_medianBlur,3);
    ui->buttonGroup_blur->setId(ui->radioButton_blur_none,4);
}
