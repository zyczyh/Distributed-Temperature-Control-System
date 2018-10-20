#ifndef MULTITHREAD_SERVER_H
#define MULTITHREAD_SERVER_H
#include <QStringList>
#include <QTcpServer>
#include <QList>
#include "multithread.h"
#include "fifo.h"

class MultithreadServer : public QTcpServer
{
    Q_OBJECT

public:
    MultithreadServer(QObject *parent = 0);
    void change_to_heating();
    void change_to_cooling();
    int get_connect_num();
    int get_state();

protected:
    void incomingConnection(qintptr socketDescriptor) Q_DECL_OVERRIDE;
public slots:
    void cut_connect_num();
    void update_border_line();
    void update_serial_num();
private:
    QString receive;
    QString send;
    int state;
    int connect_num;
};
#endif // MULTITHREAD_SERVER_H
