#include <iostream>
#include "lexicon.h"
#include "board.h"
#include "functions.h"

int main() {
    Lexicon lexicon("EnglishWords.txt");
    
    Board board = {
        Row{ "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM" },
        Row{ "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW" },
        Row{ "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT" },
        Row{ "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU" },
        Row{ "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU" }
    };

    wordsCount(board, lexicon);

    return 0;
}