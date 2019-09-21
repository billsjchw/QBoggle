#include "BoggleWindow.h"
#include "ConfigurationWindow.h"
#include "lexicon.h"
#include <QFile>
#include <QHBoxLayout>
#include <QTextEdit>
#include <iostream>
#include <QThread>
#include <QSet>
#include <QKeyEvent>
#include <QList>

const QString BoggleWindow::STANDARD_CUBES[16]  = {
        "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
        "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
        "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
        "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

const QString BoggleWindow::BIG_BOGGLE_CUBES[25]  = {
        "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
        "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
        "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
        "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
        "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

BoggleWindow::BoggleWindow(const QString *cubeLetters, QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("QBoggle!");
    this->setFixedSize(WIDTH, HEIGHT);
    this->setAttribute(Qt::WA_DeleteOnClose);

    this->letters = new QString[BOARD_SIZE * BOARD_SIZE];
    for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; ++i)
        this->letters[i] = cubeLetters[i];

    me = new WordListWidget(this, "Me");
    computer = new WordListWidget(this, "Computer");
    board = new Board(BOARD_SIZE, letters, this);
    console = new Console(this);

    me->setGeometry(20, 20, 230, 300);
    board->setGeometry(230, 0, 300, 300);
    computer->setGeometry(800 - 50 - 200, 20, 230, 300);
    console->setGeometry(30, 320, 740, 260);

    connect(console, &Console::newLineWritten, this, &BoggleWindow::handleNewLine);
    connect(board, &Board::newWordSelected, this, &BoggleWindow::handleNewWord);

    QFile qFile(":/res/EnglishWords.txt");
    if (!qFile.open(QIODevice::ReadOnly)) {
        throw new std::runtime_error("Resource file not found!");
    }
    lexicon = new Lexicon(qFile);

    /*
    for (std::string s: lex) {
        std::cout << s << std::endl;
    }
    */
    console->write("Welcome to the game Boggle!\n");
}

BoggleWindow::~BoggleWindow()
{
    delete lexicon;
    delete [] letters;
}

void BoggleWindow::handleNewLine(QString newLine) {
    if (!isPureLetters(newLine))
        return;
    board->clearPathSelected();
    repaint();
    if (!newLine.length()) {
        console->setEnabled(false);
        board->setEnabled(false);
        QSet<QString> wordSet = board->allWords(lexicon);
        QList<QString> words;
        int score = 0;
        for (const QString & word : wordSet)
           if (word.length() >= BASIC_WORD_LENGTH && !me->contains(word.toLower())) {
               words.append(word.toLower());
               score += word.length() - BASIC_WORD_LENGTH + 1;
           }
        computer->addWords(words);
        computer->addScore(score);
    } else if (!me->contains(newLine) && newLine.length() >= BASIC_WORD_LENGTH && lexicon->contains(newLine.toStdString()) && board->contains(newLine)) {
        me->addWord(newLine.toLower());
        me->addScore(newLine.length() - BASIC_WORD_LENGTH + 1);
    }
}

void BoggleWindow::handleNewWord(QString newWord) {
    if (!lexicon->containsPrefix(newWord.toStdString()))
        board->clearPathSelected();
    else if (!me->contains(newWord) && newWord.length() >= BASIC_WORD_LENGTH && lexicon->contains(newWord.toStdString())) {
        me->addWord(newWord.toLower());
        me->addScore(newWord.length() - BASIC_WORD_LENGTH + 1);
        board->clearPathSelected();
    } else if (!board->pathSelectedExtendable())
        board->clearPathSelected();
}

void BoggleWindow::keyPressEvent(QKeyEvent *event) {
    if (isHidden())
        return;
    else if (event->key() == Qt::Key_F1) {
        BoggleWindow *boggleWindow = new BoggleWindow(letters);
        boggleWindow->show();
        close();
    } else if (event->key() == Qt::Key_F2) {
        ConfigurationWindow *configurationWindow = new ConfigurationWindow;
        configurationWindow->show();
        close();
    }
}

bool BoggleWindow::isPureLetters(const QString &s) {
    for (int i = 0; i < s.length(); ++i)
        if (!s.at(i).isLetter())
            return false;
    return true;
}
