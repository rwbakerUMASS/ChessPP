#include <iostream>
#include <string>
#include "state.h"
#include "attack_tables.h"
#include "knight.h"
using namespace std;

int main()
{
    GameState gs = GameState();
    gs.pieces[whiteKnight].setSquare(18);
    gs.pieces[blackKnight].setSquare(1);
    gs.pieces[whiteKing].setSquare(3);
    gs.print();
    Knight k = Knight(18);
    k.get_moves(gs,white).print();
    return 1;
}