#include "state.h"

#include <string>
#include <iostream>

using namespace std;

const string symbols[12] =
    {
        "P",
        "p",
        "N",
        "n",
        "B",
        "b",
        "R",
        "r",
        "Q",
        "q",
        "K",
        "k",

};

int popCount(uint64_t piece)
{
    if (piece == 0)
    {
        return 0;
    }
    return popCount(piece / 2) + piece % 2;
}

GameState::GameState(/* args */)
{
    for (int i = 0; i < 12; i++)
    {
        this->pieces[i] = 0;
    }
}

void GameState::reset()
{
    this->pieces[whitePawn] = 0x000000000000ff00;
    this->pieces[blackPawn] = 0x00ff000000000000;
    this->pieces[whiteKnight] = 0x0000000000000042;
    this->pieces[blackKnight] = 0x4200000000000000;
    this->pieces[whiteBishop] = 0x0000000000000024;
    this->pieces[blackBishop] = 0x2400000000000000;
    this->pieces[whiteRook] = 0x0000000000000081;
    this->pieces[blackRook] = 0x8100000000000000;
    this->pieces[whiteQueen] = 0x0000000000000008;
    this->pieces[blackQueen] = 0x0800000000000000;
    this->pieces[whiteKing] = 0x0000000000000010;
    this->pieces[blackKing] = 0x1000000000000000;
}

uint64_t GameState::piecesMask(int side)
{
    uint64_t mask = 0;
    mask |= this->pieces[whitePawn + side];
    mask |= this->pieces[whiteKnight + side];
    mask |= this->pieces[whiteBishop + side];
    mask |= this->pieces[whiteRook + side];
    mask |= this->pieces[whiteQueen + side];
    mask |= this->pieces[whiteKing + side];
    return mask;
}

int GameState::material(int side)
{
    int value = 0;
    value += popCount(this->pieces[whitePawn + side]);
    value += 3 * popCount(this->pieces[whiteKnight + side]);
    value += 3 * popCount(this->pieces[whiteBishop + side]);
    value += 5 * popCount(this->pieces[whiteRook + side]);
    value += 9 * popCount(this->pieces[whiteQueen + side]);
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
                if (this->pieces[p] & (1ULL << square))
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