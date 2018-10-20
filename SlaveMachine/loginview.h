#ifndef LOGINVIEW_H
#define LOGINVIEW_H

#include <QWidget>
#include <loginmodel.h>
#include <mainview.h>
namespace Ui {
class loginview;
}

class loginview : public QWidget
{
    Q_OBJECT

public:
    explicit loginview(QWidget *parent = 0);
    ~loginview();

private slots:
    void on_Button_login_clicked();
    void tansfer(int workModel,float lowTemp,float highTemp);

private:
    Ui::loginview *ui;
    loginModel * x;
signals:
    void sendlogginmessage();

};

#endif // LOGINVIEW_H
