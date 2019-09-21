#ifndef WORDLISTWIDGET_H
#define WORDLISTWIDGET_H

#include "WordTable.h"

#include <QWidget>
#include <QLabel>
#include <QString>
#include <QList>

class WordListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WordListWidget(QWidget *parent = nullptr, QString label = "");
    void addScore(int s);
    void addWord(const QString &word);
    void addWords(const QList<QString> &words);
    void reset();
    bool contains(const QString &word);
signals:

public slots:

private:
    QString label;
    QList<QString> words;
    int score;
    WordTable *wordTable;
    QLabel *scoreLabel;
};

#endif // WORDLISTWIDGET_H
