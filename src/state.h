#ifndef CHESSPP_STATE_H
#define CHESSPP_STATE_H

#include <string>
#include <iostream>
#include "bitboard.h"
#include "enums.h"

using namespace std;

class GameState
{
private:
    /* data */
public:
    GameState(/* args */);
    ~GameState();
    BitBoard pieces[12];
    void print();
    int material(int side);
    void reset();
    uint64_t piecesMask(int side);
};


#endif