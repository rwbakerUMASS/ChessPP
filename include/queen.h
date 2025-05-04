#ifndef CHESSPP_QUEEN_H
#define CHESSPP_QUEEN_H

#include <iostream>
#include <string>
#include <stdint.h>
#include "bitboard.h"
#include "state.h"
#include "piece.h"
using namespace std;

class Queen : public Piece
{
private:
public:
    Queen(int square) : Piece(square) {};
    BitBoard get_moves(GameState state, int color);
};

#endif