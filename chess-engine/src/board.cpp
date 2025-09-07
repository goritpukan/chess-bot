#include "../include/chess-engine/board.h"
#include <cctype>
#include <iostream>
#include <string>

Board::Board(std::string fen) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = '.';
        }
    }
    int row = 0, col = 0;
    for (const char c : fen) {
        if (c == '/') {
            col = 0;
            row++;
            continue;
        }
        if (isdigit(c)) {
            col += c - '0';
            continue;
        }
        if (c == ' ') {
            break;
        }
        if (row >= 8 || col >= 8) {
            break;
        }
        board[row][col] = c;
        col++;
    }
}

void Board::PrintBoard() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            std::cout << board[i][j];
            if (j == 7) {
                std::cout << std::endl;
            }
        }
    }
}
