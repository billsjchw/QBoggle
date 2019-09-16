#ifndef CONFIGURATIONWINDOW_H
#define CONFIGURATIONWINDOW_H

#include <QWidget>
#include "BoardEdit.h"

class ConfigurationWindow: public QWidget {
    Q_OBJECT
public:
    explicit ConfigurationWindow(QWidget *parent = nullptr);
    virtual ~ConfigurationWindow();
public slots:
    void startWithCustom();
    void startWithDefault();
private:
    BoardEdit *boardEdit;
    static const int WIDTH = 580;
    static const int HEIGHT = 470;
};

#endif // CONFIGURATIONWINDOW_H
