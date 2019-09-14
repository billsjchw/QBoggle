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
    BoggleWindow(QWidget *parent = nullptr);
    virtual ~BoggleWindow() override;

public slots:
    void handleNewLine(QString newLine);
    void handleNewWord(QString newWord);

private:
    WordListWidget *me;
    WordListWidget *computer;
    Board *board;
    Console *console;
    Lexicon *lexicon;
    static const int BOGGLE_WINDOW_WIDTH = 800;
    static const int BOGGLE_WINDOW_HEIGHT = 600;
    static const int BASIC_WORD_LENGTH = 4;
};

#endif // BOGGLEWINDOW_H
