#ifndef CHESSPP_BASEEVAL_H
#define CHESSPP_BASEEVAL_H

#include "state.h"

using namespace std;

class Evaluator
{
private:
/* data */
public:
    virtual int evaluate(const GameState& state) = 0;
    virtual ~Evaluator() = default;
};

#endif