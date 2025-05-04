#include "bishop.h"
#include "attack_tables.h"

BitBoard Bishop::get_moves(GameState state, int color)
{
    /*TEMPORARY WILL HAVE TO FIND HOW I AM GOING TO GENERATE TABLES ONCE*/
    KnightMoveTable kt = KnightMoveTable();

    BitBoard myPieces = state.piecesMask(color);
    BitBoard otherPieces = state.piecesMask(!color);
    BitBoard moves = kt.get_moves(this->square, color).intersect(myPieces.invert());
    return moves;
}