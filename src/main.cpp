#include <iostream>
#include <string>
#include "state.h"
#include "attack_tables.h"
#include "rook.h"
using namespace std;

int main()
{
    GameState gs = GameState();
    gs.pieces[whiteKnight].setSquare(17);
    gs.pieces[blackKnight].setSquare(22);
    gs.pieces[whiteRook].setSquare(20);
    gs.print();
    Rook k = Rook(20);
    k.get_moves(gs,white).print();
    return 1;
}