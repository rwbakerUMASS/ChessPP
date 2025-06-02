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

class FenPiecePlacementTC : public TestCase {
public:
    FenPiecePlacementTC() {
        this->name = "FenPiecePlacementTestTC";
    }

    void run() override {
        GameState gs;
        gs.loadFen("8/2p3k1/5p1p/2b1p3/1Pn1P3/2P2P2/1P4PP/6K1 w - - 2 38");
        if (!gs.pieces[white][pawn].checkSquare(18)) this->testFailed("Missing white pawn at square 18 (c3)");
        if (!gs.pieces[white][pawn].checkSquare(21)) this->testFailed("Missing white pawn at square 21 (f3)");
        if (!gs.pieces[black][king].checkSquare(54)) this->testFailed("Missing black king at square 54 (g7)");
        if (!gs.pieces[black][bishop].checkSquare(34)) this->testFailed("Missing black bishop at square 34 (c5)");
        if (!gs.pieces[white][king].checkSquare(6)) this->testFailed("Missing white king at square 6 (g1)");
    }
};

class LostCastlingRightsTC : public TestCase {
public:
    LostCastlingRightsTC() {
        this->name = "LostCastlingRightsTC";
    }
    void run() override {
        GameState gs = GameState();
        gs.pieces[white][king].setSquare(4);
        gs.pieces[white][rook].setSquare(0);
        gs.pieces[white][rook].setSquare(7);
        vector<GameState> moves = gs.get_all_moves(white);
        if (moves.empty()) this->testFailed("this position is not checkmate, there are legal moves");
        for(GameState& move: moves)
        {
            if(move.castlingRights[white][king_side] && move.castlingRights[white][queen_side]) this->testFailed("there should be no move where all castling rights are kept");
        }
    }
};

class KingIntoCheckTC : public TestCase {
public:
    KingIntoCheckTC() {
        this->name = "KingIntoCheckTC";
    }

    void run() override {
        GameState gs = GameState();
        gs.pieces[white][king].setSquare(4);   // e1
        gs.pieces[black][rook].setSquare(6);   // g1

        vector<GameState> moves = gs.get_all_moves(white);
        for (const GameState& move : moves) {
            if (move.pieces[white][king].checkSquare(5)) {
                this->testFailed("King should not move into check");
            }
        }
    }
};

class KnightJumpTC : public TestCase {
public:
    KnightJumpTC() {
        this->name = "KnightJumpTC";
    }

    void run() override {
        GameState gs = GameState();
        gs.pieces[white][knight].setSquare(1);   // b1
        gs.pieces[white][pawn].setSquare(9);     // b2 (blocking path if not knight)
        vector<GameState> moves = gs.get_all_moves(white);
        bool moved = false;

        for (const GameState& move : moves) {
            if (!move.pieces[white][knight].checkSquare(18)) continue; // c3
            moved = true;
        }

        if (!moved) this->testFailed("Knight should be able to jump to c3");
    }
};

class PawnBlockedTC : public TestCase {
public:
    PawnBlockedTC() {
        this->name = "PawnBlockedTC";
    }

    void run() override {
        GameState gs = GameState();
        gs.pieces[white][pawn].setSquare(8);     // a2
        gs.pieces[black][pawn].setSquare(16);    // a3
        vector<GameState> moves = gs.get_all_moves(white);
        if (moves.size() != 0) {
            this->testFailed("Blocked pawn should not be able to move forward");
        }
    }
};

class PawnDoubleMoveTC : public TestCase {
public:
    PawnDoubleMoveTC() {
        this->name = "PawnDoubleMoveTC";
    }

    void run() override {
        GameState gs = GameState();
        gs.pieces[white][pawn].setSquare(8);   // a2
        vector<GameState> moves = gs.get_all_moves(white);
        bool doubleMove = false;

        for (const GameState& move : moves) {
            if (move.pieces[white][pawn].checkSquare(24)) { // a4
                doubleMove = true;
                break;
            }
        }

        if (!doubleMove) this->testFailed("Pawn should be able to move two squares from starting rank");
    }
};

class SimpleCaptureTC : public TestCase {
public:
    SimpleCaptureTC() {
        this->name = "SimpleCaptureTC";
    }

    void run() override {
        GameState gs = GameState();
        gs.pieces[white][rook].setSquare(0);     // a1
        gs.pieces[black][pawn].setSquare(8);     // a2
        vector<GameState> moves = gs.get_all_moves(white);
        bool captured = false;

        for (const GameState& move : moves) {
            if (move.pieces[white][rook].checkSquare(8) &&
                !move.pieces[black][pawn].checkSquare(8)) {
                captured = true;
            }
        }

        if (!captured) this->testFailed("Rook should be able to capture pawn");
    }
};

class BasicCheckmateTC : public TestCase {
public:
    BasicCheckmateTC() {
        this->name = "BasicCheckmateTC";
    }

    void run() override {
        GameState gs = GameState();
        gs.pieces[white][king].setSquare(0);
        gs.pieces[black][rook].setSquare(7);
        gs.pieces[black][rook].setSquare(15);

        vector<GameState> moves = gs.get_all_moves(white);
        if (!moves.empty()) this->testFailed("This is checkmate, no legal moves for white");
    }
};

class StartingBoardMoveCountTC : public TestCase {
public:
    StartingBoardMoveCountTC() {
        this->name = "StartingBoardMoveCountTC";
    }

    void run() override {
        GameState gs;
        gs.loadFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
        vector<GameState> moves = gs.get_all_moves(white);

        // Expected legal moves: 20 (16 pawn moves + 4 knight moves)
        if (moves.size() != 20) {
            this->testFailed("Expected 20 legal moves from the initial position, got " + std::to_string(moves.size()));
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
    ts.addTestCase(new FenPiecePlacementTC());
    ts.addTestCase(new LostCastlingRightsTC());
    ts.addTestCase(new KingIntoCheckTC());
    ts.addTestCase(new KnightJumpTC());
    ts.addTestCase(new PawnBlockedTC());
    ts.addTestCase(new PawnDoubleMoveTC());
    ts.addTestCase(new SimpleCaptureTC());
    ts.addTestCase(new BasicCheckmateTC());
    ts.addTestCase(new StartingBoardMoveCountTC());
    ts.runAll();
    return 0;
}