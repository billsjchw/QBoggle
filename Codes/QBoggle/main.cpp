#include "BoggleWindow.h"
#include "ConfigurationWindow.h"
#include "lexicon.h"
#include <QApplication>
#include <iostream>
#include <QtGlobal>
#include <QDateTime>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//     uint seed = QDateTime::currentDateTime().toTime_t();
//     uint seed = 1568391688;
//     uint seed = 1568470650;
    uint seed = 1568553560;
    qDebug() << seed;
    qsrand(seed);

//    BoggleWindow *w = new BoggleWindow;
//    w->show();
    ConfigurationWindow *w = new ConfigurationWindow;
    w->show();

    return a.exec();
}
