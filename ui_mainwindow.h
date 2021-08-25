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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tab_camera;
    QLabel *label_camera_image;
    QPushButton *pushButton_grab;
    QLineEdit *lineEdit_data_path;
    QLabel *label_2;
    QTextEdit *textEdit_save_image_lists;
    QLabel *label_data_counts;
    QWidget *tab_train;
    QPushButton *pushButton_train_flag;
    QTextEdit *textEdit_train_log;
    QLabel *label_train_result;
    QWidget *tab_test;
    QPushButton *pushButton_test;
    QLabel *label_model_path;
    QLineEdit *lineEdit_model_path;
    QLabel *label_test_camera_image;
    QLabel *label_defect_result;
    QLabel *label_defect_threshold;
    QSpinBox *spinBox_defect_threshold;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1345, 951);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(-10, 10, 1301, 881));
        tab_camera = new QWidget();
        tab_camera->setObjectName(QStringLiteral("tab_camera"));
        label_camera_image = new QLabel(tab_camera);
        label_camera_image->setObjectName(QStringLiteral("label_camera_image"));
        label_camera_image->setGeometry(QRect(30, 40, 421, 631));
        pushButton_grab = new QPushButton(tab_camera);
        pushButton_grab->setObjectName(QStringLiteral("pushButton_grab"));
        pushButton_grab->setGeometry(QRect(950, 80, 161, 81));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        pushButton_grab->setFont(font);
        lineEdit_data_path = new QLineEdit(tab_camera);
        lineEdit_data_path->setObjectName(QStringLiteral("lineEdit_data_path"));
        lineEdit_data_path->setGeometry(QRect(600, 80, 331, 81));
        label_2 = new QLabel(tab_camera);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(480, 106, 111, 41));
        QFont font1;
        font1.setFamily(QStringLiteral("Ubuntu"));
        font1.setPointSize(15);
        font1.setBold(true);
        font1.setWeight(75);
        label_2->setFont(font1);
        textEdit_save_image_lists = new QTextEdit(tab_camera);
        textEdit_save_image_lists->setObjectName(QStringLiteral("textEdit_save_image_lists"));
        textEdit_save_image_lists->setGeometry(QRect(490, 200, 641, 491));
        label_data_counts = new QLabel(tab_camera);
        label_data_counts->setObjectName(QStringLiteral("label_data_counts"));
        label_data_counts->setGeometry(QRect(1140, 210, 81, 51));
        QFont font2;
        font2.setPointSize(24);
        font2.setBold(true);
        font2.setWeight(75);
        label_data_counts->setFont(font2);
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
        QFont font3;
        font3.setPointSize(16);
        font3.setBold(false);
        font3.setWeight(50);
        label_model_path->setFont(font3);
        lineEdit_model_path = new QLineEdit(tab_test);
        lineEdit_model_path->setObjectName(QStringLiteral("lineEdit_model_path"));
        lineEdit_model_path->setGeometry(QRect(170, 10, 311, 41));
        label_test_camera_image = new QLabel(tab_test);
        label_test_camera_image->setObjectName(QStringLiteral("label_test_camera_image"));
        label_test_camera_image->setGeometry(QRect(30, 100, 461, 641));
        label_defect_result = new QLabel(tab_test);
        label_defect_result->setObjectName(QStringLiteral("label_defect_result"));
        label_defect_result->setGeometry(QRect(680, 100, 461, 641));
        label_defect_threshold = new QLabel(tab_test);
        label_defect_threshold->setObjectName(QStringLiteral("label_defect_threshold"));
        label_defect_threshold->setGeometry(QRect(880, 20, 221, 31));
        QFont font4;
        font4.setPointSize(15);
        font4.setBold(true);
        font4.setWeight(75);
        label_defect_threshold->setFont(font4);
        spinBox_defect_threshold = new QSpinBox(tab_test);
        spinBox_defect_threshold->setObjectName(QStringLiteral("spinBox_defect_threshold"));
        spinBox_defect_threshold->setGeometry(QRect(1120, 10, 81, 51));
        QFont font5;
        font5.setPointSize(15);
        font5.setBold(true);
        font5.setUnderline(false);
        font5.setWeight(75);
        font5.setStrikeOut(false);
        spinBox_defect_threshold->setFont(font5);
        tabWidget->addTab(tab_test, QString());
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1345, 20));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label_camera_image->setText(QApplication::translate("MainWindow", "Camera Image", Q_NULLPTR));
        pushButton_grab->setText(QApplication::translate("MainWindow", "Grab", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Save Path :", Q_NULLPTR));
        label_data_counts->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_camera), QApplication::translate("MainWindow", "Camera", Q_NULLPTR));
        pushButton_train_flag->setText(QApplication::translate("MainWindow", "Train", Q_NULLPTR));
        label_train_result->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_train), QApplication::translate("MainWindow", "Train", Q_NULLPTR));
        pushButton_test->setText(QApplication::translate("MainWindow", "Test", Q_NULLPTR));
        label_model_path->setText(QApplication::translate("MainWindow", "Model Path:", Q_NULLPTR));
        label_test_camera_image->setText(QApplication::translate("MainWindow", "camera image", Q_NULLPTR));
        label_defect_result->setText(QApplication::translate("MainWindow", "defect image", Q_NULLPTR));
        label_defect_threshold->setText(QApplication::translate("MainWindow", "Defect Threshold:", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_test), QApplication::translate("MainWindow", "Test", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
