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
    BitBoard get_moves(int square, int color);
};

class PawnMoveTable : public MoveTable
{
private:
    /* data */
public:
    PawnMoveTable(/* args */);
    BitBoard get_attacks(int square, int color);
};

class KnightMoveTable : public MoveTable
{
private:
    /* data */
public:
    KnightMoveTable(/* args */);
};