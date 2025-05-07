#include "queen.h"
#include "attack_tables.h"

BitBoard Queen::get_moves(GameState state, int color)
{
    BitBoard rookMoves = Rook::get_moves(state, color);
    BitBoard bishopMoves = Bishop::get_moves(state, color);
    return rookMoves.join(bishopMoves);
}