#include "Board.h"
#include "Cube.h"
#include <QGridLayout>
#include <QString>
#include <QtGlobal>
#include <QThread>

Board::Board(int size, const QString *cubeLetters, QWidget *parent) : QWidget(parent)
{
    this->size = size;
    this->cubes = new Cube*[size * size];
    this->letters = new QString[size * size];
    for (int i = 0; i < size * size; ++i)
        this->letters[i] = cubeLetters[i];
    shake();

    QGridLayout *layout = new QGridLayout(this);
    layout->setMargin(20);
    layout->setSpacing(10);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            this->cubes[index(i, j)] = new Cube(this);
            connect(this->cubes[index(i, j)], &Cube::clicked, this, &Board::handleCubeClicked);
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
    QString wordCompacted = word;
    if (!compactQu(wordCompacted))
        return false;
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            if (letters[index(i, j)].front() == wordCompacted.front().toUpper()) {
                QList<QPoint> path;
                path.append(QPoint(i, j));
                if (findPath(wordCompacted, path)) {
                    showPath(path);
                    return true;
                }
            }
    return false;
}

QSet<QString> Board::allWords(const Lexicon *lexicon) {
    QSet<QString> wordSet;
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j) {
            QList<QPoint> path;
            path.append(QPoint(i, j));
            findAllWords(path, wordSet, lexicon);
        }
    return wordSet;
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

void Board::findAllWords(QList<QPoint> &path, QSet<QString> &wordSet, const Lexicon *lexicon) {
    QString word;
    for (QPoint p : path)
        word.append(letters[index(p)].front());
    extendQ(word);
    if (!lexicon->containsPrefix(word.toStdString()))
        return;
    if (lexicon->contains(word.toStdString()))
        wordSet.insert(word);
    for (int di : {-1, 0, 1})
        for (int dj : {-1, 0, 1})
            if (di || dj) {
                QPoint next = path.back() + QPoint(di, dj);
                if (inside(next) && !path.contains(next)) {
                    path.append(next);
                    findAllWords(path, wordSet, lexicon);
                    path.removeLast();
                }
            }
}

void Board::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton)
        clearPathSelected();
}

bool Board::compactQu(QString &word) {
    QString result;
    for (int i = 0; i < word.length(); ++i)
        if (word.at(i).toUpper() != 'Q')
            result.append(word.at(i));
        else if (i + 1 == word.length() || word.at(i + 1).toLower() != 'u')
            return false;
        else {
            ++i;
            result.append('Q');
        }
    word = result;
    return true;
}

void Board::extendQ(QString &word) {
    word.replace('Q', "Qu", Qt::CaseInsensitive);
}

void Board::clearPathSelected() {
    for (QPoint p : pathSelected)
        cubes[index(p)]->cancel();
    pathSelected.clear();
}

bool Board::pathSelectedExtendable() {
    for (int di : {-1, 0, 1})
        for (int dj : {-1, 0, 1}) {
            QPoint next = pathSelected.back() + QPoint(di, dj);
            if (inside(next) && !pathSelected.contains(next))
                return true;
        }
    return false;
}

void Board::handleCubeClicked() {
    Cube *cubeClicked = dynamic_cast<Cube *>(sender());
    QPoint pos;
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            if (cubes[index(i, j)] == cubeClicked)
                pos = QPoint(i, j);
    QPoint delta(0, 0);
    if (!pathSelected.empty())
        delta = pos - pathSelected.back();
    if (!pathSelected.contains(pos) && qAbs(delta.x()) <= 1 && qAbs(delta.y()) <= 1) {
        cubeClicked->select();
        pathSelected.append(pos);
        QString newWord;
        for (QPoint p : pathSelected)
            newWord.append(letters[index(p)].front());
        extendQ(newWord);
        newWordSelected(newWord);
    }
}
