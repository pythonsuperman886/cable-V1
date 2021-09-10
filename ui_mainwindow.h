/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include "QtCharts"
#include "mylabel.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tab_camera;
    MyLabel *label_camera_image;
    QPushButton *pushButton_grab;
    QLineEdit *lineEdit_data_path;
    QLabel *label_save_path;
    QTextEdit *textEdit_save_image_lists;
    QLabel *label_data_counts;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QRadioButton *radioButton_blur;
    QRadioButton *radioButton_gaussianBlur;
    QRadioButton *radioButton_bilateraFilter;
    QRadioButton *radioButton_medianBlur;
    QRadioButton *radioButton_blur_none;
    QSpinBox *spinBox_blur_num;
    QWidget *tab_train;
    QPushButton *pushButton_train_flag;
    QTextEdit *textEdit_train_log;
    QLabel *label_train_result;
    QLabel *label_batch_size;
    QSpinBox *spinBox_batch_size;
    QLCDNumber *lcdNumber_train_time;
    QWidget *tab_test;
    QPushButton *pushButton_test;
    QLabel *label_model_path;
    QLineEdit *lineEdit_model_path;
    QLabel *label_test_camera_image;
    QLabel *label_defect_result;
    QLabel *label_defect_threshold;
    QSpinBox *spinBox_defect_threshold;
    QLabel *label_block_size;
    QSpinBox *spinBox_block_size;
    QChartView *line_chart_view;
    QTableView *tableView_all_info;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QButtonGroup *buttonGroup_blur;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1790, 1254);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(30, 10, 1741, 1201));
        tab_camera = new QWidget();
        tab_camera->setObjectName(QStringLiteral("tab_camera"));
        label_camera_image = new MyLabel(tab_camera);
        label_camera_image->setObjectName(QStringLiteral("label_camera_image"));
        label_camera_image->setGeometry(QRect(40, 220, 640, 480));
        pushButton_grab = new QPushButton(tab_camera);
        pushButton_grab->setObjectName(QStringLiteral("pushButton_grab"));
        pushButton_grab->setGeometry(QRect(1200, 100, 161, 81));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        pushButton_grab->setFont(font);
        lineEdit_data_path = new QLineEdit(tab_camera);
        lineEdit_data_path->setObjectName(QStringLiteral("lineEdit_data_path"));
        lineEdit_data_path->setGeometry(QRect(850, 100, 331, 81));
        label_save_path = new QLabel(tab_camera);
        label_save_path->setObjectName(QStringLiteral("label_save_path"));
        label_save_path->setGeometry(QRect(720, 110, 111, 41));
        QFont font1;
        font1.setFamily(QStringLiteral("Ubuntu"));
        font1.setPointSize(15);
        font1.setBold(true);
        font1.setWeight(75);
        label_save_path->setFont(font1);
        textEdit_save_image_lists = new QTextEdit(tab_camera);
        textEdit_save_image_lists->setObjectName(QStringLiteral("textEdit_save_image_lists"));
        textEdit_save_image_lists->setGeometry(QRect(730, 210, 631, 471));
        label_data_counts = new QLabel(tab_camera);
        label_data_counts->setObjectName(QStringLiteral("label_data_counts"));
        label_data_counts->setGeometry(QRect(1370, 210, 81, 51));
        QFont font2;
        font2.setPointSize(24);
        font2.setBold(true);
        font2.setWeight(75);
        label_data_counts->setFont(font2);
        gridLayoutWidget = new QWidget(tab_camera);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(20, 760, 340, 112));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        radioButton_blur = new QRadioButton(gridLayoutWidget);
        buttonGroup_blur = new QButtonGroup(MainWindow);
        buttonGroup_blur->setObjectName(QStringLiteral("buttonGroup_blur"));
        buttonGroup_blur->addButton(radioButton_blur);
        radioButton_blur->setObjectName(QStringLiteral("radioButton_blur"));
        QFont font3;
        font3.setBold(true);
        font3.setWeight(75);
        radioButton_blur->setFont(font3);
        radioButton_blur->setContextMenuPolicy(Qt::ActionsContextMenu);

        gridLayout->addWidget(radioButton_blur, 0, 0, 1, 1);

        radioButton_gaussianBlur = new QRadioButton(gridLayoutWidget);
        buttonGroup_blur->addButton(radioButton_gaussianBlur);
        radioButton_gaussianBlur->setObjectName(QStringLiteral("radioButton_gaussianBlur"));
        radioButton_gaussianBlur->setFont(font3);

        gridLayout->addWidget(radioButton_gaussianBlur, 0, 1, 1, 1);

        radioButton_bilateraFilter = new QRadioButton(gridLayoutWidget);
        buttonGroup_blur->addButton(radioButton_bilateraFilter);
        radioButton_bilateraFilter->setObjectName(QStringLiteral("radioButton_bilateraFilter"));
        radioButton_bilateraFilter->setFont(font3);
        radioButton_bilateraFilter->setChecked(true);

        gridLayout->addWidget(radioButton_bilateraFilter, 2, 0, 1, 1);

        radioButton_medianBlur = new QRadioButton(gridLayoutWidget);
        buttonGroup_blur->addButton(radioButton_medianBlur);
        radioButton_medianBlur->setObjectName(QStringLiteral("radioButton_medianBlur"));
        radioButton_medianBlur->setFont(font3);
        radioButton_medianBlur->setContextMenuPolicy(Qt::NoContextMenu);

        gridLayout->addWidget(radioButton_medianBlur, 2, 1, 1, 1);

        radioButton_blur_none = new QRadioButton(gridLayoutWidget);
        buttonGroup_blur->addButton(radioButton_blur_none);
        radioButton_blur_none->setObjectName(QStringLiteral("radioButton_blur_none"));
        radioButton_blur_none->setFont(font3);

        gridLayout->addWidget(radioButton_blur_none, 3, 0, 1, 1);

        spinBox_blur_num = new QSpinBox(gridLayoutWidget);
        spinBox_blur_num->setObjectName(QStringLiteral("spinBox_blur_num"));
        QFont font4;
        font4.setPointSize(15);
        font4.setBold(true);
        font4.setWeight(75);
        spinBox_blur_num->setFont(font4);

        gridLayout->addWidget(spinBox_blur_num, 3, 1, 1, 1);

        tabWidget->addTab(tab_camera, QString());
        tab_train = new QWidget();
        tab_train->setObjectName(QStringLiteral("tab_train"));
        pushButton_train_flag = new QPushButton(tab_train);
        pushButton_train_flag->setObjectName(QStringLiteral("pushButton_train_flag"));
        pushButton_train_flag->setGeometry(QRect(50, 70, 161, 71));
        pushButton_train_flag->setFont(font);
        textEdit_train_log = new QTextEdit(tab_train);
        textEdit_train_log->setObjectName(QStringLiteral("textEdit_train_log"));
        textEdit_train_log->setGeometry(QRect(50, 160, 611, 661));
        label_train_result = new QLabel(tab_train);
        label_train_result->setObjectName(QStringLiteral("label_train_result"));
        label_train_result->setGeometry(QRect(690, 170, 581, 241));
        label_batch_size = new QLabel(tab_train);
        label_batch_size->setObjectName(QStringLiteral("label_batch_size"));
        label_batch_size->setGeometry(QRect(260, 86, 131, 31));
        QFont font5;
        font5.setPointSize(17);
        font5.setBold(true);
        font5.setWeight(75);
        label_batch_size->setFont(font5);
        spinBox_batch_size = new QSpinBox(tab_train);
        spinBox_batch_size->setObjectName(QStringLiteral("spinBox_batch_size"));
        spinBox_batch_size->setGeometry(QRect(390, 70, 111, 61));
        QFont font6;
        font6.setPointSize(16);
        font6.setBold(true);
        font6.setWeight(75);
        spinBox_batch_size->setFont(font6);
        lcdNumber_train_time = new QLCDNumber(tab_train);
        lcdNumber_train_time->setObjectName(QStringLiteral("lcdNumber_train_time"));
        lcdNumber_train_time->setGeometry(QRect(270, 830, 381, 101));
        QFont font7;
        font7.setPointSize(20);
        font7.setBold(false);
        font7.setItalic(false);
        font7.setWeight(50);
        lcdNumber_train_time->setFont(font7);
        tabWidget->addTab(tab_train, QString());
        tab_test = new QWidget();
        tab_test->setObjectName(QStringLiteral("tab_test"));
        pushButton_test = new QPushButton(tab_test);
        pushButton_test->setObjectName(QStringLiteral("pushButton_test"));
        pushButton_test->setGeometry(QRect(520, 0, 121, 71));
        pushButton_test->setFont(font);
        label_model_path = new QLabel(tab_test);
        label_model_path->setObjectName(QStringLiteral("label_model_path"));
        label_model_path->setGeometry(QRect(30, 10, 121, 51));
        QFont font8;
        font8.setPointSize(16);
        font8.setBold(false);
        font8.setWeight(50);
        label_model_path->setFont(font8);
        lineEdit_model_path = new QLineEdit(tab_test);
        lineEdit_model_path->setObjectName(QStringLiteral("lineEdit_model_path"));
        lineEdit_model_path->setGeometry(QRect(170, 10, 311, 41));
        label_test_camera_image = new QLabel(tab_test);
        label_test_camera_image->setObjectName(QStringLiteral("label_test_camera_image"));
        label_test_camera_image->setGeometry(QRect(30, 100, 640, 480));
        label_defect_result = new QLabel(tab_test);
        label_defect_result->setObjectName(QStringLiteral("label_defect_result"));
        label_defect_result->setGeometry(QRect(710, 100, 640, 480));
        label_defect_threshold = new QLabel(tab_test);
        label_defect_threshold->setObjectName(QStringLiteral("label_defect_threshold"));
        label_defect_threshold->setGeometry(QRect(670, 20, 221, 31));
        label_defect_threshold->setFont(font4);
        spinBox_defect_threshold = new QSpinBox(tab_test);
        spinBox_defect_threshold->setObjectName(QStringLiteral("spinBox_defect_threshold"));
        spinBox_defect_threshold->setGeometry(QRect(860, 10, 81, 51));
        QFont font9;
        font9.setPointSize(15);
        font9.setBold(true);
        font9.setUnderline(false);
        font9.setWeight(75);
        font9.setStrikeOut(false);
        spinBox_defect_threshold->setFont(font9);
        label_block_size = new QLabel(tab_test);
        label_block_size->setObjectName(QStringLiteral("label_block_size"));
        label_block_size->setGeometry(QRect(970, 30, 121, 17));
        label_block_size->setFont(font4);
        spinBox_block_size = new QSpinBox(tab_test);
        spinBox_block_size->setObjectName(QStringLiteral("spinBox_block_size"));
        spinBox_block_size->setGeometry(QRect(1090, 10, 91, 51));
        spinBox_block_size->setFont(font4);
        line_chart_view = new QChartView(tab_test);
        line_chart_view->setObjectName(QStringLiteral("line_chart_view"));
        line_chart_view->setGeometry(QRect(15, 581, 871, 411));
        tableView_all_info = new QTableView(tab_test);
        tableView_all_info->setObjectName(QStringLiteral("tableView_all_info"));
        tableView_all_info->setGeometry(QRect(930, 580, 551, 411));
        tabWidget->addTab(tab_test, QString());
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1790, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label_camera_image->setText(QApplication::translate("MainWindow", "Camera Image", Q_NULLPTR));
        pushButton_grab->setText(QApplication::translate("MainWindow", "Grab", Q_NULLPTR));
        label_save_path->setText(QApplication::translate("MainWindow", "Save Path :", Q_NULLPTR));
        label_data_counts->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        radioButton_blur->setText(QApplication::translate("MainWindow", "blur", Q_NULLPTR));
        radioButton_gaussianBlur->setText(QApplication::translate("MainWindow", "GaussianBlur", Q_NULLPTR));
        radioButton_bilateraFilter->setText(QApplication::translate("MainWindow", "bilateralFilter", Q_NULLPTR));
        radioButton_medianBlur->setText(QApplication::translate("MainWindow", "medianBlur", Q_NULLPTR));
        radioButton_blur_none->setText(QApplication::translate("MainWindow", "none", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_camera), QApplication::translate("MainWindow", "Camera", Q_NULLPTR));
        pushButton_train_flag->setText(QApplication::translate("MainWindow", "Train", Q_NULLPTR));
        label_train_result->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        label_batch_size->setText(QApplication::translate("MainWindow", "Batch Size:", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_train), QApplication::translate("MainWindow", "Train", Q_NULLPTR));
        pushButton_test->setText(QApplication::translate("MainWindow", "Test", Q_NULLPTR));
        label_model_path->setText(QApplication::translate("MainWindow", "Model Path:", Q_NULLPTR));
        label_test_camera_image->setText(QApplication::translate("MainWindow", "camera image", Q_NULLPTR));
        label_defect_result->setText(QApplication::translate("MainWindow", "defect image", Q_NULLPTR));
        label_defect_threshold->setText(QApplication::translate("MainWindow", "Defect Threshold:", Q_NULLPTR));
        label_block_size->setText(QApplication::translate("MainWindow", "Block Size:", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_test), QApplication::translate("MainWindow", "Test", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
