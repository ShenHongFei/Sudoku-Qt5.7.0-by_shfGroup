#include "tableio.h"
#include <QDebug>
#include <QString>

TableIO::TableIO(QTableWidget *uitable) : data(new Data), table(uitable) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            QTableWidgetItem *item = new QTableWidgetItem();
            table->setItem(i, j, item);

        }
    }
}

void TableIO::newGame(void) {
    qDebug() << "received new game signal";
    int blanknum;
    switch (current_difficulty) {
    case EASY:blanknum = 20; break;
    case MEDIUM:blanknum = 40; break;
    case HARD:blanknum = 60; break;
    default:
        break;
    }
    data->newPuzzle(blanknum);
    table->setSortingEnabled(0);
    setPuzzle();
}

void TableIO::checkAns(void) {
    qDebug() << "received checkAnsSignal";
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (!table->item(i, j)->text().isEmpty()) {
                int num = table->item(i, j)->text().toInt();
                data->setUserAns(i + 1, j + 1, num);
            } else {
                data->setUserAns(i + 1, j + 1, 0);
            }

        }
    }
    bool result = data->checkUserAns();
    if (result) {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (data->getPuzzle(i + 1, j + 1) == 0) {
                    table->item(i, j)->setForeground(QColor(0, 255, 0));
                }
            }
        }
        emit ansright();
    } else {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (data->getPuzzle(i + 1, j + 1) == 0) {
                    table->item(i, j)->setData(Qt::DisplayRole, QVariant(data->getAns(i + 1, j + 1)));
                    table->item(i, j)->setForeground(QColor(255, 0, 0));
                }
            }
        }
        emit answrong();
    }
}

void TableIO::comboBoxChanged(int index) {
    qDebug() << "ComboBoxChanged:";
    qDebug() << index;
    current_difficulty = Diffuculty(index);
}

void TableIO::clear(void) {
    setPuzzle();
    int r = table->currentItem()->row();
    int c = table->currentItem()->column();
    drawEyeBackground(r, c);
}

void TableIO::hint(void) {
    qDebug() << "hint";
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            QString str = table->item(i, j)->text();
            if (str.isEmpty()) {
                int ans = data->getAns(i + 1, j + 1);
                QTableWidgetItem *item = new QTableWidgetItem(QString::number(ans));
                table->setItem(i, j, item);
                item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                item->setForeground(QColor(255, 204, 0));
                drawBackground();
                return;
            }
        }
    }
}

void TableIO::setPuzzle(void) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            int num = data->getPuzzle(i + 1, j + 1);
            if (num) {
                QTableWidgetItem *item = new QTableWidgetItem(QString::number(num));
                table->setItem(i, j, item);
                //将这些tablewidget设置为不可编辑状态
                table->item(i, j)->setFlags(Qt::ItemFlag(~Qt::ItemIsEditable));
                table->item(i, j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            } else {
                QTableWidgetItem *item = new QTableWidgetItem(QString(""));
                table->setItem(i, j, item);
                //设置text中的数字居中
                table->item(i, j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                item->setForeground(QColor(0, 0, 255));
            }
        }
        drawBackground();
    }
}

/**给九宫格设置基础灰白背景色**/
void TableIO::drawBackground() {
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++) {
            //将其恢复可编辑状态
            table->item(i, j)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled);
            int newr = i / 3;
            int newc = j / 3;
            //设置九宫格中2 4 6 8宫的背景色为白色
            if ((newr + newc) % 2) {
                table->item(i, j)->setBackgroundColor(QColor(255, 255, 255));
            }
            //设置九宫格中1 3 5 7 9宫的背景色为灰色
            else {
                table->item(i, j)->setBackgroundColor(QColor(235, 235, 235));
            }

            //将原题的数据所属方格恢复为不可编辑状态
            if (data->getPuzzle(i + 1, j + 1)) {
                table->item(i, j)->setFlags(Qt::ItemFlag(~Qt::ItemIsEditable));
            }
        }
}

/****天眼模式*****/
/*功能：随着鼠标点击小方格，将该方格所属的行、列、宫均用紫色的背景色显示*/
void TableIO::drawEyeBackground(int row, int column) {
    if (eyestate == 1) {
        //在下一次选中一个小方格时，先将其还原到正常的灰白背景色
        drawBackground();

        if (row == -1 || column == -1) return;
        for (int i = 0; i < 9; i++) {
            //将row行column列设置为可编辑状态
            table->item(row, i)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled);
            table->item(row, i)->setBackgroundColor(QColor(217, 179, 255));   //所属行
            table->item(i, column)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled);
            table->item(i, column)->setBackgroundColor(QColor(217, 179, 255));   //所属列
        }

        int newr = row / 3;
        int newc = column / 3;

        for (int i = newr * 3; i < (newr + 1) * 3; i++)
            for (int j = newc * 3; j < (newc + 1) * 3; j++) {
                //将其所属宫设为可编辑状态
                table->item(i, j)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled);
                table->item(i, j)->setBackgroundColor(QColor(217, 179, 255));    //所属宫
            }
        //将原题的数据所属方格恢复为不可编辑状态
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++) {
                if (data->getPuzzle(i + 1, j + 1)) {
                    table->item(i, j)->setFlags(Qt::ItemFlag(~Qt::ItemIsEditable));
                }
            }
    }
}

void TableIO::changeEyestate() {
    eyestate = !eyestate;
    if (eyestate) {
        drawBackground();
        QModelIndex index = table->currentIndex();
        drawEyeBackground(index.row(), index.column());
    } else {
        drawBackground();
    }
}

void TableIO::setnum(int n){
	QString str=QString("%1").arg(n);
	table->currentItem()->setText(str);
}
