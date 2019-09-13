#include "BoggleWindow.h"
#include "lexicon.h"

#include <QFile>
#include <QHBoxLayout>
#include <QTextEdit>
#include <iostream>
#include <QDebug>

BoggleWindow::BoggleWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("QBoggle!");
    this->setFixedSize(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);

    me = new WordListWidget(this, "Me");
    computer = new WordListWidget(this, "Computer");
    board = new Board(this);
    console = new Console(this);

    me->setGeometry(20, 20, 230, 300);
    board->setGeometry(230, 0, 300, 300);
    computer->setGeometry(800 - 50 - 200, 20, 230, 300);
    console->setGeometry(30, 320, 740, 260);

    connect(console, &Console::newLineWritten, this, &BoggleWindow::handleNewLine);

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
}

void BoggleWindow::handleNewLine(QString newLine) {
    if (!newLine.length()) {
    } else if (!me->contains(newLine) && newLine.length() >= BASIC_WORD_LENGTH && lexicon->contains(newLine.toStdString()) && board->contains(newLine)) {
        me->addWord(newLine.toLower());
        me->addScore(newLine.length() - BASIC_WORD_LENGTH + 1);
    }
}
