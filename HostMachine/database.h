#ifndef DATABASE_H
#define DATABASE_H
#include <QString>
#include <QSql>
#include <QSqlDriver>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>


void create_and_connect_db(QString db_name,QSqlDatabase* db);
void create_table();
void close_db(QSqlDatabase* db);


#endif // DATABASE_H
