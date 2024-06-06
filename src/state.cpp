#include "state.h"

#include <string>
#include <iostream>

using namespace std;

GameState::GameState(/* args */)
{
    for (int i = 0; i < 12; i++)
    {
        this->pieces[i].board = 0ULL;
    }
}

void GameState::reset()
{
    this->pieces[whitePawn].board = 0x000000000000ff00;
    this->pieces[blackPawn].board = 0x00ff000000000000;
    this->pieces[whiteKnight].board = 0x0000000000000042;
    this->pieces[blackKnight].board = 0x4200000000000000;
    this->pieces[whiteBishop].board = 0x0000000000000024;
    this->pieces[blackBishop].board = 0x2400000000000000;
    this->pieces[whiteRook].board = 0x0000000000000081;
    this->pieces[blackRook].board = 0x8100000000000000;
    this->pieces[whiteQueen].board = 0x0000000000000008;
    this->pieces[blackQueen].board = 0x0800000000000000;
    this->pieces[whiteKing].board = 0x0000000000000010;
    this->pieces[blackKing].board = 0x1000000000000000;
}

uint64_t GameState::piecesMask(int side)
{
    uint64_t mask = 0;
    mask |= this->pieces[whitePawn + side].board;
    mask |= this->pieces[whiteKnight + side].board;
    mask |= this->pieces[whiteBishop + side].board;
    mask |= this->pieces[whiteRook + side].board;
    mask |= this->pieces[whiteQueen + side].board;
    mask |= this->pieces[whiteKing + side].board;
    return mask;
}

int GameState::material(int side)
{
    int value = 0;
    value += this->pieces[whitePawn + side].pieceCount();
    value += 3 * this->pieces[whiteKnight + side].pieceCount();
    value += 3 * this->pieces[whiteBishop + side].pieceCount();
    value += 5 * this->pieces[whiteRook + side].pieceCount();
    value += 9 * this->pieces[whiteQueen + side].pieceCount();
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
            for (int p = 0; p < 12; p++)
            {
                if (this->pieces[p].checkSquare(square))
                {
                    cout << symbols[p];
                    occupied = true;
                    continue;
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