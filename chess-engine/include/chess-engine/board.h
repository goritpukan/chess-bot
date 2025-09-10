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
        bool isLegalPawnMove(int fromRow, int fromCol, int toRow, int toCol, Color color);
        std::vector<Move> getAllLegalPawnMoves(int row, int col, Color color);
    public:
        static std::string convertToAlgNotation(int fromCol, int toCol, int toRow, Piece piece, bool isCapture);
        std::vector<std::string> getAllLegalMoves();
        Board(std::string fen);
        void PrintBoard();
};
#endif