#ifndef BOARD_H
#define BOARD_H

#include "Cube.h"

#include <QWidget>
#include <QString>
#include <QPoint>
#include <QList>

class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = nullptr, int size = 5, const QString *cubeLetters = BIG_BOGGLE_CUBES);
    virtual ~Board();
    bool contains(const QString & word);

private:
    void shake();
    bool findPath(const QString & word, QList<QPoint> &path);
    void showPath(const QList<QPoint> &path);

signals:

public slots:

private:
    int size;
    Cube **cubes;
    QString *letters;
    inline int index(int i, int j) { return i * size + j; }
    inline int index(QPoint p) { return index(p.x(), p.y()); }
    inline bool inside(QPoint p) { return p.x() >= 0 && p.x() < size && p.y() >= 0 && p.y() < size; }
    static const QString STANDARD_CUBES[16];
    static const QString BIG_BOGGLE_CUBES[25];
};

#endif // BOARD_H
