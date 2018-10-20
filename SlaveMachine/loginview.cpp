#include "loginview.h"
#include "ui_loginview.h"

loginview::loginview(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::loginview)
{
    ui->setupUi(this);
    x=new loginModel();
    connect(x,SIGNAL(transtomainwin(int,float,float)),this,SLOT(tansfer(int,float,float)));

}

loginview::~loginview()
{
    delete ui;
}

/**
 * @brief loginview::on_Button_login_clicked
 * 按下登录按钮
 */
void loginview::on_Button_login_clicked()
{
    //if(x->check(ui->lineEdit_roomnumber->text(),ui->lineEdit_id->text()))
        x->login1(ui->lineEdit_roomnumber->text(),ui->lineEdit_id->text());
    //else
        //QMessageBox::information(NULL, "对不起", "您输入的格式不对", QMessageBox::Yes, QMessageBox::Yes);
}

/**
 * @brief loginview::tansfer
 * 界面转换
 * @param workModel
 * 工作模式
 * @param lowTemp
 * 最低温度
 * @param highTemp
 * 最高温度
 */
void loginview::tansfer(int workModel, float lowTemp, float highTemp)
{
    mainView * a = new mainView();
    a->setState(workModel,lowTemp,highTemp);
    a->show();
    this->close();
}
