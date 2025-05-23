#include "test_base.h"
#include "bitboard.h"

class CheckSquareTC : public TestCase {
public:
    CheckSquareTC() {
        this->name = "CheckSquareTC";
    }
    void run() override {
        for(int i = 0; i < 64; i++)
        {
            BitBoard board = BitBoard(1ULL << i);   
            for(int j = 0; j < 64; j++)
            {
                if(i == j && !board.checkSquare(j)) this->testFailed("expected square to be set, but checkSquare returned false");
                if(i != j && board.checkSquare(j)) this->testFailed("expected square to be unset, but checkSquare returned true");
            }
        }     
    }
};

class PopSquareTC : public TestCase {
public:
    PopSquareTC() {
        this->name = "PopSquareTC";
    }
    void run() override {
        for(int i = 0; i < 64; i++)
        {
            BitBoard board = BitBoard(1ULL << i);   
            for(int j = 0; j < 64; j++)
            {
                if(i == j)
                {
                    if(!board.popSquare(j)) this->testFailed("popSquare should return true when square is unoccupied");
                    if(board.board != 0) this->testFailed("board should be empty after popping square");
                    break;
                } else {
                    if(board.popSquare(j)) this->testFailed("popSquare should return false on unoccupied squares");
                    if(board.board != (1ULL << i)) this->testFailed("popSquare on unoccupied square modified the board");
                }
            }
        }     
    }
};

int main() {
    UnitTestSuite ts = UnitTestSuite("BitBoard");
    ts.addTestCase(new CheckSquareTC());
    ts.addTestCase(new PopSquareTC());
    ts.runAll();
    return 0;
}