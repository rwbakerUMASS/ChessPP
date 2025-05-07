#include "move_generator.h"

const MoveGenerator GlobalMoveGenerator = MoveGenerator();

MoveGenerator::MoveGenerator()
{

}
MoveGenerator::~MoveGenerator()
{

}

BitBoard MoveGenerator::get_pawn_moves(int square, int color, GameState state) const
{
    /*TEMPORARY WILL HAVE TO FIND HOW I AM GOING TO GENERATE TABLES ONCE*/
    static PawnMoveTable pt = PawnMoveTable();

    BitBoard allPieces = state.piecesMask();
    BitBoard otherPieces = state.piecesMask(!color);
    BitBoard moves = pt.get_attacks(square, color).intersect(otherPieces);
    moves = moves.join(pt.get_moves(square, color).intersect(allPieces.invert()));
    /*
    This does not take into account the first pawn double move being blocked!
    Will worry about en passant later
    */
    return moves;
}

BitBoard MoveGenerator::get_knight_moves(int square, int color, GameState state) const
{
    /*TEMPORARY WILL HAVE TO FIND HOW I AM GOING TO GENERATE TABLES ONCE*/
    static KnightMoveTable kt = KnightMoveTable();

    BitBoard myPieces = state.piecesMask(color);
    BitBoard otherPieces = state.piecesMask(!color);
    BitBoard moves = kt.get_moves(square, color).intersect(myPieces.invert());
    return moves;
}

BitBoard MoveGenerator::get_bishop_moves(int square, int color, GameState state) const
{
    BitBoard moves;
    BitBoard allPieces = state.piecesMask();
    BitBoard myPieces = state.piecesMask(color);
    
    int directions[4] = {-9, -7, 7, 9};

    for (int d = 0; d < 4; ++d)
    {
        int step = directions[d];
        int sq = square;

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

BitBoard MoveGenerator::get_rook_moves(int square, int color, GameState state) const
{
    BitBoard moves;
    BitBoard allPieces = state.piecesMask();
    BitBoard myPieces = state.piecesMask(color);
    
    int directions[4] = {-8, 8, -1, 1};

    for (int d = 0; d < 4; ++d)
    {
        int step = directions[d];
        int sq = square;

        while (true)
        {
            sq += step;

            // Edge of board checks
            if (sq < 0 || sq >= 64) break;
            if ((step == -1 || step == 1) && (sq / 8 != square / 8)) break;

            if (myPieces.checkSquare(sq)) break;

            moves.setSquare(sq);

            if (allPieces.checkSquare(sq)) break;
        }
    }

    return moves;
}

BitBoard MoveGenerator::get_queen_moves(int square, int color, GameState state) const
{
    BitBoard rookMoves = get_rook_moves(square, color, state);
    BitBoard bishopMoves = get_bishop_moves(square, color, state);
    return rookMoves.join(bishopMoves);
}

BitBoard MoveGenerator::get_king_moves(int square, int color, GameState state) const
{
    BitBoard myPieces = state.piecesMask(color);
    BitBoard moves;
    int directions[8] = {-9, -8, -7, 1, 9, 8, 7, -1};
    for (int d = 0; d < 8; ++d) {

        int nextSq = square + directions[d];

        if (nextSq < 0 || nextSq >= 64) continue;
        int fileDelta = abs((nextSq % 8) - (square % 8));
        if (fileDelta > 1) continue;
        if (myPieces.checkSquare(nextSq)) continue;

        moves.setSquare(nextSq);
    }

    return moves;
}

BitBoard MoveGenerator::get_moves(int type, int square, int color, GameState state) const
{
    BitBoard moves;
    switch (type)
    {
    case pawn:
        return get_pawn_moves(square, color, state);
    case knight:
        return get_knight_moves(square, color, state);
    case bishop:
        return get_bishop_moves(square, color, state);
    case rook:
        return get_rook_moves(square, color, state);
    case queen:
        return get_queen_moves(square, color, state);
    case king:
        return get_king_moves(square, color, state);
    
    default:
        cout << "ERROR: INVALID PIECE TYPE\n";
        exit(1);
    }
}