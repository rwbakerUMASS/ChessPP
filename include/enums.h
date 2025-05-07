#pragma once
#include <string>
using namespace std;

enum side_enum
{
    white,
    black
};

enum pieces_enum
{
    pawn,
    knight,
    bishop,
    rook,
    queen,
    king
};

const std::string symbols[2][6] = {
    {"P", "N", "B", "R", "Q", "K"},
    {"p", "n", "b", "r", "q", "k"} 
};