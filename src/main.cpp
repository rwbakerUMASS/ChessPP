#include <iostream>
#include <string>
#include "state.h"
#include "attack_tables.h"

using namespace std;

int main()
{
    PawnMoveTable pt = PawnMoveTable();
    pt.get_attacks(49,black).print();
    pt.get_attacks(8,white).print();
    pt.get_moves(9,white).print();
    KnightMoveTable kt = KnightMoveTable();
    BitBoard bb = BitBoard(1ULL << 36);
    kt.get_moves(0,white).join(bb).print();
    return 1;
}