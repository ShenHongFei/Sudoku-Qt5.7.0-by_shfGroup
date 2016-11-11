#include "mainwindow.h"
#include <QString>
#include <QDebug>
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QVBoxLayout>
#include <string>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    tio = new TableIO(ui->tableWidget);
    lcdtimer = new Timer(ui->timerLCD);
    countLCD = ui->countLCD;
    setFixedSize(541, 681);

    ui->tableWidget->setStyleSheet("gridline-color: black");

    QFont font = ui->tableWidget->font();
    font.setBold(false);
    font.setPointSize(25);
    ui->tableWidget->setFont(font);

    setWindowTitle(QObject::tr("Sudoku"));
    setWindowIcon(QIcon(":/sudoku"));

    ui->eyeButton->setIcon(QIcon(":/EyeOffIcon"));

    connect(ui->tableWidget,
        &QTableWidget::currentCellChanged,
        tio,
        &TableIO::drawEyeBackground);
    connect(ui->tableWidget,
        &QTableWidget::currentCellChanged,
        this,
        &MainWindow::setRemainCell);

    connect(ui->comboBox,
        static_cast<void (QComboBox:: *)(int)>(&QComboBox::currentIndexChanged),
        tio,
        &TableIO::comboBoxChanged);

    connect(ui->newGameButton, &QPushButton::clicked, tio, &TableIO::newGame);
    connect(ui->newGameButton, &QPushButton::clicked, this, &MainWindow::setRemainCell);
    connect(ui->clearButton, &QPushButton::clicked, tio, &TableIO::clear);
    connect(ui->hintButton, &QPushButton::clicked, tio, &TableIO::hint);
    connect(ui->checkAnsButton, &QPushButton::clicked, tio, &TableIO::checkAns);
    connect(ui->checkAnsButton, &QPushButton::clicked, lcdtimer, &Timer::pause);
    connect(ui->newGameButton, &QPushButton::clicked, lcdtimer, &Timer::start);
    connect(ui->pauseButton, &QPushButton::clicked, lcdtimer, &Timer::pause);
    connect(ui->pauseButton, &QPushButton::clicked, this, &MainWindow::pause);
    connect(ui->eyeButton, &QPushButton::clicked, tio, &TableIO::changeEyestate);
    connect(ui->eyeButton, &QPushButton::clicked, this, &MainWindow::changeEyeIcon);
    connect(ui->hintButton, &QPushButton::clicked, this, &MainWindow::setRemainCell);
    connect(ui->checkAnsButton, &QPushButton::clicked, this, &MainWindow::setRemainCell);
    connect(ui->clearButton, &QPushButton::clicked, this, &MainWindow::setRemainCell);
    connect(tio, &TableIO::ansright, this, &MainWindow::success);
    connect(tio, &TableIO::answrong, this, &MainWindow::failed);


}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_aboutButton_clicked() {
    aboutui = new Ui::AboutDialog;
    QDialog *aboutDialog = new QDialog(this);
    aboutui->setupUi(aboutDialog);
    aboutDialog->show();
}

void MainWindow::on_helpButton_clicked() {
    helpui = new Ui::HelpDialog;
    QDialog *helpDialog = new QDialog(this);
    helpui->setupUi(helpDialog);
    helpDialog->exec();
}

void MainWindow::setRemainCell() {
    int count = 0;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            QString str = ui->tableWidget->item(i, j)->text();
            if (str.isEmpty()) {
                ++count;
            }
        }
    }
    countLCD->display(count);
}

void MainWindow::pause() {
    QWidget *pausewindow = new QWidget(this, Qt::FramelessWindowHint);
    pausewindow->setGeometry(0, 681 - 541, 541, 541);
    pausewindow->setObjectName("pausewindow");
    pausewindow->setStyleSheet("#pausewindow {background-color:rgba(153,204,255,150);}");

    QPushButton *pausebutton = new QPushButton(pausewindow);
   // QVBoxLayout *layout = new QVBoxLayout(pausewindow);
   // layout->addWidget(pausebutton);
    pausebutton->setIcon(QIcon("://res/play.png"));
    pausebutton->setIconSize(QSize(541, 541));
    pausebutton->setGeometry(0, 0 ,541, 541);
    pausebutton->setFlat(true);
    pausewindow->show();

    QWidget *blockwindow = new QWidget(this, Qt::FramelessWindowHint);
    blockwindow->setGeometry(0, 0, 541, 681 - 541);
    blockwindow->setObjectName("blockwindow");
    blockwindow->setStyleSheet("#blockwindow {background-color:rgba(0,0,0,0);}");
    blockwindow->show();

    connect(pausebutton, &QPushButton::clicked, pausewindow, &QWidget::close);
    connect(pausebutton, &QPushButton::clicked, blockwindow, &QWidget::close);
    connect(pausebutton, &QPushButton::clicked, lcdtimer, &Timer::resume);
    
}

void MainWindow::changeEyeIcon() {
    if (eyestate) {
        ui->eyeButton->setIcon(QIcon(":/EyeOnIcon"));
    } else {
        ui->eyeButton->setIcon(QIcon(":/EyeOffIcon"));
    }
    eyestate = !eyestate;
}

void MainWindow::success() {
    
    QWidget *successwindow = new QWidget(this, Qt::FramelessWindowHint);
    successwindow->setGeometry(0, 681 - 541, 541, 541);
    successwindow->setObjectName("successwindow");
    successwindow->setStyleSheet("#successwindow {background-color:rgba(255,255,255,120);}");

    QPushButton *successbutton = new QPushButton(successwindow);
   // QVBoxLayout *layout = new QVBoxLayout(successwindow);
   // layout->addWidget(successbutton);
    successbutton->setIcon(QIcon(":/balloon"));
    successbutton->setIconSize(QSize(541, 541));
    successbutton->setGeometry(0, 0 ,541, 541);
    successbutton->setFlat(true);
    successwindow->show();

    QWidget *blockwindow = new QWidget(this, Qt::FramelessWindowHint);
    blockwindow->setGeometry(0, 0, 541, 681 - 541);
    blockwindow->setObjectName("blockwindow");
    blockwindow->setStyleSheet("#blockwindow {background-color:rgba(0,0,0,0);}");
    blockwindow->show();
    connect(successbutton, &QPushButton::clicked, successwindow, &QWidget::close);
    connect(successbutton, &QPushButton::clicked, blockwindow, &QWidget::close);
}

void MainWindow::failed() {

    QWidget *failedwindow = new QWidget(this, Qt::FramelessWindowHint);
    failedwindow->setGeometry(0, 681 - 541, 541, 541);
    failedwindow->setObjectName("failedwindow");
    failedwindow->setStyleSheet("#failedwindow {background-color:rgba(0,0,0,30);}");

    QPushButton *failedbutton = new QPushButton(failedwindow);
    // QVBoxLayout *layout = new QVBoxLayout(failedwindow);
    // layout->addWidget(failedbutton);
    failedbutton->setIcon(QIcon(":/failed"));
    failedbutton->setIconSize(QSize(541, 541));
    failedbutton->setGeometry(0, 0, 541, 541);
    failedbutton->setFlat(true);
    failedwindow->show();

    QWidget *blockwindow = new QWidget(this, Qt::FramelessWindowHint);
    blockwindow->setGeometry(0, 0, 541, 681 - 541);
    blockwindow->setObjectName("blockwindow");
    blockwindow->setStyleSheet("#blockwindow {background-color:rgba(0,0,0,0);}");
    blockwindow->show();
    connect(failedbutton, &QPushButton::clicked, failedwindow, &QWidget::close);
    connect(failedbutton, &QPushButton::clicked, blockwindow, &QWidget::close);
}
