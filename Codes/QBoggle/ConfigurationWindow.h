#ifndef CONFIGURATIONWINDOW_H
#define CONFIGURATIONWINDOW_H

#include <QWidget>

class ConfigurationWindow: public QWidget {
public:
    explicit ConfigurationWindow(QWidget *parent = nullptr);
    virtual ~ConfigurationWindow();
};

#endif // CONFIGURATIONWINDOW_H
