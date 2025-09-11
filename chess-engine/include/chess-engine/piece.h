#ifndef CHESSENGINE_PIECE_H
#define CHESSENGINE_PIECE_H

enum class Piece : char {
    Empty  = '.',
    WhitePawn  = 'P',
    WhiteKnight = 'N',
    WhiteBishop = 'B',
    WhiteRook   = 'R',
    WhiteQueen  = 'Q',
    WhiteKing   = 'K',
    BlackPawn  = 'p',
    BlackKnight = 'n',
    BlackBishop = 'b',
    BlackRook   = 'r',
    BlackQueen  = 'q',
    BlackKing   = 'k'
};

#endif