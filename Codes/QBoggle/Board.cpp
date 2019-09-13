#include "Board.h"
#include "Cube.h"

#include <QGridLayout>
#include <QString>
#include <QtGlobal>
#include <QThread>
#include <QDebug>

const QString Board::STANDARD_CUBES[16]  = {
        "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
        "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
        "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
        "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

const QString Board::BIG_BOGGLE_CUBES[25]  = {
        "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
        "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
        "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
        "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
        "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

Board::Board(QWidget *parent, int size, const QString *cubeLetters) : QWidget(parent)
{
    this->size = size;
    this->cubes = new Cube*[size * size];
    this->letters = new QString[size * size];
    for (int i = 0; i < size * size; ++i)
        this->letters[i] = cubeLetters[i];
    shake();

    QGridLayout *layout = new QGridLayout();
    layout->setMargin(20);
    layout->setSpacing(10);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            this->cubes[index(i, j)] = new Cube(this);
            layout->addWidget(this->cubes[index(i, j)], i, j, Qt::AlignmentFlag::AlignCenter);
        }
    }
    setLayout(layout);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            this->cubes[index(i, j)]->setLetter(this->letters[index(i, j)].front());
        }
    }
    // this->setStyleSheet("background-color:grey; border: 3px solid");
}

Board::~Board()
{
    if (cubes) delete[] cubes;
    if (letters) delete[] letters;
}

bool Board::contains(const QString & word) {
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            if (letters[index(i, j)].front() == word.front().toUpper()) {
                QList<QPoint> path;
                path.append(QPoint(i, j));
                if (findPath(word, path)) {
                    showPath(path);
                    return true;
                }
            }
    return false;
}

void Board::shake()
{
    // Shake Cubes
    for (int i = 0; i < size * size; ++i) {
        int k = qrand() % 6;
        QString afterShake;
        for (int j = 0; j < 6; ++j)
            afterShake.append(letters[i].at((j + k) % 6));
        letters[i] = afterShake;
    }
    for (int i = 0; i < size * size; ++i) {
        int k = i + qrand() % (size * size - i);
        qSwap(letters[i], letters[k]);
    }
}

bool Board::findPath(const QString & word, QList<QPoint> &path) {
    if (path.length() == word.length())
        return true;
    for (int di : {-1, 0, 1})
        for (int dj : {-1, 0, 1})
            if (di || dj) {
                QPoint next = path.back() + QPoint(di, dj);
                if (inside(next) && !path.contains(next) && letters[index(next)].front() ==  word.at(path.length()).toUpper()) {
                    path.append(next);
                    if (findPath(word, path))
                        return true;
                    path.removeLast();
                }
            }
    return false;
}

void Board::showPath(const QList<QPoint> &path) {
    for (QPoint p : path)
        cubes[index(p)]->select();
    repaint();
    QThread::msleep(800);
    for (QPoint p : path)
        cubes[index(p)]->cancel();
}
