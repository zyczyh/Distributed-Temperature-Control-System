#ifndef ROOM_H
#define ROOM_H

#include <QObject>
#include <QTimer>

class room : public QObject
{
    Q_OBJECT
public:
    explicit room(QObject *parent = 0);
    float gettemp();
    void settemp(float x);
private:
    float temperature;
    QTimer* times;
public slots:

signals:
    void timeover();
private slots:
    void sig();
};

#endif // ROOM_H
