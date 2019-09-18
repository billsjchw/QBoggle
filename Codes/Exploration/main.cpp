#include "lexicon.h"
#include "board.h"
#include "functions.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>

static int energy(const Board &board, const Lexicon &lexicon) {
    // return wordsCount(board, lexicon);
    // return -maxWordLength(board, lexicon);
    return -score(board, lexicon);
}

static Board shake(const Board &board) {
    Board boardNew = board;
    if (std::rand() % 2) {
        int i = std::rand() % SIZE;
        int j = std::rand() % SIZE;
        int t = std::rand() % 6;
        std::string afterShake;
        for (int k = 0; k < 6; ++k)
            afterShake.push_back(boardNew[i][j][(k + t) % 6]);
        boardNew[i][j] = afterShake;
    } else {
        int i1 = std::rand() % SIZE;
        int j1 = std::rand() % SIZE;
        int i2 = std::rand() % SIZE;
        int j2 = std::rand() % SIZE;
        std::swap(boardNew[i1][j1], boardNew[i2][j2]);
    }
    return boardNew;
}

static void printBoard(const Board &board) {
    for (int i = 0; i < SIZE; ++i) {
        for (const std::string &cube : board[i])
            std::cout << cube << " ";
        std::cout << std::endl;
    }
}

int main() {
    Lexicon lexicon("EnglishWords.txt");
    
    Board board = {
        Row{ "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM" },
        Row{ "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW" },
        Row{ "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT" },
        Row{ "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU" },
        Row{ "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU" }
    };

    std::srand((unsigned) std::time(nullptr));

    const double tMax = 100000.0;
    const double tMin = 0.001;
    const double c = 0.99;
    int e = energy(board, lexicon);
    int eMin = e;
    Board boardBest = board;
    for (double t = tMax; t > tMin; t *= c) {
        std::cout << t << std::endl;
        Board boardNew = shake(board);
        int eNew = energy(boardNew, lexicon);
        if (eNew < e || (double) std::rand() / RAND_MAX < std::exp(-(eNew - e) / t)) {
            e = eNew;
            board = boardNew;
            if (e < eMin) {
                eMin = e;
                boardBest = board;
            }
        }
    }
    std::cout << eMin << std::endl;
    printBoard(boardBest);

    return 0;
}