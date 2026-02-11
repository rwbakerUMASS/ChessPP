#include <iostream>
#include <string>
#include "state.h"
#include "logger.h"
#include "raw_material_eval.h"
#include "psq_table_eval.h"
#include "minimax.h"
#include "base_eval.h"

using namespace std;

int main()
{
    SET_LOG_LEVEL(LOG_LEVEL_DEBUG);
    GameState gs = GameState();
    RawMaterialEval rm;
    PSQTableEval psqt;
    MiniMax mm(psqt);
    // gs.loadFen("rnbqkbnr/pppp1ppp/8/4p3/4Q3/8/PPPP1PPP/RNB1KBNR w KQkq - 0 3");
    gs.reset();
    gs.print();

    mm.timeLimit=10000;
    mm.depth=50;
    int color = white;
    for (int i = 0; i < 10; i++)
    {
        gs = mm.selectMove(gs,color);
        color = !color;
        LOG_DEBUG("Turn FEN: " + gs.dumpFen());
    }


    return 1;
}