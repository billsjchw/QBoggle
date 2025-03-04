#include "WordListWidget.h"
#include "WordTable.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QTableView>

WordListWidget::WordListWidget(QWidget *parent, QString label) : QWidget(parent)
{
    reset();

    QVBoxLayout *layout = new QVBoxLayout();
    QHBoxLayout *headLayout = new QHBoxLayout();

    QLabel *nameLabel = new QLabel(this);
    scoreLabel = new QLabel(this);
    QFont font = nameLabel->font();
    font.setPointSize(20);
    nameLabel->setFont(font);
    scoreLabel->setFont(font);
    nameLabel->setText(label);
    scoreLabel->setText(QString::number(score));

    headLayout->addWidget(nameLabel, 0, Qt::AlignmentFlag::AlignLeft);
    headLayout->addWidget(scoreLabel, 0, Qt::AlignmentFlag::AlignRight);
    layout->addLayout(headLayout);

    QFrame *hline = new QFrame();
    hline->setFrameShape(QFrame::HLine);
    hline->setFrameShadow(QFrame::Sunken);
    layout->addWidget(hline);

    wordTable = new WordTable();
    layout->addWidget(wordTable);

    setLayout(layout);
}

void WordListWidget::addScore(int score)
{
    this->score += score;
    this->scoreLabel->setText(QString::number(this->score));
}

void WordListWidget::addWord(const QString &word)
{
    this->words.append(word);
    this->wordTable->addWord(word);
    this->wordTable->resizeToContents();
}

void WordListWidget::addWords(const QList<QString> &words) {
    this->words.append(words);
    for (const QString &word : words)
        this->wordTable->addWord(word);
    this->wordTable->resizeToContents();
}

void WordListWidget::reset()
{
    this->score = 0;
    this->words.clear();
}

bool WordListWidget::contains(const QString &word) {
    return words.contains(word.toLower());
}
