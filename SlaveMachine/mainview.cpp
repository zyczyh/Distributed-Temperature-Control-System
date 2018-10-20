#include "mainview.h"
#include "ui_mainview.h"

mainView::mainView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainView)
{
    ui->setupUi(this);
    x= new mainmodel();
    clickMux=0;

}

mainView::~mainView()
{
    delete ui;
}

/**
 * @brief mainView::setState
 * 初始状态设置
 * @param workMode
 * @param lowTemp
 * @param highTemp
 */
void mainView::setState(int workMode, float lowTemp, float highTemp)
{

    ui->workTemp->setMaximum(highTemp);
    ui->workTemp->setMinimum(lowTemp);
    ui->showworkmode->setText(QString::number(workMode));
    ui->showlowtemp->setText(QString::number(lowTemp));
    ui->showhightemp->setText(QString::number(highTemp));

    ui->state->setText("工作中");
    ui->roomTemp->setText(QString::number(x->getroom()->gettemp()));
    if(workMode==0)
    {
    ui->workTemp->setValue(22);
    x->setall(workMode, lowTemp, highTemp,22);
    }
    if(workMode==1)
    {
    ui->workTemp->setValue(28);
    x->setall(workMode, lowTemp, highTemp,28);
    }
    //connect(ui->workTemp,SIGNAL(valueChanged(double)),this,SLOT(on_workTemp_valueChanged(double)));
    connect(x,SIGNAL(changeroomtemp(float)),this,SLOT(freshtoomtemp(float)));
    connect(x,SIGNAL(showcost(QString,QString)),this,SLOT(showcost(QString,QString)));
    connect(x,SIGNAL(changewind()),this,SLOT(changewind()));
    connect(x,SIGNAL(changewid()),this,SLOT(changewid()));
    connect(x,SIGNAL(changestate(int)),this,SLOT(changestate(int)));
}

void mainView::on_windChange_sliderReleased()
{
    x->sendwind(ui->windChange->value());
}

/**
 * @brief mainView::on_workTemp_valueChanged
 * 当调整工作温度时触发，进行1s内控制
 * @param arg1
 * 改变的值
 */
void mainView::on_workTemp_valueChanged(double arg1)
{
    if(clickMux==0)
    {
    timetochange= new QTimer();
    connect(timetochange,SIGNAL(timeout()),this,SLOT(sendworkTemp()));
    timetochange->start(1000);
    clickMux=1;
    }
    else
    {
        timetochange->stop();
        timetochange->start(1000);
    }
}
/**
 * @brief mainView::sendworkTemp
 * 到model里进行触发发送
 */
void mainView::sendworkTemp()
{
    x->changeworktemp(ui->workTemp->value());
    timetochange->stop();
    clickMux=0;
}

void mainView::freshtoomtemp(float x)
{
    ui->roomTemp->setText(QString::number(x));
}

void mainView::showcost(QString a,QString b)
{
    ui->showenergy->setText(a);
    ui->showmonney->setText(b);
}
/**
 * @brief mainView::changewind
 * 改变风速显示
 */
void mainView::changewind()
{
    QString a;
    switch(ui->windChange->value())
    {
        case 0:
        a="低";break;
        case 1:
        a="中";break;
        case 2:
        a="高";break;
    }
    ui->showwind->setText(a);
}
/**
 * @brief mainView::changewid
 * 转换窗口
 */
void mainView::changewid()
{
    loginview* a=new loginview();
    a->show();
    this->close();
}

/**
 * @brief mainView::on_pushButton_clicked
 * 中断连接按钮
 */
void mainView::on_pushButton_clicked()
{
    x->interrept();
}

/**
 * @brief mainView::changestate
 * 改变工作状态
 * @param x
 * 0代表停机
 * 1代表工作
 */
void mainView::changestate(int x)
{
    if(x==1)
        ui->state->setText("工作中");
    else
        ui->state->setText("停机中");
}
