#include "ConfigurationWindow.h"
#include <QApplication>
#include <QtGlobal>
#include <QDateTime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    uint seed = QDateTime::currentDateTime().toTime_t();
    uint seed = 1568391688;
//    uint seed = 1568470650;
//    uint seed = 1568553560;
//    uint seed = 1568636577;
    qsrand(seed);

    ConfigurationWindow *configurationWindow = new ConfigurationWindow;
    configurationWindow->show();

    return a.exec();
}
