#ifndef CHESSPP_BISHOP_H
#define CHESSPP_BISHOP_H

#include <iostream>
#include <string>
#include <stdint.h>
#include "bitboard.h"
#include "state.h"
#include "piece.h"
using namespace std;

class Bishop : public Piece
{
private:
public:
    Bishop(int square) : Piece(square) {};
    BitBoard get_moves(GameState state, int color);
};

#endif