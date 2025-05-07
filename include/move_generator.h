#ifndef CHESSPP_MOVEGEN_H
#define CHESSPP_MOVEGEN_H

#include <iostream>
#include <string>
#include <stdint.h>
#include "bitboard.h"
#include "state.h"
#include "attack_tables.h"
#include "enums.h"
using namespace std;

class MoveGenerator
{
private:
    BitBoard get_pawn_moves(int square, int color, GameState state);
    BitBoard get_knight_moves(int square, int color, GameState state);
    BitBoard get_bishop_moves(int square, int color, GameState state);
    BitBoard get_rook_moves(int square, int color, GameState state);
    BitBoard get_queen_moves(int square, int color, GameState state);
    BitBoard get_king_moves(int square, int color, GameState state);
public:
    MoveGenerator();
    ~MoveGenerator();
    BitBoard get_moves(int type, int square, int color, GameState state);
};

#endif