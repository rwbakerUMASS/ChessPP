#ifndef CHESSPP_BITBOARD_H
#define CHESSPP_BITBOARD_H

#include <iostream>
#include <string>
using namespace std;

class BitBoard
{
private:
    int pieceCountHelper(uint64_t board);
public:
    BitBoard();
    BitBoard(uint64_t board);
    ~BitBoard();
    uint64_t board;
    bool checkSquare(int square);
    void setSquare(int square);
    bool popSquare(int square);
    void print();
    int pieceCount();
};

#endif