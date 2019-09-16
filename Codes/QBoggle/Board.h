#ifndef BOARD_H
#define BOARD_H

#include "Cube.h"
#include "lexicon.h"

#include <QWidget>
#include <QString>
#include <QPoint>
#include <QList>
#include <QSet>

class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(int size, const QString *cubeLetters, QWidget *parent = nullptr);
    virtual ~Board();
    bool contains(const QString &word);
    QSet<QString> allWords(const Lexicon *lexicon);
    void clearPathSelected();
    bool pathSelectedExtendable();

signals:
    void newWordSelected(QString newWord);

public slots:
    void handleCubeClicked();

private:
    int size;
    Cube **cubes;
    QString *letters;
    QList<QPoint> pathSelected;

    void shake();
    bool findPath(const QString &word, QList<QPoint> &path);
    void showPath(const QList<QPoint> &path);
    void findAllWords(QList<QPoint> &path, QSet<QString> &wordSet, const Lexicon *lexicon);
    void mousePressEvent(QMouseEvent *event);
    inline int index(int i, int j) { return i * size + j; }
    inline int index(QPoint p) { return index(p.x(), p.y()); }
    inline bool inside(QPoint p) { return p.x() >= 0 && p.x() < size && p.y() >= 0 && p.y() < size; }
    static bool compactQu(QString &word);
    static void extendQ(QString &word);
};

#endif // BOARD_H
