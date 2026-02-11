#include "minimax.h"
#include <vector>
#include "logger.h"
#include <limits.h>
#include <atomic>
#include <thread>
#include <chrono>

GameState MiniMax::selectMove(const GameState& state, bool color){
    // prepare timer-based stop flag
    this->stopSearch.store(false);

    // start a timer thread that sets stopSearch after timeLimit milliseconds
    std::thread timer([this]() {
        int remaining = this->timeLimit;
        const int tick = 10; // ms
        while (remaining > 0 && !this->stopSearch.load()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(tick));
            remaining -= tick;
        }
        LOG_DEBUG("MiniMax::selectMove(): Time limit reached, stopping search");
        if (!this->stopSearch.load()) this->stopSearch.store(true);
    });

    vector<GameState> candidates = state.get_all_moves(color);
    GameState bestMove;
    int bestScore = (color == white) ? INT_MIN : INT_MAX;
    int depthReached = 0;
    for (int idDepth = 1; idDepth <= this->depth; idDepth++)
    {
        if (this->stopSearch.load()) break; // time up
        int currentBestScore = (color == white) ? INT_MIN : INT_MAX;
        GameState currentBestMove;
        for (GameState move : candidates)
        {
            if (this->stopSearch.load()) break; // time up
            int score = this->search(move,idDepth,INT_MIN,INT_MAX,!color);
            if ((color == white && score > currentBestScore) ||
                (color == black && score < currentBestScore)) {
                currentBestScore = score;
                currentBestMove = move;
            }
        }
        // Only update bestMove if we completed this depth
        if (!this->stopSearch.load()) {
            bestScore = currentBestScore;
            bestMove = currentBestMove;
            depthReached = idDepth;
        }
    }

    // signal timer to stop early and join
    this->stopSearch.store(true);
    if (timer.joinable()) timer.join();
    LOG_DEBUG("MiniMax::selectMove(): Best score: " + to_string(bestScore) + " at depth: " + to_string(depthReached));

    return bestMove;
}

int MiniMax::search(const GameState& state, int depth, int alpha, int beta, bool color) const {
    if (this->stopSearch.load()) return this->evaluator.evaluate(state);
    if (depth == 0) {
        return this->evaluator.evaluate(state);
    }
    vector<GameState> candidates = state.get_all_moves(color);
    if (color == white)
    {
        int score = INT_MIN;
        for (GameState move : candidates)
        {
            if (this->stopSearch.load()) break;
            score = max(score, search(move, depth-1, alpha, beta, !color));
            alpha = max(alpha, score);
            if (alpha >= beta) break;
        }
        return score;
    } else {
        int score = INT_MAX;
        for (GameState move : candidates)
        {
            if (this->stopSearch.load()) break;
            score = min(score, search(move, depth-1, alpha, beta, !color));
            beta = min(beta,score);
            if (beta <= alpha) break;
        }
        return score;
    }
}