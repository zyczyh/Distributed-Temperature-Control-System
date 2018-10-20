#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QWidget>
#include <mainmodel.h>
#include <QTimer>
#include <loginview.h>
namespace Ui {
class mainView;
}

class mainView : public QWidget
{
    Q_OBJECT

public:
    explicit mainView(QWidget *parent = 0);
    ~mainView();

    void setState(int workMode, float lowTemp, float highTemp);
private slots:
    void on_windChange_sliderReleased();
    void on_workTemp_valueChanged(double arg1);

    void sendworkTemp();
    void freshtoomtemp(float x);
    void showcost(QString a,QString b);
    void changewind();
    void changewid();
    void on_pushButton_clicked();
    void changestate(int x);
private:
    Ui::mainView *ui;
    mainmodel * x;
    bool clickMux;
    QTimer* timetochange;
};

#endif // MAINVIEW_H
