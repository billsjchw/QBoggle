#ifndef CUBE_H
#define CUBE_H

#include <QPushButton>
#include <QWidget>

class Cube : public QWidget
{
    Q_OBJECT
public:
    explicit Cube(QWidget *parent = nullptr);
    void setLetter(QChar l);
    void select();
    void cancel();

signals:
    void clicked();

public slots:

private:
    QPushButton *button;
};

#endif // CUBE_H
