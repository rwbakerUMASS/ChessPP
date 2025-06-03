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
    BitBoard get_pawn_moves(int square, int color, const GameState& state) const;
    BitBoard get_knight_moves(int square, int color, const GameState& state) const;
    BitBoard get_bishop_moves(int square, int color, const GameState& state) const;
    BitBoard get_rook_moves(int square, int color, const GameState& state) const;
    BitBoard get_queen_moves(int square, int color, const GameState& state) const;
    BitBoard get_king_moves(int square, int color, const GameState& state) const;
public:
    MoveGenerator();
    ~MoveGenerator();

    /*
    @brief Gets all moves of a piece, given the current game state
    
    @note This does not guarantee the move is legal, eg. checks, pins.
    
    @param type piece type
    @param square piece's current square
    @param color piece's color
    @param state Current state of the board
    @returns New BitBoard containing all moves
    */
    BitBoard get_moves(int type, int square, int color, const GameState& state) const;
};

extern const MoveGenerator GlobalMoveGenerator;

#endif