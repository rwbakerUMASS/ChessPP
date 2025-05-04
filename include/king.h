#ifndef CHESSPP_KING_H
#define CHESSPP_KING_H

#include <iostream>
#include <string>
#include <stdint.h>
#include "bitboard.h"
#include "state.h"
#include "piece.h"
using namespace std;

class King : public Piece
{
private:
public:
    King(int square) : Piece(square) {};
    BitBoard get_moves(GameState state, int color);
};

#endif