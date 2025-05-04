#include "rook.h"

BitBoard Rook::get_moves(GameState state, int color)
{
    int rank = this->square/8;
    int file = this->square%8;
    BitBoard row = BitBoard(255ULL << (rank * 8));
    BitBoard col = BitBoard(72340172838076673ULL << file);
    BitBoard allPieces = state.piecesMask();
    BitBoard myPieces = state.piecesMask(color);
    row.popSquare(this->square);
    if (!row.intersect(allPieces).isEmpty())
    {
        bool foundPiece = false;
        for (int i = this->square-1; i%8 != 7; i--)
        {
            if(foundPiece)
            {
                row.popSquare(i);
                continue;
            }
            if(allPieces.checkSquare(i))
            {
                foundPiece = true;
                if(myPieces.checkSquare(i))
                {
                    row.popSquare(i);
                }
            }
        }

        foundPiece = false;
        for (int i = this->square+1; i%8 != 0; i++)
        {
            if(foundPiece)
            {
                row.popSquare(i);
                continue;
            }
            if(allPieces.checkSquare(i))
            {
                foundPiece = true;
                if(myPieces.checkSquare(i))
                {
                    row.popSquare(i);
                }
            }
        }
    }
    return row.join(col);
}