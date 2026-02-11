#include "psq_table_eval.h"
#include "state.h"
#include "enums.h"

int PSQTableEval::evaluate(const GameState& state)
{
    int score = 0;
    for (int color = 0; color < 2; color++)
    {
        for (int piece = 0; piece < 6; piece++)
        {
            BitBoard pieces = state.pieces[color][piece];
            while (pieces.any())
            {
                int square = pieces.findAllSet().back();
                pieces.popSquare(square);
                switch (piece)
                {
                case pawn:
                    score += ((color == white) ? PAWN_PSQT[square] : -PAWN_PSQT[FLIP[square]]);
                    break;
                case knight:
                    score += ((color == white) ? KNIGHT_PSQT[square] : -KNIGHT_PSQT[FLIP[square]]);
                    break;
                case bishop:
                    score += ((color == white) ? BISHOP_PSQT[square] : -BISHOP_PSQT[FLIP[square]]);
                    break;
                case rook:
                    score += ((color == white) ? ROOK_PSQT[square] : -ROOK_PSQT[FLIP[square]]);
                    break;
                case queen:
                    score += ((color == white) ? QUEEN_PSQT[square] : -QUEEN_PSQT[FLIP[square]]);
                    break;
                }
            }
        }
    }

    return score;
}