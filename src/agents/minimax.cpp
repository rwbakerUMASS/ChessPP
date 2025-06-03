#include "minimax.h"
#include <vector>
#include <limits.h>

Move MiniMax::selectMove(GameState& state, bool color){
    vector<Move> candidates = state.get_all_moves(color);
    int bestScore = (color == white) ? INT_MIN : INT_MAX;
    Move bestMove;
    for (Move move : candidates)
    {
        state.makeMove(move);
        int score = this->search(state,this->depth,INT_MIN,INT_MAX,!color);
        if ((color == white && score > bestScore) ||
            (color == black && score < bestScore)) {
            bestScore = score;
            bestMove = move;
        }
        state.undoMove();
    }
    return bestMove;
}

int MiniMax::search(GameState& state, int depth, int alpha, int beta, bool color) const {
    if (depth == 0) {
        return this->evaluator.evaluate(state);
    }
    vector<Move> candidates = state.get_all_moves(color);
    if (color == white)
    {
        int score = INT_MIN;
        for (Move move : candidates)
        {
            state.makeMove(move);
            score = max(score,search(state,depth-1,alpha,beta,!color));
            state.undoMove();
            alpha = max(alpha,score);
            if (alpha >= beta) break;
        }
        return score;
    } else {
        int score = INT_MAX;
        for (Move move : candidates)
        {
            state.makeMove(move);
            score = min(score,search(state,depth-1,alpha,beta,!color));
            state.undoMove();
            beta = min(beta,score);
            if (beta <= alpha) break;
        }
        return score;
    }
}