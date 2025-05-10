#include <stdint.h>
#include "enums.h"
#include "bitboard.h"
using namespace std;

class MoveTable
{
private:
    /* data */
protected:
    BitBoard moves[2][64];
    BitBoard attacks[2][64];
public:

    /*
    @brief Gets all squares the given pieces could move to, regardless of legality

    @param square current square of piece
    @param color color of piece
    @returns New BitBoard containing all moves
    */
    BitBoard get_moves(int square, int color);
};

class PawnMoveTable : public MoveTable
{
private:
    /* data */
public:
    PawnMoveTable(/* args */);

    /*
    @brief Gets all squares the given pawn could attack, regardless of legality
    
    @param square current square of pawn
    @param color color of pawn
    @returns New BitBoard containing all attacks
    */
    BitBoard get_attacks(int square, int color);
};

class KnightMoveTable : public MoveTable
{
private:
    /* data */
public:
    KnightMoveTable(/* args */);
};