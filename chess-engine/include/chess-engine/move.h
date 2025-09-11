#ifndef CHESSENGINE_MOVE_H
#define CHESSENGINE_MOVE_H

#include <cstdint>

#include "piece.h"

struct Move {
    uint16_t fromRow : 3;
    uint16_t fromCol : 3;
    uint16_t toRow   : 3;
    uint16_t toCol   : 3;
    bool isCapture : 1;
    Piece piece;

    Move(const int fromRow, const int fromCol, const int toRow, const int toCol, const bool isCapture, const Piece piece) {
        this->fromRow = fromRow;
        this->fromCol = fromCol;
        this->toRow   = toRow;
        this ->toCol   = toCol;
        this->isCapture = isCapture;
        this->piece    = piece;
    }
};
#endif