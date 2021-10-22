//
// Created by explore on 2021/9/17.
//

#ifndef CABLE_V1_MYDATABASE_H
#define CABLE_V1_MYDATABASE_H
#include <sqlite3.h>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <vector>
class MyDatabase {

public:
    MyDatabase();
    ~MyDatabase();
    void Insert_data(int pic,int defect_num,const std::vector<int>& diameter_nums);
    void query_all();

private:

    QSqlDatabase database;
    QSqlQuery sql_query;


};


#endif //CABLE_V1_MYDATABASE_H
