#ifndef CHESSPP_KNIGHT_H
#define CHESSPP_KNIGHT_H

#include <iostream>
#include <string>
#include <stdint.h>
#include "bitboard.h"
#include "state.h"
#include "piece.h"
using namespace std;

class Knight : public Piece
{
private:
public:
    Knight(int square) : Piece(square) {};
    BitBoard get_moves(GameState state, int color);
};

#endif