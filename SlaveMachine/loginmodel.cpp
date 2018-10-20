#include "loginmodel.h"

loginModel::loginModel(QObject *parent) : QObject(parent)
{
    socket=socketSingle::getSocket();
    connect(socket,SIGNAL(readyRead()),this,SLOT(revData()));
}

/**
 * @brief loginModel::login1
 * 进行连接
 * @param roomnumber
 * 房间号
 * @param id
 * 身份证号
 */
void loginModel::login1(QString roomnumber, QString id)
{

    socket->connectToHost("localhost",6666);
    if (socket->waitForConnected(1000))
    {
        QString a = "clientMsg/"+roomnumber+"/"+id;
        socket->write(a.toLatin1());
    }
    else
    {

    }
}

/**
 * @brief loginModel::check
 * 检验输入的身份证号和房间号是否正确
 * @param roomnumber
 * 房间号
 * @param id
 * 身份证号
 * @return
 */
bool loginModel::check(QString roomnumber, QString id)
{
    QString patternRoomnumber("(\\d){3}");
    QString patternId("(\\d){18}");
    QRegExp rx(patternRoomnumber);
    QRegExp rx2(patternId);

    bool match = rx.exactMatch(roomnumber);
    bool match2 = rx2.exactMatch(id);
    qDebug()<<match<<match2;
    return match&match2;
}

/**
 * @brief loginModel::revData
 * 接受到服务器发过来的工作模式和最高温度和最低温度然后通知界面更改
 */
void loginModel::revData()
{
    QString datas = socket->readAll();
    qDebug()<<datas;
    QStringList list = datas.split("/");

    if(QString::compare(QString(list[1]),"reject")==0)
    {
        qDebug()<<"不给住";
        QMessageBox::information(NULL, "对不起", "您输入的格式不对", QMessageBox::Yes, QMessageBox::Yes);
        return ;
    }
    else
    {
    int workModel=QString(list[1]).toInt();
    float lowTemp= QString(list[2]).toFloat();
    float highTemp= QString(list[3]).toFloat();

    disconnect(socket,SIGNAL(readyRead()),this,SLOT(revData()));
    emit this->transtomainwin(workModel,lowTemp,highTemp);
    }
}

