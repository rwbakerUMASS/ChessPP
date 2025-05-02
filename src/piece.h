#ifndef CHESSPP_PIECE_H
#define CHESSPP_PIECE_H

#include <iostream>
#include <string>
#include <stdint.h>
#include "bitboard.h"
#include "state.h"
using namespace std;

class Piece
{
private:
public:
    int square;
    Piece(int square);
    virtual BitBoard get_moves(GameState state, int color) = 0;
};

#endif