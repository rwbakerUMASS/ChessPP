#ifndef CHESSPP_BITBOARD_H
#define CHESSPP_BITBOARD_H

#include <iostream>
#include <string>
#include <stdint.h>
#include <vector>
using namespace std;

class BitBoard
{
public:
    BitBoard();
    BitBoard(uint64_t board);
    ~BitBoard();
    uint64_t board;

    /*
    @brief Checks if the given square is set
    
    @param square index of the square to be checked
    @returns true if square is set, false otherwise
    */
    bool checkSquare(int square) const;

    /*
    @brief Sets given square
    
    @param square index of the square to be set
    @returns void
    */
    void setSquare(int square);

    /*
    @brief Removes square if set, otherwise does nothing
    
    @param square index of the square to be removed
    @returns true if square is unset, false otherwise
    */
    bool popSquare(int square);

    /*
    @brief Gets the intersection of this BitBoard with another
    
    @param other BitBoard to be intersected with
    @returns New BitBoard containing the intersection
    */
    BitBoard intersect(BitBoard other);

    /*
    @brief Gets the union of this BitBoard with another
    
    @param other BitBoard to be joined with
    @returns New BitBoard containing the union
    */
    BitBoard join(BitBoard other);

    void joinInPlace(const BitBoard& other);

    /*
    @brief Gets inverted BitBoard
    
    @returns New inverted BitBoard
    */
    BitBoard invert();

    /*
    @brief Checks if there are no squares set on the BitBoard
    
    @returns true if BitBoard is empty, false otherwise
    */
    bool isEmpty();

    /*
    @brief Checks if there are any squares set on the BitBoard
    
    @returns true if BitBoard is not empty, false otherwise
    */
    bool any();


    /*
    @brief Finds all squares where the bitboard is set
    
    @returns Vector of all locations where a bit is set
    */
    vector<int> findAllSet();

    /*
    @brief Prints formatted BitBoard
    
    @returns void
    */
    void print();

    /*
    @brief Gets the total number of squares set on BitBoard
    
    @returns Count of set bits
    */
    int pieceCount() const;
};

#endif