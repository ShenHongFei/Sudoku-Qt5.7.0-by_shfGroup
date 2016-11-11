#ifndef TABLEIO_H
#define TABLEIO_H

#include "ui_mainwindow.h"
#include <QTableWidget>
#include "data.h"



class TableIO :public QObject
{
    Q_OBJECT
public:
    TableIO(QTableWidget *uitable);

    void newGame();
    void comboBoxChanged(int index);
    void clear();
    void hint();
    void checkAns();
	void drawBackground();
    void drawEyeBackground(int row, int column);
    void changeEyestate();
	void setnum(int n);

signals:
    void ansright();
    void answrong();
    
private:
    void setPuzzle(void);//set to table

    QTableWidget* table;
	Data *data;
    enum Diffuculty {EASY,MEDIUM,HARD};
	Diffuculty current_difficulty=EASY;
    bool eyestate=1;

};

#endif // TABLEIO_H
