#include "room.h"

room::room(QObject *parent) : QObject(parent)
{
    temperature=25.0;
    times = new QTimer();
    times->start(4000);
    connect(times,SIGNAL(timeout()),this,SLOT(sig()));
}

float room::gettemp()
{
    return this->temperature;
}

void room::settemp(float x)
{
    this->temperature=x;
}

void room::sig()
{
    emit timeover();
}
