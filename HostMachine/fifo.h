#ifndef FIFO_H
#define FIFO_H
#include <QList>
#include <QString>
extern int border_line;                    //用于先来先服务策略的队头标志
extern int serial_num;                     //用于先来先服务策略的队尾标志
extern int all_num;                        //用于记录各房间信息数组的标志
extern QList <int> missing_values;         //用于记录队列缺失值的链表
extern QList <QString> all_roomnum;        //用于记录已连接的房间的房间号
extern QList <float> all_temperature;      //用于记录已连接房间的室内温度
extern QList <float> all_aim_temperature;  //用于记录已连接房间的目标温度
extern QList <int> all_windspeed;          //用于记录已连接房间的风速
#endif // FIFO_H
