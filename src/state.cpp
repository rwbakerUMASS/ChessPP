#include "state.h"
#include "move_generator.h"

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
}

GameState::GameState(const GameState& other) {
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            this->pieces[i][j] = other.pieces[i][j];
        }
    }
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
                controlled = controlled.join(GlobalMoveGenerator.get_moves(p,s,color,*this));
            }
        }
    }
    return controlled;
}

BitBoard GameState::piecesMask(int color)
{
    BitBoard mask;
    for (int p = 0; p < 6; p++)
    {
        mask = mask.join(this->pieces[color][p]);
    }
    return BitBoard(mask);
}

BitBoard GameState::piecesMask()
{
    BitBoard mask;
    mask = mask.join(piecesMask(white));
    mask = mask.join(piecesMask(black));
    return mask;
}

int GameState::material(int color)
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
        cout << "  +---+---+---+---+---+---+---+---+" << "\n";
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
        cout << "|" << "\n";
    }
    cout << "  +---+---+---+---+---+---+---+---+\n"
         << "    A   B   C   D   E   F   G   H  \n"
         << "White Material: " << material(white) << "\n"
         << "Black Material: " << material(black) << endl;
}

vector<GameState> GameState::get_all_moves(int color)
{
    vector<GameState> allMoves;
    for (int p = 0; p < 6; p++)
    {
        BitBoard pieceBB = this->pieces[color][p];
        for (int s = 0; s < 64; s++)
        {
            if (pieceBB.checkSquare(s))
            {
                BitBoard tmpMoves = GlobalMoveGenerator.get_moves(p,s,color,*this);
                for (int i = 0; i < 64; i++)
                {
                    if (tmpMoves.checkSquare(i))
                    {
                        GameState tmpState = GameState(*this);
                        tmpState.pieces[color][p].popSquare(s);
                        tmpState.pieces[color][p].setSquare(i);
                        if (tmpState.piecesMask(!color).checkSquare(i))
                        {
                            for (int otherPiece = 0; otherPiece < 6; otherPiece++)
                            {
                                tmpState.pieces[!color][otherPiece].popSquare(i);
                            }
                        }
                        if(!tmpState.isCheck(color)) allMoves.push_back(tmpState);
                    }
                }
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

GameState::~GameState()
{
}