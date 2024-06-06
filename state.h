#ifndef CHESSPP_STATE_H
#define CHESSPP_STATE_H

#include <string>
#include <iostream>

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

class GameState
{
private:
    /* data */
public:
    GameState(/* args */);
    ~GameState();
    uint64_t pieces[12];
    void print();
    int material(int side);
    void reset();
    uint64_t piecesMask(int side);
};


#endif