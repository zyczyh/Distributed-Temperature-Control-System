#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lcdNumber->setDigitCount(3);
    ui->lcdNumber->setMode(QLCDNumber::Dec);
    QPalette lcdpat = ui->lcdNumber->palette();
    lcdpat.setColor(QPalette::Normal,QPalette::WindowText,Qt::white);
    ui->lcdNumber->setPalette(lcdpat);
    ui->pushButton_2->setEnabled(false);
    roomnum="";
    id="";
    power=0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::print_day_report()
{
    QSqlQuery query;
    QSqlQuery query1;
    QDateTime time=QDateTime::currentDateTime();
    QDateTime one_day_before=time.addDays(-1);
    QDateTime start;
    QDateTime end;
    QDateTime shut;
    QFile file("S:\\day_report.txt");
    QString query_id;
    QString roomid;
    QString start_time;
    QString end_time;
    QString shut_time;
    float start_temp;
    float end_temp;
    float cost;
    float tot_cost=0;
    int count=0;

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
          qDebug()<<"open file failed.";
    }
    QTextStream txtOutput(&file);
    query.prepare("select * from Query");
    query.exec();
    while(query.next())
    {
        query_id=query.value(0).toString();
        roomid=query.value(1).toString();
        start_time=query.value(2).toString();
        end_time=query.value(3).toString();
        start_temp=query.value(4).toFloat();
        end_temp=query.value(5).toFloat();
        cost=query.value(6).toFloat();
        start=QDateTime::fromString(start_time,"yyyy-MM-dd hh:mm:ss ddd");
        end=QDateTime::fromString(end_time,"yyyy-MM-dd hh:mm:ss ddd");
        if(start>=one_day_before && end<=time)
        {
            txtOutput<<"-------------------------------------------------------------------------------------------------------------"<<endl;
            txtOutput<<"query_id:"<<query_id<<endl<<"roomid:"<<roomid<<endl<<"start_time:"<<start_time<<endl<<"end_time:"<<end_time<<endl<<"start_temp:"<<start_temp<<endl<<"end_temp:"<<end_temp<<endl<<"cost:"<<cost<<endl;
            tot_cost=tot_cost+cost;
            query1.prepare("select * from Windspeed where queryid=?");
            query1.addBindValue(query_id);
            query1.exec();
            while(query1.next())
            {
                txtOutput<<"********************************************************************************************************"<<endl;
                txtOutput<<"query_id:"<<query1.value(0).toString()<<endl<<"start_time:"<<query1.value(1).toString()<<endl<<"end_time:"<<query1.value(2).toString()<<endl<<"windspeed:"<<query1.value(3).toString()<<endl;
                txtOutput<<"********************************************************************************************************"<<endl;
            }
            txtOutput<<"-------------------------------------------------------------------------------------------------------------"<<endl;
        }
    }
    txtOutput<<"total cost:"<<tot_cost<<endl;
    query.finish();
    query1.finish();
    query.prepare("select distinct roomid from Shutdown where time >= ? and time <= ?");
    query.addBindValue(one_day_before.toString("yyyy-MM-dd hh:mm:ss ddd"));
    query.addBindValue(time.toString("yyyy-MM-dd hh:mm:ss ddd"));
    query.exec();
    while(query.next())
    {
        roomid=query.value(0).toString();
        count=0;
        query1.prepare("select * from Shutdown where roomid=?");
        query1.addBindValue(roomid);
        query1.exec();
        while(query1.next())
        {
            roomid=query1.value(0).toString();
            shut_time=query1.value(1).toString();
            shut=QDateTime::fromString(shut_time,"yyyy-MM-dd hh:mm:ss ddd");
            if(shut>=one_day_before && shut<=time)
            {
                count=count+1;
            }
        }
        txtOutput<<"roomid:"<<roomid<<" "<<"shutdown times:"<<count<<endl;

    }
    file.close();
}

void MainWindow::print_week_report()
{
    QSqlQuery query;
    QSqlQuery query1;
    QDateTime time=QDateTime::currentDateTime();
    QDateTime one_week_before=time.addDays(-7);
    QDateTime start;
    QDateTime end;
    QDateTime shut;
    QFile file("S:\\week_report.txt");
    QString query_id;
    QString roomid;
    QString start_time;
    QString end_time;
    QString shut_time;
    float start_temp;
    float end_temp;
    float cost;
    float tot_cost=0;
    int count=0;

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
          qDebug()<<"open file failed.";
    }
    QTextStream txtOutput(&file);
    query.prepare("select * from Query");
    query.exec();
    while(query.next())
    {
        query_id=query.value(0).toString();
        roomid=query.value(1).toString();
        start_time=query.value(2).toString();
        end_time=query.value(3).toString();
        start_temp=query.value(4).toFloat();
        end_temp=query.value(5).toFloat();
        cost=query.value(6).toFloat();
        start=QDateTime::fromString(start_time,"yyyy-MM-dd hh:mm:ss ddd");
        end=QDateTime::fromString(end_time,"yyyy-MM-dd hh:mm:ss ddd");
        if(start>=one_week_before && end<=time)
        {
            txtOutput<<"-------------------------------------------------------------------------------------------------------------"<<endl;
            txtOutput<<"query_id:"<<query_id<<endl<<"roomid:"<<roomid<<endl<<"start_time:"<<start_time<<endl<<"end_time:"<<end_time<<endl<<"start_temp:"<<start_temp<<endl<<"end_temp:"<<end_temp<<endl<<"cost:"<<cost<<endl;
            tot_cost=tot_cost+cost;
            query1.prepare("select * from Windspeed where queryid=?");
            query1.addBindValue(query_id);
            query1.exec();
            while(query1.next())
            {
                txtOutput<<"********************************************************************************************************"<<endl;
                txtOutput<<"query_id:"<<query1.value(0).toString()<<endl<<"start_time:"<<query1.value(1).toString()<<endl<<"end_time:"<<query1.value(2).toString()<<endl<<"windspeed:"<<query1.value(3).toString()<<endl;
                txtOutput<<"********************************************************************************************************"<<endl;
            }
            txtOutput<<"-------------------------------------------------------------------------------------------------------------"<<endl;
        }
    }
    txtOutput<<"total cost:"<<tot_cost<<endl;
    query.finish();
    query1.finish();
    query.prepare("select distinct roomid from Shutdown where time >= ? and time <= ?");
    query.addBindValue(one_week_before.toString("yyyy-MM-dd hh:mm:ss ddd"));
    query.addBindValue(time.toString("yyyy-MM-dd hh:mm:ss ddd"));
    query.exec();
    while(query.next())
    {
        roomid=query.value(0).toString();
        count=0;
        query1.prepare("select * from Shutdown where roomid=?");
        query1.addBindValue(roomid);
        query1.exec();
        while(query1.next())
        {
            roomid=query1.value(0).toString();
            shut_time=query1.value(1).toString();
            shut=QDateTime::fromString(shut_time,"yyyy-MM-dd hh:mm:ss ddd");
            if(shut>=one_week_before && shut<=time)
            {
                count=count+1;
            }
        }
        txtOutput<<"roomid:"<<roomid<<" "<<"shutdown times:"<<count<<endl;

    }
    file.close();
}

void MainWindow::print_month_report()
{
    QSqlQuery query;
    QSqlQuery query1;
    QDateTime time=QDateTime::currentDateTime();
    QDateTime one_month_before=time.addMonths(-1);
    QDateTime start;
    QDateTime end;
    QDateTime shut;
    QFile file("S:\\month_report.txt");
    QString query_id;
    QString roomid;
    QString start_time;
    QString end_time;
    QString shut_time;
    float start_temp;
    float end_temp;
    float cost;
    float tot_cost=0;
    int count=0;

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
          qDebug()<<"open file failed.";
    }
    QTextStream txtOutput(&file);
    query.prepare("select * from Query");
    query.exec();
    while(query.next())
    {
        query_id=query.value(0).toString();
        roomid=query.value(1).toString();
        start_time=query.value(2).toString();
        end_time=query.value(3).toString();
        start_temp=query.value(4).toFloat();
        end_temp=query.value(5).toFloat();
        cost=query.value(6).toFloat();
        start=QDateTime::fromString(start_time,"yyyy-MM-dd hh:mm:ss ddd");
        end=QDateTime::fromString(end_time,"yyyy-MM-dd hh:mm:ss ddd");
        if(start>=one_month_before && end<=time)
        {
            txtOutput<<"-------------------------------------------------------------------------------------------------------------"<<endl;
            txtOutput<<"query_id:"<<query_id<<endl<<"roomid:"<<roomid<<endl<<"start_time:"<<start_time<<endl<<"end_time:"<<end_time<<endl<<"start_temp:"<<start_temp<<endl<<"end_temp:"<<end_temp<<endl<<"cost:"<<cost<<endl;
            tot_cost=tot_cost+cost;
            query1.prepare("select * from Windspeed where queryid=?");
            query1.addBindValue(query_id);
            query1.exec();
            while(query1.next())
            {
                txtOutput<<"********************************************************************************************************"<<endl;
                txtOutput<<"query_id:"<<query1.value(0).toString()<<endl<<"start_time:"<<query1.value(1).toString()<<endl<<"end_time:"<<query1.value(2).toString()<<endl<<"windspeed:"<<query1.value(3).toString()<<endl;
                txtOutput<<"********************************************************************************************************"<<endl;
            }
            txtOutput<<"-------------------------------------------------------------------------------------------------------------"<<endl;
        }
    }
    txtOutput<<"total cost:"<<tot_cost<<endl;
    query.finish();
    query1.finish();
    query.prepare("select distinct roomid from Shutdown where time >= ? and time <= ?");
    query.addBindValue(one_month_before.toString("yyyy-MM-dd hh:mm:ss ddd"));
    query.addBindValue(time.toString("yyyy-MM-dd hh:mm:ss ddd"));
    query.exec();
    while(query.next())
    {
        roomid=query.value(0).toString();
        count=0;
        query1.prepare("select * from Shutdown where roomid=?");
        query1.addBindValue(roomid);
        query1.exec();
        while(query1.next())
        {
            roomid=query1.value(0).toString();
            shut_time=query1.value(1).toString();
            shut=QDateTime::fromString(shut_time,"yyyy-MM-dd hh:mm:ss ddd");
            if(shut>=one_month_before && shut<=time)
            {
                count=count+1;
            }
        }
        txtOutput<<"roomid:"<<roomid<<" "<<"shutdown times:"<<count<<endl;

    }
    file.close();
}

void MainWindow::on_pushButton_3_clicked()
{
    QProcess* report=new QProcess();
    this->print_day_report();
    report->start("notepad.exe s:\\day_report.txt");
    ui->label_5->setText("Print day report success!");
}

void MainWindow::on_pushButton_4_clicked()
{
    QProcess* report=new QProcess();
    this->print_week_report();
    report->start("notepad.exe s:\\week_report.txt");
    ui->label_5->setText("Print week report success!");
}

void MainWindow::on_pushButton_5_clicked()
{
    QProcess* report=new QProcess();
    this->print_month_report();
    report->start("notepad.exe s:\\month_report.txt");
    ui->label_5->setText("Print month report success!");
}

void MainWindow::on_pushButton_clicked()
{
    if(power==0)
    {
        server=new MultithreadServer;
        server->listen(QHostAddress::Any,6666);
        lcdtimer=new QTimer(this);
        lcdtimer->setInterval(1000);
        connect(lcdtimer, SIGNAL(timeout()), this, SLOT(onTimeOut()));
        lcdtimer->start();
        ui->label_5->setText("air conditioner opened!");
        ui->pushButton_2->setEnabled(true);
        power=1;
        ui->pushButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/picture/kg_2_an.jpg);}");
    }
    else
    {
        delete(server);
        ui->label_5->setText("air conditioner closed!");
        ui->pushButton_2->setEnabled(false);
        power=0;
        ui->pushButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/picture/kg_2.jpg);}");
        this->close();
    }
}



void MainWindow::onTimeOut()
{
    if(power==1)
    {
        ui->lcdNumber->display(server->get_connect_num());
    }
    else
    {
        ui->lcdNumber->display(0);
    }
}

void MainWindow::on_lineEdit_editingFinished()
{
    roomnum=ui->lineEdit->text();
}



void MainWindow::on_lineEdit_2_editingFinished()
{
    id=ui->lineEdit_2->text();
}



void MainWindow::on_pushButton_6_clicked()
{
    QSqlQuery query;
    if(roomnum==""||id=="")
    {
        ui->label_5->setText("Please input room number and ID!");
    }
    else
    {
        query.prepare("insert into ID values(?,?)");
        query.addBindValue(roomnum);
        query.addBindValue(id);
        query.exec();
        query.finish();
        roomnum="";
        id="";
        ui->label_5->setText("query commited!");
    }
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
}

void MainWindow::on_pushButton_2_clicked()
{
    if(server->get_state()==0)
    {
        server->change_to_heating();
        ui->pushButton_2->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/picture/zr_2.jpg);}");
        ui->label_5->setText("change to heating!");
    }
    else
    {
        server->change_to_cooling();
        ui->pushButton_2->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/picture/zl_2.jpg);}");
        ui->label_5->setText("change to cooling!");
    }
}

void MainWindow::on_pushButton_7_clicked()
{
    monitor=new Form();
    monitor->show();
    ui->label_5->setText("monitor opened!");
}
