#include "WordTable.h"
#include <QHeaderView>
#include <QScrollBar>

WordTable::WordTable(QWidget *parent, int maxCol) : QTableWidget(parent)
{
    this->maxCol = maxCol;
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
}

void WordTable::resizeToContents() {
    this->resizeColumnsToContents();
    this->resizeRowsToContents();
}

void WordTable::reset()
{
    row = 0;
    col = 0;
    this->setColumnCount(maxCol);
    this->setRowCount(1);
}
