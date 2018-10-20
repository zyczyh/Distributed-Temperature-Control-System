#ifndef MAINMODEL_H
#define MAINMODEL_H

#include <QObject>
#include <room.h>
#include <QtNetwork>
#include <socketsingle.h>
#include <QTimer>
class mainmodel : public QObject
{
    Q_OBJECT
public:
    explicit mainmodel(QObject *parent = 0);
    void setall(int workMode,float lowTemp,float highTemp,int worktemp);
    room* getroom();
    void sendwind(int wind);
    void changeworktemp(float worktemp);
    void interrept();
private:
    int workMode;
    float lowTemp;
    float highTemp;
    int wind;
    float worktemp;
    int sendMux;
    room * aroom;
    QTcpSocket* socket;

    void changeTemp();
    void transTemp(int,float);
    bool check();
signals:
    void changeroomtemp(float x);
    void showcost(QString a,QString b);
    void changewind();
    void changewid();
    void changestate(int);
private slots:
    void revData();
    void sendReq();
    void normalchange();
    void closed();
};

#endif // MAINMODEL_H
