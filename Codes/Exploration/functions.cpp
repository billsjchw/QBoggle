#include "functions.h"
#include "board.h"
#include "lexicon.h"
#include <vector>
#include <set>
#include <string>
#include <cctype>
#include <iostream>

struct Subscript {
    int i;
    int j;
    explicit Subscript(int i = 0, int j = 0): i(i), j(j) {}
    Subscript operator+(const Subscript &rhs) {
        return Subscript(i + rhs.i, j + rhs.j);
    }
    bool operator==(const Subscript &rhs) {
        return i == rhs.i && j == rhs.j;
    }
};

static bool inside(Subscript sub) {
    return sub.i >= 0 && sub.i < SIZE && sub.j >= 0 && sub.j < SIZE;
}

static std::string extendQ(const std::string &word) {
    std::string result;
    for (char c : word)
        if (toupper(c) == 'Q')
            result.append("Qu");
        else
            result.push_back(c);
    return result;
}

static bool contains(const std::vector<Subscript> &path, Subscript sub) {
    for (Subscript vis : path)
        if (vis == sub)
            return true;
    return false;
}

static void findAllWords(std::vector<Subscript> &path, std::set<std::string> &wordSet, const Board &board, const Lexicon &lexicon) {
    std::string word;
    for (Subscript sub : path)
        word.push_back(board[sub.i][sub.j].front());
    word = extendQ(word);
    if (!lexicon.containsPrefix(word))
        return;
    if (lexicon.contains(word))
        wordSet.insert(word);
    for (int di : {-1, 0, 1})
        for (int dj : {-1, 0, 1})
            if (di || dj) {
                Subscript next = path.back() + Subscript(di, dj);
                if (inside(next) && !contains(path, next)) {
                    path.push_back(next);
                    findAllWords(path, wordSet, board, lexicon);
                    path.pop_back();
                }
            }
}

static std::set<std::string> allWords(const Board &board, const Lexicon &lexicon) {
    std::set<std::string> wordSet;
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j) {
            std::vector<Subscript> path;
            path.push_back(Subscript(i, j));
            findAllWords(path, wordSet, board, lexicon);
        }
    return wordSet;
}

int wordsCount(const Board &board, const Lexicon &lexicon) {
    return allWords(board, lexicon).size();
}

int maxWordLength(const Board &board, const Lexicon &lexicon) {
    std::set<std::string> wordSet = allWords(board, lexicon);
    int result = 0;
    for (const std::string &word : wordSet)
        if (word.length() > result)
            result = word.length();
    return result;
}

int score(const Board &board, const Lexicon &lexicon) {
    const int basicWordLength = 4;
    std::set<std::string> wordSet = allWords(board, lexicon);
    int result = 0;
    for (const std::string &word : wordSet)
        if (word.length() > basicWordLength)
            result += word.length() - basicWordLength + 1;
    return result;
}