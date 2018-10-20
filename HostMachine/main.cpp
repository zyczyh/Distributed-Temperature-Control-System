#include "mainwindow.h"
#include <QApplication>
#include <QTcpSocket>
#include "multithread_server.h"
#include "multithread.h"
#include "client.h"
#include "database.h"
#include <QtSql>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSqlDatabase db;

    db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("air_conditioner.db");
    if(!db.open())
    {
    qDebug()<<db.lastError();
    qFatal("failed to connect.") ;
    }
    else
    {
        QSqlQuery query;
        query.prepare("create table if not exists Query(queryid varchar primary key,roomid varchar,start_time varchar,end_time varchar,start_temp float,end_temp float,cost float)");
        if(!query.exec())
        {
        qDebug()<<query.lastError();
        }
        else
        {
        qDebug()<<"table created!";
        }
        query.finish();
        query.prepare("create table if not exists Windspeed(queryid varchar,start_time varchar,end_time varchar,windspeed int)");
        if(!query.exec())
        {
        qDebug()<<query.lastError();
        }
        else
        {
        qDebug()<<"table created!";
        }
        query.finish();
        query.prepare("create table if not exists ID(roomid varchar,idnum varchar)");
        if(!query.exec())
        {
        qDebug()<<query.lastError();
        }
        else
        {
        qDebug()<<"table created!";
        }
        query.finish();
        query.prepare("create table if not exists Shutdown(roomid varchar,time varchar)");
        if(!query.exec())
        {
        qDebug()<<query.lastError();
        }
        else
        {
        qDebug()<<"table created!";
        }
        query.finish();
    }
    MainWindow window;
    window.show();
    return a.exec();
}
