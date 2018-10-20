#ifndef MULTITHREAD_H
#define MULTITHREAD_H
#include <QThread>
#include <QTcpSocket>
#include <QtNetwork>
#include <QString>
#include <QTimer>
#include <QDateTime>
#include "database.h"
#include "multithread_server.h"
#include "fifo.h"

class MultiThread : public QThread
{
    Q_OBJECT

public:
      MultiThread(qintptr s,int state,QObject *parent);
      void run() Q_DECL_OVERRIDE;
      int seq_num;
      int buffer_num;
       ~MultiThread();
signals:
      void thread_end();
private slots:
      void deal_with_message();
      void send_consumption_message();
      void send_require_message();
      void update_energy();
      void kill_thread();
      void check_order();
      void update_info();
private:
      qintptr socketDescriptor;
      QString text;
      QTcpSocket* tcpsocket;
      int workingstate;
      int connectstate;
      float energy;
      QString roomnum;
      float temperature;
      float aim_temperature;
      int windspeed;
      QString query_start_time;
      QString query_end_time;
      QString wind_start_time;
      QString wind_end_time;
      float query_start_temp;
      float query_end_temp;
      float query_start_energy;
      float query_end_energy;
      int query_start;
      QSqlDatabase database;
      QString dblink;
      int connect_success;
      QTimer allow;
  };
#endif // MULTITHREAD_H
