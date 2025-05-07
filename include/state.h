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
    BitBoard pieces[2][6];
    void print();
    int material(int color);
    void reset();
    BitBoard piecesMask(int color);
    BitBoard getControlledSquares(int color);
    BitBoard piecesMask();
};


#endif