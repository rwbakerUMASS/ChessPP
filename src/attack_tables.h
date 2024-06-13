#include <stdint.h>
#include "enums.h"
#include "bitboard.h"
using namespace std;

class MoveTable
{
private:
    /* data */
public:
    // MoveTable(/* args */);
};

class PawnMoveTable : public MoveTable
{
private:
    /* data */
    BitBoard moves[2][56];
    BitBoard attacks[2][56];
public:
    PawnMoveTable(/* args */);
    BitBoard get_moves(int square, int color);
    BitBoard get_attacks(int square, int color);
};
