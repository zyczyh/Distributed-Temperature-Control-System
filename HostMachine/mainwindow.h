#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QButtonGroup>
#include <QTimer>
#include <QString>
#include <QMessageBox>
#include <QProcess>
#include "database.h"
#include "multithread_server.h"
#include "fifo.h"
#include "form.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void print_day_report();

    void print_week_report();

    void print_month_report();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void onTimeOut();

    void on_lineEdit_editingFinished();

    void on_lineEdit_2_editingFinished();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::MainWindow *ui;
    MultithreadServer* server;
    QTimer* lcdtimer;
    QString roomnum;
    QString id;
    int power;
    Form* monitor;
};

#endif // MAINWINDOW_H
