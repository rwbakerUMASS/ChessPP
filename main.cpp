#include <iostream>
#include <string>
#include "state.h"

using namespace std;

int main()
{
    GameState bb = GameState();
    bb.print();
    GameState bb2 = GameState();
    bb2.reset();
    bb.print();
    bb2.print();
    cout << bb2.piecesMask(white) << endl;
    cout << bb2.piecesMask(black) << endl;
    return 1;
}