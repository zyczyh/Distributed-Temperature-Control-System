#ifndef LOGINMODEL_H
#define LOGINMODEL_H

#include <QObject>
#include <QtNetwork>
#include<socketsingle.h>
#include <QMessageBox>
class loginModel : public QObject
{
    Q_OBJECT
public:
    explicit loginModel(QObject *parent = 0);
    void login1(QString roomnumber,QString id);
    bool check(QString roomnumber,QString id);
signals:
    void transtomainwin(int,float,float);
private slots:
    void revData();
private:
    QTcpSocket* socket;
};

#endif // LOGINMODEL_H
