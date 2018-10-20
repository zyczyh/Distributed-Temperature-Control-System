#include "multithread.h"

MultiThread::MultiThread(qintptr s,int state,QObject *parent)
    : QThread(parent), socketDescriptor(s)
{
    allow.moveToThread(this);
    workingstate=state;
    connectstate=1;
    energy=0;
    windspeed=-1;
    query_start=0;
    connect_success=0;
    QDateTime time=QDateTime::currentDateTime();
    dblink=time.toString("hh:mm:ss");
    database=QSqlDatabase::addDatabase("QSQLITE",dblink);
    database.setDatabaseName("air_conditioner.db");
    if(database.open())
    {
        qDebug()<<"database opened";
    }
    else
    {
        qDebug()<<"database open failed";
    }
}

 void MultiThread::run()
 {
     QTimer timer1;
     QTimer timer2;
     QTimer timer3;
     QTimer timer4;
     tcpsocket=new QTcpSocket;
     if (!tcpsocket->setSocketDescriptor(socketDescriptor)) {
         qDebug()<<"error";
         return;
     }
     connect(tcpsocket,SIGNAL(readyRead()),this,SLOT(deal_with_message()),Qt::DirectConnection);
     connect(tcpsocket,SIGNAL(disconnected()),this,SLOT(kill_thread()));
     connect(&allow,SIGNAL(timeout()),this,SLOT(check_order()),Qt::DirectConnection);
     connect(&timer1,SIGNAL(timeout()),this,SLOT(send_consumption_message()),Qt::DirectConnection);
     connect(&timer2,SIGNAL(timeout()),this,SLOT(send_require_message()),Qt::DirectConnection);
     connect(&timer3,SIGNAL(timeout()),this,SLOT(update_energy()),Qt::DirectConnection);
     connect(&timer4,SIGNAL(timeout()),this,SLOT(update_info()),Qt::DirectConnection);
     timer1.start(4000);
     timer2.start(2000);
     timer3.start(4000);
     timer4.start(500);
     this->exec();
     qDebug()<<1;
     timer1.stop();
     timer2.stop();
     timer3.stop();
     tcpsocket->disconnectFromHost();
     tcpsocket->waitForDisconnected();
     //this->exec();
 }

 void MultiThread::deal_with_message()
 {
     QString data=tcpsocket->readAll();
     int count=0;
     int result=0;
     int found=0;
     int i;
     QString id="";
     QString out;
     QString wind="";
     QString temp="";
     QString aim_temp="";
     QByteArray sendMessage;
     QDateTime time;
     QSqlQuery query(QSqlDatabase::database(dblink));

     qDebug()<<data;
     if(data[0]=='c')
     {
         roomnum="";
         while(data[count]!='/')
         {
             count=count+1;
         }
         count=count+1;
         while(data[count]!='/')
         {
             roomnum=roomnum+data[count];
             count=count+1;
         }
         count=count+1;
         while(count<data.length())
         {
             id=id+data[count];
             count=count+1;
         }
         query.prepare("select * from ID where roomid=? and idnum=?");
         query.addBindValue(roomnum);
         query.addBindValue(id);
         query.exec();
         while(query.next())
         {
             result=result+1;
         }
         for(i=0;i<all_num;i=i+1)
         {
             if(all_windspeed[i]>=0 && all_roomnum[i]==roomnum)
             {
                 found=1;
             }
         }
         if(result>0 && found==0)//检查id
         {
             connect_success=1;
             if(workingstate==0)
             {
                 out="serverMsg/0/18/25";
             }
             else
             {
                 out="serverMsg/1/25/30";
             }
             sendMessage = out.toLocal8Bit();
             tcpsocket->write(sendMessage);
         }
         else
         {
             out="serverMsg/reject";
             sendMessage=out.toLocal8Bit();
             tcpsocket->write(sendMessage);
             connectstate=0;
         }
     }
     else if(data[0]=='r' && data[7]=='/')
     {
         while(data[count]!='/')
         {
             count=count+1;
         }
         count=count+1;
         while(data[count]!='/')
         {
             temp=temp+data[count];
             count=count+1;
         }
         count=count+1;
         temperature=temp.toFloat();
         if(seq_num <= border_line)
         {
            out="answer";
            sendMessage=out.toLocal8Bit();
            tcpsocket->write(sendMessage);
            if(query_start==0)
            {
                time=QDateTime::currentDateTime();
                query_start_time=time.toString("yyyy-MM-dd hh:mm:ss ddd");
                query_start_temp=temperature;
                query_start_energy=energy;
                wind_start_time=time.toString("yyyy-MM-dd hh:mm:ss ddd");
                query_start=1;
            }
         }
         else
         {
             allow.start(10);
         }
     }
     else if(data[0]=='w')
     {
         out="acceptWind";
         sendMessage=out.toLocal8Bit();
         tcpsocket->write(sendMessage);
         while(data[count]!='/')
         {
             count=count+1;
         }
         count=count+1;
         wind=data[count];
         time=QDateTime::currentDateTime();
         wind_end_time=time.toString("yyyy-MM-dd hh:mm:ss ddd");
         //这里为插入风速数据库操作
         query.prepare("insert into Windspeed values(?,?,?,?)");
         query.addBindValue(roomnum+query_start_time);
         query.addBindValue(wind_start_time);
         query.addBindValue(wind_end_time);
         query.addBindValue(windspeed);
         query.exec();
         query.finish();
         wind_start_time=time.toString("yyyy-MM-dd hh:mm:ss ddd");
         windspeed=wind.toInt();
     }
     else if(data=="requestEnd")
     {
         border_line=border_line+1;
         while(missing_values.contains(border_line))
         {
            border_line=border_line+1;
         }
         serial_num=serial_num+1;
         seq_num=serial_num;
         time=QDateTime::currentDateTime();
         query_end_time=time.toString("yyyy-MM-dd hh:mm:ss ddd");
         query_end_temp=temperature;
         query_end_energy=energy;
         wind_end_time=time.toString("yyyy-MM-dd hh:mm:ss ddd");
         //这里为插入请求数据库和风速数据库操作
         query.prepare("insert into Query values(?,?,?,?,?,?,?)");
         query.addBindValue(roomnum+query_start_time);
         query.addBindValue(roomnum);
         query.addBindValue(query_start_time);
         query.addBindValue(query_end_time);
         query.addBindValue(query_start_temp);
         query.addBindValue(query_end_temp);
         query.addBindValue((query_end_energy-query_start_energy)*5);
         query.exec();
         query.finish();
         query.prepare("insert into Windspeed values(?,?,?,?)");
         query.addBindValue(roomnum+query_start_time);
         query.addBindValue(wind_start_time);
         query.addBindValue(wind_end_time);
         query.addBindValue(windspeed);
         query.exec();
         query.finish();
         query_start=0;
     }
     else if(data[0]=='a')
     {
         while(data[count]!='/')
         {
             count=count+1;
         }
         count=count+1;
         while(data[count]!='/')
         {
             temp=temp+data[count];
             count=count+1;
         }
         count=count+1;
         while(data[count]!='/')
         {
             aim_temp=aim_temp+data[count];
             count=count+1;
         }
         count=count+1;
         wind=data[count];
         temperature=temp.toFloat();
         aim_temperature=aim_temp.toFloat();
         windspeed=wind.toInt();
     }
     else
     {
     }
 }

void MultiThread::send_consumption_message()
{
    QString out;
    QByteArray sendMessage;
    if(connect_success==1)
    {
        out="cost/"+QString::number(energy)+'/'+QString::number(energy*5);
        sendMessage = out.toLocal8Bit();
        tcpsocket->write(sendMessage);
    }
}

void MultiThread::send_require_message()
{
    QString out;
    QByteArray sendMessage;
    if(connect_success==1)
    {
        out="request";
        sendMessage = out.toLocal8Bit();
        tcpsocket->write(sendMessage);
    }
}

void MultiThread::update_energy()
{
    if(windspeed==0&&query_start==1)
    {
        energy=energy+0.8;
    }
    else if(windspeed==1&&query_start==1)
    {
        energy=energy+1;
    }
    else if(windspeed==2&&query_start==1)
    {
        energy=energy+1.3;
    }
    else
    {
    }
}

void MultiThread::update_info()
{
    all_aim_temperature[buffer_num]=aim_temperature;
    all_roomnum[buffer_num]=roomnum;
    all_temperature[buffer_num]=temperature;
    all_windspeed[buffer_num]=windspeed;
}

void MultiThread::kill_thread()
{
    QSqlQuery query(QSqlDatabase::database(dblink));
    QDateTime time=QDateTime::currentDateTime();
    QString timenow=time.toString("yyyy-MM-dd hh:mm:ss ddd");
    query.prepare("insert into Shutdown values(?,?)");
    query.addBindValue(roomnum);
    query.addBindValue(timenow);
    query.exec();
    if(seq_num<=border_line)
    {
        border_line=border_line+1;
    }
    else
    {
        missing_values.append(seq_num);
    }
    emit thread_end();
    this->deleteLater();
}

void MultiThread::check_order()          //避免主从机陷入死锁
{
    QString out;
    QByteArray sendMessage;
    QDateTime time;

    if(seq_num <= border_line)
    {
        out="answer";
        sendMessage=out.toLocal8Bit();
        tcpsocket->write(sendMessage);
        if(query_start==0)
        {
            time=QDateTime::currentDateTime();
            query_start_time=time.toString("yyyy-MM-dd hh:mm:ss ddd");
            query_start_temp=temperature;
            query_start_energy=energy;
            wind_start_time=time.toString("yyyy-MM-dd hh:mm:ss ddd");
            query_start=1;
        }
        allow.stop();
    }
}

MultiThread::~MultiThread()
{
    all_windspeed[buffer_num]=-100;
}
