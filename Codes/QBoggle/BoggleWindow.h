#ifndef BOGGLEWINDOW_H
#define BOGGLEWINDOW_H

#include "Board.h"
#include "Console.h"
#include "WordListWidget.h"
#include "lexicon.h"
#include <QMainWindow>
#include <QString>

class BoggleWindow : public QMainWindow
{
    Q_OBJECT
public:
    BoggleWindow(const QString *cubeLetters = BIG_BOGGLE_CUBES, QWidget *parent = nullptr);
    virtual ~BoggleWindow();

public slots:
    void handleNewLine(QString newLine);
    void handleNewWord(QString newWord);

private:
    virtual void keyPressEvent(QKeyEvent *event);
    static bool isPureLetters(const QString &s);
    WordListWidget *me;
    WordListWidget *computer;
    Board *board;
    Console *console;
    Lexicon *lexicon;
    QString *letters;
    static const int WIDTH = 800;
    static const int HEIGHT = 600;
    static const int BASIC_WORD_LENGTH = 4;
    static const int BOARD_SIZE = 5;
    static const QString STANDARD_CUBES[16];
    static const QString BIG_BOGGLE_CUBES[25];
};

#endif // BOGGLEWINDOW_H
