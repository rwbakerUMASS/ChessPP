#ifndef CHESSPP_RAWMAT_H
#define CHESSPP_RAWMAT_H

#include "state.h"
#include "base_eval.h"

using namespace std;

class RawMaterialEval : Evaluator
{
private:
public:
    int evaluate(const GameState& state) override;
};

#endif