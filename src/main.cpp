#include <iostream>
#include <string>
#include "state.h"
#include "logger.h"
#include "raw_material_eval.h"
#include "minimax.h"
#include "base_eval.h"

using namespace std;

int main()
{
    SET_LOG_LEVEL(LOG_LEVEL_ERROR);
    GameState gs = GameState();
    RawMaterialEval rm;
    MiniMax mm(rm);
    gs.loadFen("rnbqkbnr/pppp1ppp/8/4p3/4Q3/8/PPPP1PPP/RNB1KBNR w KQkq - 0 3");
    gs.print();

    mm.depth=4;
    gs.makeMove(mm.selectMove(gs,white));
    gs.print();

    // mm.depth=3;
    // gs = mm.selectMove(gs,black);
    // gs.print();

    // mm.depth=3;
    // gs = mm.selectMove(gs,white);
    // gs.print();

    // mm.depth=1;
    // gs = mm.selectMove(gs,black);
    // gs.print();

    return 1;
}