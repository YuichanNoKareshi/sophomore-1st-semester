#include "WordTable.h"
#include <QHeaderView>
#include <QScrollBar>

WordTable::WordTable(QWidget *parent, int maxCol) : QTableWidget(parent)
{
    this->maxCol = maxCol;//默认值是2
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setShowGrid(false);
    this->horizontalHeader()->hide();
    this->verticalHeader()->hide();
    this->horizontalScrollBar()->hide();
    this->verticalScrollBar()->hide();
    reset();
}

void WordTable::addWord(QString word)
{
    if (col == maxCol) {
        row++;
        this->model()->insertRow(row);
        col = 0;
    }
    this->setItem(row, col, new QTableWidgetItem(word));
    col++;
    this->resizeColumnsToContents();
    this->resizeRowsToContents();
}

void WordTable::reset()
{
    row = 0;
    col = 0;
    this->setColumnCount(maxCol);
    this->setRowCount(1);
    this->resizeColumnsToContents();
    this->resizeRowsToContents();
}

void WordTable::polish()
{
    for (int j=col;j>=0;j--)
        this->takeItem(row,j);//先把最后一行take掉

    for (int i=row-1;i>=0;i--)
        for (int j=maxCol;j>=0;j--)
           this->takeItem(i,j);
    reset();
}
