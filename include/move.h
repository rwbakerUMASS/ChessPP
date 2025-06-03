#ifndef CHESSPP_MOVE_H
#define CHESSPP_MOVE_H

#include "bitboard.h"

class Move
{
public:
    bool color;
    int pieceMoved;
    int fromSquare;
    int toSquare;
    bool isCapture;
    int capturedPieceType;
    bool isCastle; //TODO
    bool isEnPassant; //TODO
    int promotionType; //TODO

    Move() = default;

    Move(
        bool color,
        int pieceMoved,
        int fromSquare,
        int toSquare,
        bool isCapture = false,
        int capturedPieceType = -1,
        bool isCastle = false,
        bool isEnPassant = false,
        int promotionType = -1
    )
    : color(color),
      pieceMoved(pieceMoved),
      fromSquare(fromSquare),
      toSquare(toSquare),
      isCapture(isCapture),
      capturedPieceType(capturedPieceType),
      isCastle(isCastle),
      isEnPassant(isEnPassant),
      promotionType(promotionType)
    {}
};

class UndoInfo {
public:
    bool color;
    int fromSquare;
    int toSquare;
    int pieceMoved;
    bool castlingRights[2][2];
    int halfmoveBefore;
    int fullmoveBefore;
    BitBoard enPassantBefore;
    int capturedPieceType;
    int capturedSquare;
    bool wasPromotion;
    int promotionType;
    bool wasEnPassantCapture;
    int enPassantCapturedPawnSquare;

    UndoInfo() = default; // default constructor

    UndoInfo(
        bool c,
        int from,
        int to,
        int piece,
        bool cr[2][2],
        int half,
        int full,
        BitBoard ep,
        int capType,
        int capSq,
        bool promo,
        int promoType,
        bool epCapture,
        int epCapSq
    )
        : color(c),
        fromSquare(from),
        toSquare(to),
        pieceMoved(piece),
        halfmoveBefore(half),
        fullmoveBefore(full),
        enPassantBefore(ep),
        capturedPieceType(capType),
        capturedSquare(capSq),
        wasPromotion(promo),
        promotionType(promoType),
        wasEnPassantCapture(epCapture),
        enPassantCapturedPawnSquare(epCapSq)
    {
        castlingRights[0][0] = cr[0][0];
        castlingRights[0][1] = cr[0][1];
        castlingRights[1][0] = cr[1][0];
        castlingRights[1][1] = cr[1][1];
    }
};
    

#endif