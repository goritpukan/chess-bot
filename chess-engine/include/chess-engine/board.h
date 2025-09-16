#ifndef CHESSENGINE_BOARD_H
#define CHESSENGINE_BOARD_H

#include <string>
#include <vector>

#include "color.h"
#include "move.h"
#include "piece.h"

class Board {
    private:
        char board[8][8];
        std::vector<Move> getAllLegalWhitePawnMoves(int row, int col) const;
        std::vector<Move> getAllLegalBlackPawnMoves(int row, int col) const;
        std::vector<Move> getAllLegalWhiteBishopMoves(int row, int col) const;
    public:
        static std::string convertToAlgNotation(int fromCol, int toCol, int toRow, Piece piece, bool isCapture);
        std::vector<Move> getAllLegalMoves(Color color) const;
        Board(std::string fen);
        void PrintBoard();
};
#endif