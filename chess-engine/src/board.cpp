#include "../include/chess-engine/board.h"
#include <cctype>
#include <iostream>
#include <string>

#include "../include/chess-engine/move.h"
#include "../include/chess-engine/piece.h"

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
    for (int i = 0; i < 4; ++i) {
        std::swap(board[i], board[7 - i]);
    }
}

std::string Board::convertToAlgNotation(const int fromCol, const int toCol, const int toRow, const Piece piece, const bool isCapture) {
    std::string result;
    if (piece != Piece::WhitePawn && piece != Piece::BlackPawn) {
        result += toupper(static_cast<char>(piece));
    }else if (isCapture) {
        result += std::string(1, 'a' + fromCol);
    }

    if (isCapture) {
        result += "x";
    }
    result += std::string(1, 'a' + toCol);
    result += std::to_string(toRow + 1);
    return result;
}

std::vector<Move> Board::getAllLegalMoves(const Color color) const {
    std::vector<Move> moves;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (color == Color::White) {
                switch (board[i][j]) {
                    case '.':
                        break;
                    case 'P': {
                        std::vector<Move> whitePawnMoves = getAllLegalWhitePawnMoves(i, j);
                        moves.insert(moves.end(), whitePawnMoves.begin(), whitePawnMoves.end());
                        break;
                    }
                    case 'B': {
                        std::vector<Move> whiteBishopMoves = getAllLegalWhiteBishopMoves(i, j);
                        moves.insert(moves.end(), whiteBishopMoves.begin(), whiteBishopMoves.end());
                        break;
                    }

                }
            }else {
                switch (board[i][j]) {
                    case '.':
                        break;
                    case 'p': {
                        std::vector<Move> blackPawnMoves = getAllLegalBlackPawnMoves(i, j);
                        moves.insert(moves.end(), blackPawnMoves.begin(), blackPawnMoves.end());
                        break;
                    }
                }
            }
        }
    }
    for (Move move : moves) {
        std::cout << convertToAlgNotation((int)move.fromCol, (int)move.toCol, (int)move.toRow, move.piece, move.isCapture) << std::endl;
    }
    return moves;
}

std::vector<Move> Board::getAllLegalWhitePawnMoves(const int row, const int col) const {
    std::vector<Move> moves;
    //White pawn makes one move forward
    if (row + 1 <= 7 && board[row + 1][col] == '.') {
        moves.emplace_back(row, col, row + 1, col, false, Piece::WhitePawn);
    }
    //White pawn makes 2 moves forward
    if (row + 2 <= 7 && board[row + 2][col] == '.' && row == 1 && board[row + 1][col] == '.') {
        moves.emplace_back(row, col, row + 2, col, false, Piece::WhitePawn);
    }
    //White pawn capture left
    if (row + 1 <= 7 && col + 1 <= 7 && board[row + 1][col + 1] != '.' && !std::isupper(board[row + 1][col + 1])) {
        moves.emplace_back(row, col, row + 1, col + 1, true, Piece::WhitePawn);
    }
    //White pawn capture right
    if (row + 1 <= 7 && col - 1 >= 0 && board[row + 1][col - 1] != '.' && !std::isupper(board[row + 1][col - 1])) {
        moves.emplace_back(row, col, row + 1, col - 1, true, Piece::WhitePawn);
    }
    return moves;
}

std::vector<Move> Board::getAllLegalBlackPawnMoves(const int row, const int col) const {
    std::vector<Move> moves;
    //Black pawn makes 1 move forward
    if (row - 1 >= 0 && board[row - 1][col] == '.') {
        moves.emplace_back(row, col, row - 1, col, false, Piece::BlackPawn);
    }
    //Black pawn makes 2 moves forward
    if (row - 2 >= 0 && board[row - 2][col] == '.' && row == 6 && board[row -1][col] == '.') {
        moves.emplace_back(row, col, row - 2, col, false, Piece::BlackPawn);
    }
    //Black pawn capture right
    if (row - 1 >= 0 && col + 1 <= 7 && board[row - 1][col + 1] != '.' && std::isupper(board[row - 1][col + 1])) {
        moves.emplace_back(row, col, row - 1, col + 1, true, Piece::BlackPawn);
    }
    //Black pawn capture left
    if (row - 1 >= 0 && col - 1 >= 0 && board[row - 1][col - 1] != '.' && std::isupper(board[row - 1][col - 1])) {
        moves.emplace_back(row, col, row - 1, col - 1, true, Piece::BlackPawn);
    }
    return moves;
}

std::vector<Move> Board::getAllLegalWhiteBishopMoves(int row, int col) const {
    std::vector<Move> moves;
    int localRow = row, localCol = col;
    //Check move left and up
    while (localRow >= 0 && localCol >= 0) {
        localRow--;
        localCol--;
        if (localRow < 0 || localCol < 0) {
            break;
        }
        if (board[localRow][localCol] != '.' && !std::isupper(board[localRow][localCol])) {
            moves.emplace_back(row, col, localCol, localCol, true, Piece::BlackBishop);
            break;
        }
        moves.emplace_back(row, col, localCol, localCol, false, Piece::WhiteBishop);
    }
    return moves;
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

