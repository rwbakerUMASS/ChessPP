#include <iostream>
#include <string>
#include "state.h"
#include "move_generator.h"
using namespace std;

int main()
{
    GameState gs = GameState();
    gs.pieces[white][knight].setSquare(17);
    gs.pieces[black][knight].setSquare(22);
    gs.pieces[white][rook].setSquare(20);
    gs.print();
    MoveGenerator mvgen = MoveGenerator();
    mvgen.get_moves(king+1,24,white,gs).print();
    return 1;
}