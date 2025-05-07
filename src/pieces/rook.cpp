#include "rook.h"

BitBoard Rook::get_moves(GameState state, int color)
{
    BitBoard moves;
    BitBoard allPieces = state.piecesMask();
    BitBoard myPieces = state.piecesMask(color);
    
    int directions[4] = {-8, 8, -1, 1};

    for (int d = 0; d < 4; ++d)
    {
        int step = directions[d];
        int sq = this->square;

        while (true)
        {
            sq += step;

            // Edge of board checks
            if (sq < 0 || sq >= 64) break;
            if ((step == -1 || step == 1) && (sq / 8 != this->square / 8)) break;

            if (myPieces.checkSquare(sq)) break;

            moves.setSquare(sq);

            if (allPieces.checkSquare(sq)) break;
        }
    }

    return moves;
}