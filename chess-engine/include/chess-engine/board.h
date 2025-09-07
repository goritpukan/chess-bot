#ifndef CHESSENGINE_BOARD_H
#define CHESSENGINE_BOARD_H

#include <string>

class Board {
    private:
        char board[8][8];
    public:
        Board(std::string fen);
        void PrintBoard();
};

#endif