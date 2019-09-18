#ifndef BOARD_H
#define BOARD_H

#include <array>
#include <string>

const int SIZE = 5;
typedef std::array<std::string, SIZE> Row;
typedef std::array<Row, SIZE> Board;

#endif