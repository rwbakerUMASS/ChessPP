#ifndef CHESSPP_STATE_H
#define CHESSPP_STATE_H

#include <string>
#include <iostream>
#include "bitboard.h"
#include "enums.h"
#include <vector>

using namespace std;

class GameState
{
private:
/* data */
public:
    GameState(/* args */);
    GameState(const GameState& other);
    ~GameState();
    BitBoard pieces[2][6];
    bool turn;
    // castlingRights[color][direction]
    bool castlingRights[2][2];
    BitBoard enPassant;
    int halfmove;
    int fullmove;

    /*
    @brief Prints a formatted representation of the current game state.

    @return void
    */
    void print();

    /*
    @brief Gets the material value of a given color

    @param color The color of the pieces (white=0, black=1)
    @return Integer value of the current material on the board
    */
    int material(int color) const;

    /*
    @brief Resets the game state to a standard starting chess position
    
    @returns void
    */
    void reset();

    /*
    @brief Gets a mask of all occupied squares of a given color

    @param color The color of the pieces (white=0, black=1)
    @return BitBoard representing all squares on the board occupied by that color
    */
    BitBoard piecesMask(int color);

    /*
    @brief Gets all controlled squares by a given color
    
    @note This function does not currently work, it gets all possible moves, but does not take into account the fact that:
        1.) Pieces can control squares where pieces are currently (defending)
        2.) Pawns don't control where they can move.
        3.) Pinned pieces
    
    @param color The color of the pieces (white=0, black=1)
    @return BitBoard representing all controlled squares on the board
    */
    BitBoard getControlledSquares(int color);

    /*
    @brief Gets a mask of all occupied squares of both colors

    @param color The color of the pieces (white=0, black=1)
    @return BitBoard representing all occupied squares on the board
    */
    BitBoard piecesMask();

    /*
    @brief Check if the current state is check for a given color

    @param color Color who to check
    @return True if color is in check, false otherwise
    */
    bool isCheck(int color);
    
    /*
    @brief Gets all possible moves in the current state

    @param color Color whose turn it is
    @return Vector of all possible resulting GameStates
    */
    vector<GameState> get_all_moves(int color) const;
    
    /*
    @brief Check if square is attacked by any pieces

    @param square Location of square to check
    @param color Color whose turn it is
    @return True if square is under attack, false otherwise
    */
    bool isSquareAttacked(int square, int color);

    /* 
    @brief Load FEN string into game state

    @param fen String in FEN format
    @returns void
    */
    void loadFen(string fen);
};


#endif