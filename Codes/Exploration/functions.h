#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "board.h"
#include "lexicon.h"

int wordsCount(const Board &board, const Lexicon &lexicon);
int maxWordLength(const Board &board, const Lexicon &lexicon);
int score(const Board &board, const Lexicon &lexicon);

#endif