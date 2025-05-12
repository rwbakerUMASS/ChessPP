#ifndef CHESSPP_BITBOARD_H
#define CHESSPP_BITBOARD_H

#include <iostream>
#include <string>
#include <stdint.h>
#include <vector>
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
    BitBoard intersect(BitBoard other);
    BitBoard join(BitBoard other);
    BitBoard invert();
    bool isEmpty();
    bool any();
    vector<int> findAllSet();
    void print();
    int pieceCount();
};

#endif