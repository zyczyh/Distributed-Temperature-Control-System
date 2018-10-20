#ifndef SOCKETSINGLE_H
#define SOCKETSINGLE_H

#include <QObject>
#include <QtNetwork>

class socketSingle : public QObject
{
    Q_OBJECT
public:
    static QTcpSocket * getSocket();

private:
    explicit socketSingle(QObject *parent = 0);
    static QTcpSocket* socket;

};

#endif // SOCKETSINGLE_H
