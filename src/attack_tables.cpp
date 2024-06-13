#include "attack_tables.h"

PawnMoveTable::PawnMoveTable(/* args */)
{
    for (int rank = 1; rank < 7; rank++)
    {
        for (int file = 0; file < 8; file++)
        {
            int square = rank * 8 + file;
            this->moves[white][square].setSquare(square + 8);
            this->moves[black][square].setSquare(square - 8);

            if (rank == 1)
            {
                this->moves[white][square].setSquare(square + 16);
            }

            if (rank == 6)
            {
                this->moves[black][square].setSquare(square - 16);
            }
            if (file != 0)
            {
                this->attacks[white][square].setSquare(square + 7);
                this->attacks[black][square].setSquare(square - 9);
            }
            if (file != 7)
            {
                this->attacks[white][square].setSquare(square + 9);
                this->attacks[black][square].setSquare(square - 7);
            }
        }
    }
}

BitBoard PawnMoveTable::get_attacks(int square, int color)
{
    return this->attacks[color][square];
}

BitBoard PawnMoveTable::get_moves(int square, int color)
{
    return this->moves[color][square];
}
