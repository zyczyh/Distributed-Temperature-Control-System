#include "mainmodel.h"

mainmodel::mainmodel(QObject *parent) : QObject(parent)
{
    aroom=new room();
    socket=socketSingle::getSocket();
    connect(socket,SIGNAL(readyRead()),this,SLOT(revData()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(closed()));
    sendMux=0;
    wind=0;
}

void mainmodel::setall(int workMode, float lowTemp, float highTemp,int worktemp)
{
    this->workMode=workMode;
    this->lowTemp=lowTemp;
    this->highTemp=highTemp;
    this->worktemp=worktemp;

    changeworktemp(this->worktemp);

    connect(aroom,SIGNAL(timeover()),this,SLOT(normalchange()));

}

room *mainmodel::getroom()
{
    return aroom;
}

void mainmodel::sendwind(int wind) //发送改变请求
{
    QString a="wind/"+QString::number(wind);
    socket->write(a.toLatin1());
}

void mainmodel::changeworktemp(float worktemp)
{
    this->worktemp=worktemp;
    qDebug()<<worktemp;
    if(fabs(aroom->gettemp()-worktemp)>0.01) //当工作温度和房间温度不相等时
    {
            emit changestate(1);
            sendMux=1;
            if(aroom->gettemp()<worktemp&&workMode==1) //满足制热条件
            {
                sendMux=2;
                QString a="request/"+QString::number(this->aroom->gettemp())+"/"+QString::number(worktemp);
                socket->write(a.toLatin1());
                qDebug()<<"制热";

            }
            else if(aroom->gettemp()>worktemp&&workMode==0) //满足制冷条件
            {
                sendMux=2;
                QString a="request/"+QString::number(this->aroom->gettemp())+"/"+QString::number(worktemp);
                socket->write(a.toLatin1());
                qDebug()<<"制冷";
            }
            else
            {
                sendMux=0;
            }

    }
}

void mainmodel::revData()
{
    QString datas = socket->readAll();
    qDebug()<<datas;
    QStringList list = datas.split("/");


    if(QString::compare(QString(list[0]),"cost")==0)
    {
        //ui->textBrowser->append("enegy"+QString(list[1])+"\ncost:"+QString(list[2]));
        emit showcost(QString(list[1]),QString(list[2]));
    }
    if(QString::compare(QString(list[0]),"request")==0)
    {
        QString a= "answer/"+QString::number(aroom->gettemp())+"/"+QString::number(worktemp)+"/"+QString::number(wind);
        socket->write(a.toLatin1());
    }
    if(QString::compare(QString(list[0]),"answer")==0)
    {
        changeTemp();
    }
    if(QString::compare(QString(list[0]),"acceptWind")==0)
    {
        emit changewind();
    }

}

/**
 * @brief mainmodel::changeTemp
 * 改变温度
 */
void mainmodel::changeTemp()
{
    float x=0;
    switch(wind)
    {
        case 0:
            x=0.1; break;
        case 1:
            x=0.2; break;
        case 2:
            x=0.3; break;
    }
    if(this->workMode==0)
        transTemp(1,x);

    if(this->workMode==1)
        transTemp(0,x);

    if(sendMux==2&&check()==false)
        QTimer::singleShot(200,this,SLOT(sendReq())); //降降速
}

void mainmodel::transTemp(int sym,float num)
{
    if(sym==0)
    aroom->settemp(aroom->gettemp()+num);
    else
    aroom->settemp(aroom->gettemp()-num);

    emit changeroomtemp(aroom->gettemp());
}

bool mainmodel::check()
{
    if(workMode==0&&aroom->gettemp()<=worktemp)
    {
        QString a="requestEnd";
        socket->write(a.toLatin1());
        sendMux=0;
        emit changestate(2);
        return true;
    }
    if(workMode==1&&aroom->gettemp()>=worktemp)
    {
        QString a="requestEnd";
        socket->write(a.toLatin1());
        sendMux=0;
        return true;
    }
    return false;
}

/**
 * @brief mainmodel::interrept
 * 手动断开连接
 */
void mainmodel::interrept()
{
    socket->abort();

}

void mainmodel::sendReq()
{
    QString a="request/"+QString::number(this->aroom->gettemp())+"/"+QString::number(worktemp);
    socket->write(a.toLatin1());
}

/**
 * @brief mainmodel::normalchange
 *房间温度的改变
 */
void mainmodel::normalchange()
{
    if(sendMux==0)
    {
        if(workMode==0&&(aroom->gettemp()-worktemp)<1.0) //制冷模式 房间温度高 但没超过1度
        {
            transTemp(0,0.1);
        }
        else if(workMode==0&&(aroom->gettemp()-worktemp)>1.0) //制冷模式 房间温度高 超过1度
        {
            changeworktemp(this->worktemp);
        }
        else if(workMode==0&&(worktemp-aroom->gettemp())>0.0) //制冷模式 房间温度低
        {
            transTemp(0,0.1);
        }

        else if(workMode==1&&(aroom->gettemp()-worktemp)>0.0) //制热模式 房间温度高
        {
            transTemp(1,0.1);
        }
        else if(workMode==1&&(worktemp-aroom->gettemp())<1.0) //制热模式 房间温度低 没超过过1度
        {
            transTemp(1,0.1);
        }
        else if(workMode==1&&(worktemp-aroom->gettemp())>1.0) //制热模式 房间温度低 超过1度
        {
            changeworktemp(this->worktemp);
        }

    }
}

/**
 * @brief mainmodel::closed
 * 断开tcp后的操作
 */
void mainmodel::closed()
{
   disconnect(socket,SIGNAL(readyRead()),this,SLOT(revData()));
   emit this->changewid();
}
