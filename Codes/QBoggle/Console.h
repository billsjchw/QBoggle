#ifndef CONSOLE_H
#define CONSOLE_H

#include <QObject>
#include <QTextEdit>
#include <QWidget>

class Console : public QTextEdit
{
    Q_OBJECT
public:
    explicit Console(QWidget *parent = nullptr);

signals:
    void newLineWritten(QString newLine);

public slots:
    void write(QString msg);

protected:
    virtual void keyPressEvent(QKeyEvent *event);
};

#endif // CONSOLE_H
