#ifndef CHESSPP_ROOK_H
#define CHESSPP_ROOK_H

#include <iostream>
#include <string>
#include <stdint.h>
#include "bitboard.h"
#include "state.h"
#include "piece.h"
using namespace std;

class Rook : public Piece
{
private:
public:
    Rook(int square) : Piece(square) {};
    BitBoard get_moves(GameState state, int color);
};

#endif