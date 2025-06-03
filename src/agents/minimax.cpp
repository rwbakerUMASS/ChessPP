#include "minimax.h"
#include <vector>
#include <limits.h>

GameState MiniMax::selectMove(const GameState& state, bool color){
    vector<GameState> candidates = state.get_all_moves(color);
    int bestScore = (color == white) ? INT_MIN : INT_MAX;
    GameState bestMove;
    for (GameState move : candidates)
    {
        int score = this->search(move,this->depth,INT_MIN,INT_MAX,!color);
        if ((color == white && score > bestScore) ||
            (color == black && score < bestScore)) {
            bestScore = score;
            bestMove = move;
        }
    }
    return bestMove;
}

int MiniMax::search(const GameState& state, int depth, int alpha, int beta, bool color) const {
    if (depth == 0) {
        return this->evaluator.evaluate(state);
    }
    vector<GameState> candidates = state.get_all_moves(color);
    if (color == white)
    {
        int score = INT_MIN;
        for (GameState move : candidates)
        {
            score = max(score,search(move,depth-1,alpha,beta,!color));
            if (alpha >= beta) break;
            alpha = max(alpha,score);
        }
        return score;
    } else {
        int score = INT_MAX;
        for (GameState move : candidates)
        {
            score = min(score,search(move,depth-1,alpha,beta,!color));
            if (beta <= alpha) break;
            beta = min(beta,score);
        }
        return score;
    }
}