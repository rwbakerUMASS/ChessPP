#include <iostream>
#include <string>
#include "state.h"
#include "attack_tables.h"
#include "king.h"
using namespace std;

int main()
{
    GameState gs = GameState();
    gs.pieces[white][knight].setSquare(17);
    gs.pieces[black][knight].setSquare(22);
    gs.pieces[white][rook].setSquare(20);
    gs.print();
    King k = King(23);
    k.get_moves(gs,white).print();
    return 1;
}