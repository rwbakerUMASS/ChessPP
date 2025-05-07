#include <iostream>
#include <string>
#include "state.h"
using namespace std;

int main()
{
    GameState gs = GameState();
    gs.pieces[white][knight].setSquare(17);
    gs.pieces[black][knight].setSquare(22);
    gs.pieces[white][rook].setSquare(20);
    gs.print();
    gs.getControlledSquares(white).print();
    gs.getControlledSquares(black).print();
    return 1;
}