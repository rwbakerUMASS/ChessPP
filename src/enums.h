#include <string>
using namespace std;

enum side_enum
{
    white,
    black
};

enum pieces_enum
{
    whitePawn,
    blackPawn,
    whiteKnight,
    blackKnight,
    whiteBishop,
    blackBishop,
    whiteRook,
    blackRook,
    whiteQueen,
    blackQueen,
    whiteKing,
    blackKing
};

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