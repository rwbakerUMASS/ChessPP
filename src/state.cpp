#include "state.h"
#include "move_generator.h"
#include "logger.h"

#include <string>
#include <iostream>

using namespace std;

GameState::GameState()
{
    for (int i = 0; i < 6; i++)
    {
        this->pieces[black][i].board = 0ULL;
        this->pieces[white][i].board = 0ULL;
    }
    this->turn = white;
    this->castlingRights[black][king] = false;
    this->castlingRights[black][queen] = false;
    this->castlingRights[white][king] = false;
    this->castlingRights[white][queen] = false;
    this->enPassant = BitBoard(0);
    this->halfmove = 0;
    this->fullmove = 0;

    this->isPiecesMaskCached[0] = false;
    this->isPiecesMaskCached[1] = false;
}

GameState::GameState(const GameState& other) {
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            this->pieces[i][j] = other.pieces[i][j];
        }
    }
    this->turn = other.turn;
    this->castlingRights[black][king] = other.castlingRights[black][king];
    this->castlingRights[black][queen] = other.castlingRights[black][queen];
    this->castlingRights[white][king] = other.castlingRights[white][king];
    this->castlingRights[white][queen] = other.castlingRights[white][queen];
    this->enPassant = other.enPassant;
    this->halfmove = other.halfmove;
    this->fullmove = other.fullmove;

    this->isPiecesMaskCached[0] = false;
    this->isPiecesMaskCached[1] = false;
}

void GameState::reset()
{
    this->pieces[white][pawn].board = 0x000000000000ff00;
    this->pieces[black][pawn].board = 0x00ff000000000000;
    this->pieces[white][knight].board = 0x0000000000000042;
    this->pieces[black][knight].board = 0x4200000000000000;
    this->pieces[white][bishop].board = 0x0000000000000024;
    this->pieces[black][bishop].board = 0x2400000000000000;
    this->pieces[white][rook].board = 0x0000000000000081;
    this->pieces[black][rook].board = 0x8100000000000000;
    this->pieces[white][queen].board = 0x0000000000000008;
    this->pieces[black][queen].board = 0x0800000000000000;
    this->pieces[white][king].board = 0x0000000000000010;
    this->pieces[black][king].board = 0x1000000000000000;

    this->turn = white;
    this->castlingRights[black][king] = true;
    this->castlingRights[black][queen] = true;
    this->castlingRights[white][king] = true;
    this->castlingRights[white][queen] = true;
    this->enPassant = BitBoard(0);
    this->halfmove = 0;
    this->fullmove = 0;

    this->isPiecesMaskCached[0] = false;
    this->isPiecesMaskCached[1] = false;
}

BitBoard GameState::getControlledSquares(int color)
{
    BitBoard controlled;
    for (int p = 0; p < 6; p++)
    {
        BitBoard pieceBB = this->pieces[color][p];
        for (int s = 0; s < 64; s++)
        {
            if (pieceBB.checkSquare(s))
            {
                controlled.joinInPlace(GlobalMoveGenerator.get_moves(p,s,color,*this));
            }
        }
    }
    return controlled;
}

BitBoard GameState::piecesMask(int color) const
{
    if(this->isPiecesMaskCached[color]) return this->piecesMaskCache[color];
    BitBoard mask;
    for (int p = 0; p < 6; p++)
    {
        mask.joinInPlace(this->pieces[color][p]);
    }
    this->piecesMaskCache[color] = mask;
    this->isPiecesMaskCached[color] = true;
    return mask;
}

BitBoard GameState::piecesMask() const
{
    BitBoard mask = piecesMask(white);
    mask.joinInPlace(piecesMask(black));
    return mask;
}

int GameState::material(int color) const
{
    int value = 0;
    value +=     this->pieces[color][pawn].pieceCount();
    value += 3 * this->pieces[color][knight].pieceCount();
    value += 3 * this->pieces[color][bishop].pieceCount();
    value += 5 * this->pieces[color][rook].pieceCount();
    value += 9 * this->pieces[color][queen].pieceCount();
    return value;
}

void GameState::print()
{
    for (int rank = 0; rank < 8; rank++)
    {
        cout << "  +---+---+---+---+---+---+---+---+" << endl;
        for (int file = 0; file < 8; file++)
        {
            int square = rank * 8 + file;
            bool occupied = false;
            if (!file)
            {
                cout << rank + 1 << " ";
            }
            cout << "| ";
            // cout << square;
            for (int c = 0; c < 2; c++)
            {
                for (int p = 0; p < 6; p++)
                {
                    if (this->pieces[c][p].checkSquare(square))
                    {
                        cout << symbols[c][p];
                        occupied = true;
                        continue;
                    }
                }
            }
            if (!occupied)
            {
                cout << " ";
            }
            cout << " ";
        }
        cout << "|" << endl;
    }
    cout << "  +---+---+---+---+---+---+---+---+" << endl
         << "    A   B   C   D   E   F   G   H  " << endl
         << "Turn: " << (this->turn ? "black" : "white") << endl
         << "Halfmove: " << to_string(this->halfmove) << endl
         << "Fullmove: " << to_string(this->fullmove) << endl
         << "White Material: " << material(white) << endl
         << "Black Material: " << material(black) << endl;
}

vector<Move> GameState::get_all_moves(int color)
{
    vector<Move> allMoves;
    for (int p = 0; p < 6; p++)
    {
        BitBoard pieceBB = this->pieces[color][p];
        vector<int> allFrom = pieceBB.findAllSet();
        for (int from : allFrom)
        {
            BitBoard tmpMoves = GlobalMoveGenerator.get_moves(p,from,color,*this);
            vector<int> allTo = tmpMoves.findAllSet();
            for (int to : allTo)
            {
                bool isCapture = false;
                int captureType = -1;
                if (this->piecesMask(!color).checkSquare(to))
                {
                    for (int otherPiece = 0; otherPiece < 6; otherPiece++)
                    {
                        if (this->pieces[!color][otherPiece].checkSquare(to)) {
                            isCapture = true;
                            captureType = otherPiece;
                            break;
                        }
                    }
                }
                Move move(color,p,from,to,isCapture,captureType,false,false,-1);
                this->makeMove(move);
                if (!this->isCheck(color))
                {
                    allMoves.push_back(move);
                }
                this->undoMove();
            }
        }
    }
    return allMoves;
}

bool GameState::isCheck(int color)
{
    // Leaving open the possibility for multiple kings (idk could be a fun spin on chess)
    vector<int> kingSquares = this->pieces[color][king].findAllSet();
    for (size_t i = 0; i < kingSquares.size(); i++)
    {
        if (this->isSquareAttacked(kingSquares[i],color)) return true;
    }
    return false;
}

bool GameState::isSquareAttacked(int square, int color)
{
    static PawnMoveTable pt;
    for (int i = 0; i < 6; i++)
    {
        if(i==pawn)
        {
            BitBoard possiblePawnAttacks = pt.get_attacks(square, color); // reverse: from square's point of view
            BitBoard pawns = this->pieces[!color][pawn];
            if (possiblePawnAttacks.intersect(pawns).any()) return true;
            continue;
        }
        // Trace back where attacks of that piece type could come from
        BitBoard possibleSquares = GlobalMoveGenerator.get_moves(i,square,color,*this);
        // If any of those squares are that piece type, it's attacked
        if(possibleSquares.intersect(this->pieces[!color][i]).any()) return true;
    }
    return false;
}

void GameState::makeMove(const Move& move)
{
    this->undoStack.push_back(UndoInfo(
        move.color,
        move.fromSquare,
        move.toSquare,
        move.pieceMoved,
        this->castlingRights,
        this->halfmove,
        this->fullmove,
        this->enPassant,
        move.isCapture ? move.capturedPieceType : -1,
        move.toSquare,
        move.promotionType != -1,
        move.promotionType,
        move.isEnPassant,
        move.isEnPassant ? (move.color == white ? move.toSquare - 8 : move.toSquare + 8) : -1
    ));

    if (!this->pieces[move.color][move.pieceMoved].popSquare(move.fromSquare))
    {
        LOG_ERROR("Tried to move " + symbols[move.color][move.pieceMoved] +
            " on square " + to_string(move.fromSquare) + "but there was no piece there!");
    }

    this->pieces[move.color][move.pieceMoved].setSquare(move.toSquare);

    if (move.isCapture)
    {
        if (!this->pieces[!move.color][move.capturedPieceType].popSquare(move.toSquare))
        {
            LOG_ERROR("Move " + symbols[move.color][move.pieceMoved] +
                " tried to take " + symbols[!move.color][move.capturedPieceType] +
                " on square " + to_string(move.toSquare) + "but there was no piece there!");
        }
    }
    this->halfmove++;
    if (move.color == black) this->fullmove++;
    if (move.isCapture || move.pieceMoved == pawn) this->halfmove = 0;

    this->isPiecesMaskCached[0] = false;
    this->isPiecesMaskCached[1] = false;
}

GameState GameState::applyMove(const Move& move) const 
{
    GameState new_state(*this);
    new_state.makeMove(move);
    return new_state;
}

void GameState::undoMove()
{
    UndoInfo undo = this->undoStack.back();
    this->undoStack.pop_back();

    this->fullmove = undo.fullmoveBefore;
    this->halfmove = undo.halfmoveBefore;
    
    

    this->pieces[undo.color][undo.pieceMoved].popSquare(undo.toSquare);
    this->pieces[undo.color][undo.pieceMoved].setSquare(undo.fromSquare);

    if (undo.capturedPieceType != -1)
    {
        this->pieces[!undo.color][undo.capturedPieceType].setSquare(undo.toSquare);
    }

    this->isPiecesMaskCached[0] = false;
    this->isPiecesMaskCached[1] = false;
}

void GameState::loadFen(string fen)
{
    size_t end_of_rows = fen.find(" ");
    string state = fen.substr(end_of_rows+1);
    fen = fen.substr(0,end_of_rows);

    stringstream rows_ss(fen);
    string rowStr;
    vector<string> rows;
    while (getline(rows_ss, rowStr, '/')) {
        rows.push_back(rowStr);
    }

    int rank = 7;
    for(string row : rows)
    {
        int file = 0;
        for(char piece : row)
        {
            if (isdigit(piece)) {
                file += piece - '0';
                continue;
            }

            int sq = rank * 8 + file;

            switch (piece) {
                case 'p' :this->pieces[black][pawn].setSquare(sq); break;
                case 'r' :this->pieces[black][rook].setSquare(sq); break;
                case 'n' :this->pieces[black][knight].setSquare(sq); break;
                case 'b' :this->pieces[black][bishop].setSquare(sq); break;
                case 'q' :this->pieces[black][queen].setSquare(sq); break;
                case 'k' :this->pieces[black][king].setSquare(sq); break;
                case 'P' :this->pieces[white][pawn].setSquare(sq); break;
                case 'R' :this->pieces[white][rook].setSquare(sq); break;
                case 'N' :this->pieces[white][knight].setSquare(sq); break;
                case 'B' :this->pieces[white][bishop].setSquare(sq); break;
                case 'Q' :this->pieces[white][queen].setSquare(sq); break;
                case 'K' :this->pieces[white][king].setSquare(sq); break;
                default: LOG_ERROR("INVALID PIECE TYPE: " + string(1,piece));
            }
            file++;
        }

        if (file != 8) {
            LOG_ERROR("FEN row had " + to_string(file) + " squares, expected 8.");
        }

        rank--;
    }

    if (rank != -1) {
        LOG_ERROR("FEN had " + to_string(7 - rank) + " rows, expected 8.");
    }

    stringstream flags_ss(state);
    string flagsStr;
    vector<string> flags;
    while (getline(flags_ss, flagsStr, ' ')) {
        flags.push_back(flagsStr);
    }

    if(flags.size() != 5) LOG_ERROR("FEN input had " + to_string(flags.size()) + " flags, expected 5");
    if (flags[0] == "w")
    {
        this->turn = white;
    }
    else if (flags[0] == "b")
    {
        this->turn = black;
    } else {
        LOG_ERROR("FEN input had invalid turn: " + flags[0]);
    }

    if (flags[1].find("k") != string::npos) this->castlingRights[black][king_side] = true;
    if (flags[1].find("q") != string::npos) this->castlingRights[black][queen_side] = true;
    if (flags[1].find("K") != string::npos) this->castlingRights[white][king_side] = true;
    if (flags[1].find("Q") != string::npos) this->castlingRights[white][queen_side] = true; 

    if (flags[2] != "-")
    {
        int file = flags[2][0] - 'a';
        int rank = flags[2][1] - '1';
        int sq = rank * 8 + file;
        this->enPassant = BitBoard(0);
        this->enPassant.setSquare(sq);
    } else {
        this->enPassant = BitBoard(0);
    }

    try
    {
        this->halfmove = stoi(flags[3]);
    }
    catch(const std::invalid_argument& e)
    {
        LOG_ERROR("FEN halfmove is not an integer: " + flags[3]);
    }

    try
    {
        this->fullmove = stoi(flags[4]);
    }
    catch(const std::invalid_argument& e)
    {
        LOG_ERROR("FEN halfmove is not an integer: " + flags[4]);
    }
}

GameState::~GameState()
{
}