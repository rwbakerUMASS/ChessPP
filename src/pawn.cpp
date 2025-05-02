#include "pawn.h"
#include "attack_tables.h"

BitBoard Pawn::get_moves(GameState state, int color)
{
    /*TEMPORARY WILL HAVE TO FIND HOW I AM GOING TO GENERATE TABLES ONCE*/
    PawnMoveTable pt = PawnMoveTable();

    BitBoard allPieces = state.piecesMask();
    BitBoard otherPieces = state.piecesMask(!color);
    BitBoard moves = pt.get_attacks(this->square, color).intersect(otherPieces);
    moves = moves.join(pt.get_moves(this->square, color).intersect(allPieces.invert()));
    /*
    This does not take into account the first pawn double move being blocked!
    Will worry about en passant later
    */
    return moves;
}