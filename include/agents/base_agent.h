#ifndef CHESSPP_BASEAGENT_H
#define CHESSPP_BASEAGENT_H

#include "state.h"
#include "base_eval.h"

using namespace std;

class Agent
{
protected:
    Evaluator& evaluator;
public:
    Agent(Evaluator& eval) : evaluator(eval){}
    virtual ~Agent() = default;
    int timeLimit = 1000;
    virtual GameState selectMove(const GameState& state, bool color) = 0;
};

#endif