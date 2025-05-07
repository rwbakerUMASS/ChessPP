#include "state.h"

#include <string>
#include <iostream>

using namespace std;

GameState::GameState(/* args */)
{
    for (int i = 0; i < 6; i++)
    {
        this->pieces[black][i].board = 0ULL;
        this->pieces[white][i].board = 0ULL;
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
    for (int p = 0; p < 6; p++)
    {

    }
}

BitBoard GameState::piecesMask(int color)
{
    BitBoard mask;
    for (int p = 0; p < 6; p++)
    {
        mask = mask.join(this->pieces[color][pawn]);
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

GameState::~GameState()
{
}