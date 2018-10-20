#include"database.h"

void create_and_connect_db(QString db_name,QSqlDatabase* db)
{
    *db=QSqlDatabase::addDatabase("QSQLITE");
    db->setDatabaseName(db_name);
    qDebug()<<db->open();
}

void create_table()
{
    QSqlQuery query;

    query.exec("create table if not exists Query(queryid varchar primary key,roomid varchar,start_time varchar,end_time varchar,start_temp float,end_temp float,cost float)");
    query.finish();
    query.exec("create table if not exists Windspeed(queryid varchar,start_time varchar,end_time varchar,windspeed int)");
    query.finish();
    query.exec("create table if not exists ID(roomid varchar,idnum varchar)");
    query.finish();
}

void close_db(QSqlDatabase* db)
{
    db->close();
}


