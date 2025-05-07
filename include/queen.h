#ifndef CHESSPP_QUEEN_H
#define CHESSPP_QUEEN_H

#include <iostream>
#include <string>
#include <stdint.h>
#include "bitboard.h"
#include "state.h"
#include "rook.h"
#include "bishop.h"
#include "piece.h"
using namespace std;

class Queen :  public Piece, public Rook, public Bishop
{
private:
public:
    Queen(int square) : Piece(square), Rook(square), Bishop(square) {};
    BitBoard get_moves(GameState state, int color);
};

#endif