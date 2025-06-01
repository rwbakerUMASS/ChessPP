#ifndef CHESSPP_MINIMAX_H
#define CHESSPP_MINIMAX_H

#include "base_agent.h"

using namespace std;

class MiniMax : public Agent
{
private:
    int search(const GameState& state, int depth, int alpha, int beta, bool color) const;
public:
    using Agent::Agent;
    int depth;
    virtual GameState selectMove(const GameState& state, bool color) override;
};

#endif