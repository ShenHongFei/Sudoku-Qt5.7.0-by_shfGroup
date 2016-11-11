#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tableio.h"
#include "timer.h"
#include "ui_mainwindow.h"
#include "ui_aboutdialog.h"
#include "ui_helpdialog.h"
#include <QMouseEvent>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
public slots:
    void on_aboutButton_clicked();
    void on_helpButton_clicked();
    void setRemainCell();
    void pause();
    void changeEyeIcon();

    void success();

    void failed();

private slots:
	void on_numButton_1_clicked();

	void on_numButton_2_clicked();

	void on_numButton_3_clicked();

	void on_numButton_4_clicked();

	void on_numButton_5_clicked();

	void on_numButton_9_clicked();

	void on_numButton_6_clicked();

	void on_numButton_7_clicked();

	void on_numButton_8_clicked();

private:

    Ui::MainWindow *ui;
    Ui::AboutDialog *aboutui;
    Ui::HelpDialog *helpui;
    TableIO *tio;
    Timer *lcdtimer;
    QLCDNumber *countLCD;
    bool eyestate=1;


};

#endif // MAINWINDOW_H
