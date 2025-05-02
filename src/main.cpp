#include <iostream>
#include <string>
#include "state.h"
#include "attack_tables.h"
#include "pawn.h"
using namespace std;

int main()
{
    GameState gs = GameState();
    gs.pieces[whitePawn].setSquare(18);
    gs.pieces[blackKnight].setSquare(27);
    gs.pieces[blackKing].setSquare(26);
    gs.print();
    Pawn pawn = Pawn(18);
    pawn.get_moves(gs,white).print();
    return 1;
}