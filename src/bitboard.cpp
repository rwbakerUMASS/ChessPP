#include "bitboard.h"
#include "logger.h"

BitBoard::BitBoard(/* args */)
{
    this->board = 0ULL;
}

BitBoard::BitBoard(uint64_t board)
{
    this->board = board;
}

bool BitBoard::checkSquare(int square) const
{
    return this->board & (1ULL << square);
}

void BitBoard::setSquare(int square)
{
    if (square < 0 || square > 63) 
    {
        LOG_ERROR("BitBoard::setSquare(): Out of bounds! square: "  + to_string(square));
        return;
    }
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

BitBoard BitBoard::intersect(BitBoard other)
{
    return BitBoard(this->board & other.board);
}

BitBoard BitBoard::join(BitBoard other)
{
    return BitBoard(this->board | other.board);
}

BitBoard BitBoard::invert()
{
    return BitBoard(~(this->board));
}

bool BitBoard::isEmpty()
{
    return this->board == 0;
}

bool BitBoard::any()
{
    return !this->isEmpty();
}

vector<int> BitBoard::findAllSet()
{
    vector<int> allSet;
    uint64_t tempBoard = this->board;
    while(tempBoard != 0)
    {
        int nextSet = __builtin_ctzll(tempBoard);
        allSet.push_back(nextSet);
        tempBoard &= (tempBoard - 1);
    }
    return allSet;
}

int BitBoard::pieceCount() const
{
    return __builtin_popcountll(this->board);
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
         << "    A   B   C   D   E   F   G   H  \n"
         << "Count: " << pieceCount() << "\n"
         << endl;
}

BitBoard::~BitBoard()
{
}
