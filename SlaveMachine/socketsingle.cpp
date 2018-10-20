#include "socketsingle.h"

QTcpSocket* socketSingle::socket=NULL;
QTcpSocket *socketSingle::getSocket()
{
    if (socket == NULL)
    {
        socket = new QTcpSocket();
    }
    return socket;
}

socketSingle::socketSingle(QObject *parent) : QObject(parent)
{

}


