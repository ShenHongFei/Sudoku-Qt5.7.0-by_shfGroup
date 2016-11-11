#include "timer.h"
#include <QDebug>
#include <QLCDNumber>


Timer::Timer(QLCDNumber *_lcd):lcd(_lcd),timer(new QTimer(lcd)),time(0,0,0,0) {
    connect(timer, &QTimer::timeout, this, &Timer::displayUpdate);
    lcd->setSegmentStyle(QLCDNumber::Filled);
    lcd->display("00:00");
}

Timer::~Timer() {}

void Timer::start() {
    time = QTime(0, 0, 0, 0);
    qDebug() << "timer start.";
    timer->start(1000);
}

void Timer::pause() {
    timer->stop();
}

void Timer::resume() {
    timer->start(1000);
}



void Timer::displayUpdate() {
    time = time.addSecs(1);
    lcd->display(time.toString("mm:ss"));
    qDebug() << time;
}


