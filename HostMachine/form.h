#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QTimer>
#include "fifo.h"
#include <QDebug>
namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();
private slots:
    void update_message();                            //更新显示信息
    void on_horizontalSlider_valueChanged(int value); //滑条槽函数

private:
    Ui::Form *ui;
    QTimer freq;
};

#endif // FORM_H
