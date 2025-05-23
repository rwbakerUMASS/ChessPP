#include "test_base.h"
#include "state.h"
#include "enums.h"
#include <vector>

class QueenCheckTC : public TestCase {
public:
    QueenCheckTC() {
        this->name = "QueenCheckTC";
    }
    void run() override {
        GameState gs = GameState();
        gs.pieces[white][king].setSquare(14);
        gs.pieces[black][queen].setSquare(42);
        if(!gs.isCheck(white)) this->testFailed("this position is check for white");
    }
};

class KingMoveFromCheckTC : public TestCase {
public:
    KingMoveFromCheckTC() {
        this->name = "KingMoveFromCheckTC";
    }
    void run() override {
        GameState gs = GameState();
        gs.pieces[white][king].setSquare(14);
        gs.pieces[black][queen].setSquare(42);
        vector<GameState> moves = gs.get_all_moves(white);
        if (moves.empty()) this->testFailed("this position is not checkmate, there are legal moves");
        for(GameState& move: moves)
        {
            if(move.piecesMask(white).checkSquare(7) || move.piecesMask(white).checkSquare(21)) {
                this->testFailed("king move stayed in check");
            }
        }
    }
};

class KingCaptureFromCheckTC : public TestCase {
public:
    KingCaptureFromCheckTC() {
        this->name = "KingCaptureFromCheckTC";
    }
    void run() override {
        GameState gs = GameState();
        gs.pieces[white][king].setSquare(14);
        gs.pieces[black][queen].setSquare(21);
        vector<GameState> moves = gs.get_all_moves(white);
        if (moves.empty()) this->testFailed("this position is not checkmate, there are legal moves");
        bool capture = false;
        for(GameState& move: moves)
        {
            if(move.piecesMask(white).checkSquare(21)) {
                if(move.piecesMask(black).checkSquare(21)) this->testFailed("the capture failed to remove the black piece");
                capture = true;
                break;
            }
        }
        if (!capture) this->testFailed("failed to find move where king captured its attacker");
    }
};

class KingCannotCaptureFromCheckTC : public TestCase {
    public:
        KingCannotCaptureFromCheckTC() {
            this->name = "KingCannotCaptureFromCheckTC";
        }
        void run() override {
            GameState gs = GameState();
            gs.pieces[white][king].setSquare(14);
            gs.pieces[black][queen].setSquare(21);
            gs.pieces[black][rook].setSquare(37);
            vector<GameState> moves = gs.get_all_moves(white);
            if (moves.empty()) this->testFailed("this position is not checkmate, there are legal moves");
            for(GameState& move: moves)
            {
                if(move.piecesMask(white).checkSquare(21)) this->testFailed("king can't take its attacker, it is defended");
            }
        }
    };

class OwnPieceBlockingCheckTC : public TestCase {
public:
    OwnPieceBlockingCheckTC() {
        this->name = "OwnPieceBlockingCheckTC";
    }
    void run() override {
        GameState gs = GameState();
        gs.pieces[white][king].setSquare(14);
        gs.pieces[black][queen].setSquare(42);
        gs.pieces[white][pawn].setSquare(21);
        if(gs.isCheck(white)) this->testFailed("The queen should be blocked, no check");
    }
};

class OpponentBlockingCheckTC : public TestCase {
public:
    OpponentBlockingCheckTC() {
        this->name = "OpponentBlockingCheckTC";
    }
    void run() override {
        GameState gs = GameState();
        gs.pieces[white][king].setSquare(14);
        gs.pieces[black][queen].setSquare(42);
        gs.pieces[black][rook].setSquare(21);
        if(gs.isCheck(white)) this->testFailed("The queen should be blocked, no check");
    }
};

class StalemateTC : public TestCase {
public:
    StalemateTC() {
        this->name = "StalemateTC";
    }
    void run() override {
        GameState gs = GameState();
        gs.pieces[white][king].setSquare(23);
        gs.pieces[black][queen].setSquare(28);
        gs.pieces[black][bishop].setSquare(36);
        if(!gs.get_all_moves(white).empty()) this->testFailed("The king should have no legal moves");
    }
};

class BishopStopCheckTC : public TestCase {
public:
    BishopStopCheckTC() {
        this->name = "BishopStopCheckTC";
    }
    void run() override {
        GameState gs = GameState();
        gs.pieces[white][king].setSquare(14);
        gs.pieces[black][queen].setSquare(35);
        gs.pieces[white][bishop].setSquare(17);
        vector<GameState> moves = gs.get_all_moves(white);
        if (moves.empty()) this->testFailed("this position is not checkmate, there are legal moves");
        bool capture = false;
        for(GameState& move: moves)
        {
            if(move.piecesMask(white).checkSquare(35)) {
                if(move.piecesMask(black).checkSquare(35)) this->testFailed("the capture failed to remove the black piece");
                capture = true;
                break;
            }
        }
        if (!capture) this->testFailed("failed to find move where bishop captured king's attacker");
    }
};

class DoubleCheckTC : public TestCase {
public:
    DoubleCheckTC() {
        this->name = "DoubleCheckTC";
    }
    void run() override {
        GameState gs = GameState();
        gs.pieces[white][king].setSquare(14);
        gs.pieces[black][queen].setSquare(35);
        gs.pieces[black][rook].setSquare(30);
        gs.pieces[white][bishop].setSquare(17);
        vector<GameState> moves = gs.get_all_moves(white);
        if (moves.empty()) this->testFailed("this position is not checkmate, there are legal moves");
        for(GameState& move: moves)
        {
            if(move.piecesMask(white).checkSquare(35)) this->testFailed("bishop cannot capture, double check");
        }
    }
};

int main() {
    UnitTestSuite ts = UnitTestSuite("Game State");
    ts.addTestCase(new QueenCheckTC());
    ts.addTestCase(new KingMoveFromCheckTC());
    ts.addTestCase(new KingCaptureFromCheckTC());
    ts.addTestCase(new KingCannotCaptureFromCheckTC());
    ts.addTestCase(new OwnPieceBlockingCheckTC());
    ts.addTestCase(new OpponentBlockingCheckTC());
    ts.addTestCase(new StalemateTC());
    ts.addTestCase(new BishopStopCheckTC());
    ts.addTestCase(new DoubleCheckTC());
    ts.runAll();
    return 0;
}