#include "bishop.h"

BitBoard Bishop::get_moves(GameState state, int color)
{
    BitBoard moves;
    BitBoard allPieces = state.piecesMask();
    BitBoard myPieces = state.piecesMask(color);
    
    int directions[4] = {-9, -7, 7, 9};

    for (int d = 0; d < 4; ++d)
    {
        int step = directions[d];
        int sq = this->square;

        while (true)
        {
            int nextSq = sq + step;

            // Edge of board checks
            if (nextSq < 0 || nextSq >= 64) break;
            int fileDelta = abs((nextSq % 8) - (sq % 8));
            if (fileDelta != 1) break;

            sq = nextSq;

            if (myPieces.checkSquare(sq)) break;

            moves.setSquare(sq);

            if (allPieces.checkSquare(sq)) break;
        }
    }

    return moves;
}