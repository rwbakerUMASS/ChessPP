#ifndef CHESSPP_PAWN_H
#define CHESSPP_PAWN_H

#include <iostream>
#include <string>
#include <stdint.h>
#include "bitboard.h"
#include "state.h"
#include "piece.h"
using namespace std;

class Pawn : public Piece
{
private:
public:
    Pawn(int square) : Piece(square) {};
    BitBoard get_moves(GameState state, int color);
};

#endif