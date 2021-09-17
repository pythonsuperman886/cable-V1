//
// Created by explore on 2021/9/17.
//

#include <iostream>
#include "mydatabase.h"
MyDatabase::MyDatabase(){
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("../checkpoints/MyDataBase.db");
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    else
    {
        qDebug() << "Succeed to connect database." ;
    }

    //创建表格
    sql_query = QSqlQuery(database);

    sql_query.prepare( "CREATE TABLE IF NOT EXISTS cable_defect_info (id int, defect_num int, min_diameter int, max_diameter int)" );
    if( !sql_query.exec())
        qDebug() << sql_query.lastError();
    else
        qDebug() << "Table created!";


    if(!sql_query.exec("INSERT INTO cable_defect_info VALUES(1, 2, 3,4)"))
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "inserted Li!";
    }

}

void MyDatabase::Insert_data(int pic,int defect_num,const std::vector<int>& diameter_nums){
    int max_width = -1;
    int min_width = -1;
    if(diameter_nums[0]!=-1&&diameter_nums[1]!=-1&&diameter_nums[2]!=-1&&diameter_nums[3]!=-1){

        max_width = diameter_nums[1]- diameter_nums[0];
        min_width = diameter_nums[3]- diameter_nums[2];

    }


    sql_query.prepare("INSERT INTO cable_defect_info(id,defect_num,min_diameter,max_diameter) VALUES(:id,:defect_num,:min_diameter,:max_diameter)");
    sql_query.bindValue(":id",pic);
    sql_query.bindValue(":defect_num",defect_num);
    sql_query.bindValue(":min_diameter",min_width);
    sql_query.bindValue(":max_diameter",max_width);



//    QString  mess = QString("(%1  %2 %3 %4)").arg(pic).arg(defect_num).arg(min_width).arg(max_width);
//    QString  insert = "INSERT INTO cable_defect_info VALUES ";
//    sql_query.prepare(mess+insert);
//    sql_query.prepare( "INSERT INTO names (id, firstname, lastname) VALUES (9, 'Ralph', 'Roe')" );
//    sql_query.bindValue((int) ":id", static_cast<QFlag>(pic));
//    sql_query.bindValue((int) ":defect_num", static_cast<QFlag>(defect_num));
//    sql_query.bindValue((int) ":min_diameter", static_cast<QFlag>(min_width));
//    sql_query.bindValue((int) ":max_diameter", static_cast<QFlag>(max_width));



    if(!sql_query.exec())
    {
        qDebug() <<sql_query.lastError();
    }
    else
    {
        qDebug()<<"插入记录成功";
    }

}

MyDatabase::~MyDatabase(){
    database.close();
}

void MyDatabase::query_all() {
    QString sql = "select * from cable_defect_info";
    if(!sql_query.exec(sql))
    {
        qDebug()<<sql_query.lastError();
        std::cout<<"query error"<<endl;
    }else{
//        while(sql_query.next()){
//            //取出并打印值
//            qDebug() << sql_query.value("id").toInt()
//            << sql_query.value("defect_num").toInt()
//            << sql_query.value("min_diameter").toInt();
//        }
        std::cout<<"query succeed"<<std::endl;
    }
}
