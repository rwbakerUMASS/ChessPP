#include <vector>
#include <chrono>
#include "state.h"
#include "enums.h"
using namespace std::chrono;

uint64_t performance_test(GameState state, int depth, int color) {
    if(depth == 0) {
        return 1;
    }
    uint64_t nodes = 0;
    vector<GameState> moves = state.get_all_moves(color);
    for(GameState& move : moves){
        nodes += performance_test(move, depth-1,!color);
    }
    return nodes;
}

int main() {
    GameState gs = GameState();
    gs.reset();
    high_resolution_clock::time_point start = high_resolution_clock::now();
    uint64_t nodes = performance_test(gs,4,white);
    high_resolution_clock::time_point end = high_resolution_clock::now();
    duration<double> elapsed_seconds = end - start;
    double nodes_per_sec = nodes/elapsed_seconds.count();
    cout << "Performance test: Generated " << nodes << " positions in "
    << elapsed_seconds.count() << "seconds\nNodes/s: " << nodes_per_sec << endl;    
}