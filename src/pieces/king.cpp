#include "king.h"
#include "attack_tables.h"

BitBoard King::get_moves(GameState state, int color)
{
    BitBoard myPieces = state.piecesMask(color);
    BitBoard moves;
    int directions[8] = {-9, -8, -7, 1, 9, 8, 7, -1};
    for (int d = 0; d < 8; ++d) {

        int nextSq = this->square + directions[d];

        if (nextSq < 0 || nextSq >= 64) continue;
        int fileDelta = abs((nextSq % 8) - (this->square % 8));
        if (fileDelta > 1) continue;
        if (myPieces.checkSquare(nextSq)) continue;

        moves.setSquare(nextSq);
    }

    return moves;
}