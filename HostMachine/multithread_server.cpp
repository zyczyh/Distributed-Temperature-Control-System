#include"multithread_server.h"



MultithreadServer::MultithreadServer(QObject *parent)
: QTcpServer(parent)
{
    state=0;
    connect_num=0;
    all_num=0;
    border_line=3;
    serial_num=0;
    missing_values.clear();
}

void MultithreadServer::incomingConnection(qintptr socketDescriptor)
{
    connect_num=connect_num+1;
    serial_num=serial_num+1;
    MultiThread *thread = new MultiThread(socketDescriptor,state,this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(thread,SIGNAL(thread_end()),this,SLOT(cut_connect_num()));
    all_aim_temperature.append(0.0);
    all_roomnum.append("");
    all_temperature.append(0.0);
    all_windspeed.append(-100);
    all_num=all_num+1;
    thread->buffer_num=all_num-1;
    thread->seq_num=serial_num;
    thread->start();
}

void MultithreadServer::change_to_heating()
{
    state=1;
}

void MultithreadServer::change_to_cooling()
{
    state=0;
}

int MultithreadServer::get_state()
{
    return state;
}

int MultithreadServer::get_connect_num()
{
    return connect_num;
}

void MultithreadServer::cut_connect_num()
{
    connect_num=connect_num-1;
}

void MultithreadServer::update_border_line()
{
    border_line=border_line+1;
}

void MultithreadServer::update_serial_num()
{
    serial_num=serial_num+1;
}

