#ifndef CHESSENGINE_PIECE_H
#define CHESSENGINE_PIECE_H

enum class Piece : char {
    Empty  = '.',
    Pawn  = 'P',
    Knight = 'N',
    Bishop = 'B',
    Rook   = 'R',
    Queen  = 'Q',
    King   = 'K',
};

#endif