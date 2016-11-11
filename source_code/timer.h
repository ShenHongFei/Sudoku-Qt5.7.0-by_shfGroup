#pragma once
#include <QWidget>
#include <QTimer>
#include <QString>
#include <QLCDNumber>
#include <QtCore>
#include <QTime>

class Timer :
    public QTimer {
    Q_OBJECT

public:
    Timer(QLCDNumber *_lcd);
    ~Timer();

    void start();
    void pause();
    void resume();
    void displayUpdate();
private:

    int count=0;
    QLCDNumber *lcd;
    QTimer *timer;
    QTime time;

};

