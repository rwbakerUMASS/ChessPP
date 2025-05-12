#include <iostream>
#include <string>
#include "state.h"
#include "logger.h"
using namespace std;

int main()
{
    SET_LOG_LEVEL(LOG_LEVEL_ERROR);
    GameState gs = GameState();
    gs.pieces[white][knight].setSquare(65);
    gs.pieces[black][knight].setSquare(22);
    gs.pieces[white][rook].setSquare(20);
    gs.print();
    gs.getControlledSquares(white).print();
    gs.getControlledSquares(black).print();
    return 1;
}