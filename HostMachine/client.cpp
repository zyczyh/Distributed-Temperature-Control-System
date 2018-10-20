#include "client.h"

void Client::init()
{
    tcpSocket = new QTcpSocket;
    newTcpConnect();

    connect(tcpSocket,SIGNAL(readyRead()),SLOT(onReciveData()));
}

void Client::newTcpConnect()
{
    tcpSocket->abort();
    tcpSocket->connectToHost("127.0.0.1",6666);
}

void Client::onReciveData()
{
    QString data = tcpSocket->readAll();
    qDebug()<<data;
}

