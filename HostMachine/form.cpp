#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    ui->label_3->setText(QString::number(1));
    connect(&freq,SIGNAL(timeout()),this,SLOT(update_message()));
    freq.start(1000);
}

void Form::update_message()
{
    int i;
    QString text="";
    for(i=0;i<all_num;i=i+1)
    {
        if(all_windspeed[i]>=0)
        {
            text=text+" "+all_roomnum[i]+"         "+QString::number(all_temperature[i],'f',1)+"         "+QString::number(all_aim_temperature[i],'f',1)+"          "+QString::number(all_windspeed[i])+"\n";
            qDebug()<<text;
        }
    }
    ui->textBrowser->setText(text);
}

Form::~Form()
{
    delete ui;
}

void Form::on_horizontalSlider_valueChanged(int value)
{
    ui->label_3->setText(QString::number(value));
    freq.stop();
    freq.start(value*1000);
}
