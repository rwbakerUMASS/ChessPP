#include "bitboard.h"

BitBoard::BitBoard(/* args */)
{
    this->board = 0ULL;
}

BitBoard::BitBoard(uint64_t board)
{
    this->board = board;
}

bool BitBoard::checkSquare(int square)
{
    return this->board & (1ULL << square);
}

void BitBoard::setSquare(int square)
{
    this->board |= (1ULL << square);
}

bool BitBoard::popSquare(int square)
{
    bool occupied = this->checkSquare(square);
    if (occupied)
    {
        this->board &= ~(1ULL << square);
    }

    return occupied;
}

int BitBoard::pieceCount()
{
    return this->pieceCountHelper(this->board);
}

int BitBoard::pieceCountHelper(uint64_t piece)
{
    if (piece == 0)
    {
        return 0;
    }
    return this->pieceCountHelper(piece / 2) + piece % 2;
}

void BitBoard::print()
{
    for (int rank = 0; rank < 8; rank++)
    {
        cout << "  +---+---+---+---+---+---+---+---+" << "\n";
        for (int file = 0; file < 8; file++)
        {
            int square = rank * 8 + file;
            if (!file)
            {
                cout << rank + 1 << " ";
            }
            if (this->checkSquare(square))
            {
                cout << "| X ";
            }
            else
            {
                cout << "|   ";
            }
        }
        cout << "|" << "\n";
    }
    cout << "  +---+---+---+---+---+---+---+---+\n"
         << "    A   B   C   D   E   F   G   H  \n" << endl;
}

BitBoard::~BitBoard()
{
}
