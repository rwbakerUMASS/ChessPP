#include "bitboard.h"

BitBoard::BitBoard(/* args */)
{
    this->board = 0ULL;
}

BitBoard::BitBoard(uint64_t board)
{
    this->board = board;
}

/*
@brief Checks if the given square is set

@param square index of the square to be checked
@returns true if square is set, false otherwise
*/
bool BitBoard::checkSquare(int square)
{
    return this->board & (1ULL << square);
}

/*
@brief Sets given square

@param square index of the square to be set
@returns void
*/
void BitBoard::setSquare(int square)
{
    if (square < 0 || square > 63) 
    {
        cout << "WARN: BitBoard::setSquare(): Out of bounds! square:" << square << "\n";
        return;
    }
    this->board |= (1ULL << square);
}

/*
@brief Removes square if set, otherwise does nothing

@param square index of the square to be removed
@returns true if square is unset, false otherwise
*/
bool BitBoard::popSquare(int square)
{
    bool occupied = this->checkSquare(square);
    if (occupied)
    {
        this->board &= ~(1ULL << square);
    }

    return occupied;
}

/*
@brief Gets the intersection of this BitBoard with another

@param other BitBoard to be intersected with
@returns New BitBoard containing the intersection
*/
BitBoard BitBoard::intersect(BitBoard other)
{
    return BitBoard(this->board & other.board);
}

/*
@brief Gets the union of this BitBoard with another

@param other BitBoard to be joined with
@returns New BitBoard containing the union
*/
BitBoard BitBoard::join(BitBoard other)
{
    return BitBoard(this->board | other.board);
}

/*
@brief Gets inverted BitBoard

@returns New inverted BitBoard
*/
BitBoard BitBoard::invert()
{
    return BitBoard(~(this->board));
}

/*
@brief Checks if there are no squares set on the BitBoard

@returns true if BitBoard is empty, false otherwise
*/
bool BitBoard::isEmpty()
{
    return this->board == 0;
}

/*
@brief Gets the total number of squares set on BitBoard

@returns Count of set bits
*/
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

/*
@brief Prints formatted BitBoard

@returns void
*/
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
