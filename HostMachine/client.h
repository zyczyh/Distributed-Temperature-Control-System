#ifndef CLIENT_H
#define CLIENT_H
#include <QTcpSocket>
#include <QTcpServer>
#include <QDataStream>
#include <QObject>

class Client : public QTcpSocket
{
    Q_OBJECT
public:
    void init();
    void newTcpConnect();
private slots:
    void onReciveData();
private:
    QTcpSocket *tcpSocket;
    QByteArray mChat;
};
#endif // CLIENT_H
