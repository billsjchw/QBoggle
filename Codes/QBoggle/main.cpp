#include "BoggleWindow.h"
#include "lexicon.h"
#include <QApplication>
#include <iostream>
#include <QtGlobal>
#include <QDateTime>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // uint seed = QDateTime::currentDateTime().toTime_t();
    uint seed = 1568391688;
    qDebug() << seed;
    qsrand(seed);

    BoggleWindow w;
    w.show();

    return a.exec();
}
