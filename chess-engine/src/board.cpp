#include "../include/chess-engine/board.h"
#include "../include/chess-engine/color.h"
#include <cctype>
#include <iostream>
#include <string>

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
    if (piece != Piece::Pawn) {
        result += static_cast<char>(piece);
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

std::vector<std::string> Board::getAllLegalMoves() {
    std::vector<std::string> result;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            switch (board[i][j]) {
                case '.':
                    break;
                case 'P':
                    std::vector<std::string> moves = getAllLegalPawnMoves(i, j, Color::White);
                    result.insert(result.end(), moves.begin(), moves.end());
                    break;

            }
        }
    }
    for (std::string x : result)
        std::cout << x << std::endl;
    return result;
}

//TODO: add check for indexes so they wont outbound from board range
std::vector<std::string> Board::getAllLegalPawnMoves(const int row, const int col, const Color color) {
    std::vector<std::string> result;
    if (color == Color::White) {
        //White pawn makes one move forward
        if (board[row + 1][col] == '.') {
            result.push_back(convertToAlgNotation(col, col, row + 1, Piece::Pawn, false));
        }
        //White pawn makes 2 moves forward
        if (board[row + 2][col] == '.'  && row == 1 && board[row + 1][col] == '.') {
            result.push_back(convertToAlgNotation(col, col, row + 2, Piece::Pawn, false));
        }
        //White pawn capture left
        if (board[row + 1][col + 1] != '.' && !std::isupper(board[row + 1][col + 1])) {
            result.push_back(convertToAlgNotation(col, col + 1, row + 1, Piece::Pawn, true));
        }
        //White pawn capture right
        if (board[row + 1][col - 1] != '.' && !std::isupper(board[row + 1][col - 1])) {
            result.push_back(convertToAlgNotation(col, col - 1, row + 1, Piece::Pawn, true));
        }
    }
    return result;
}

//TODO: REWORK OR DELETE
bool Board::isLegalPawnMove(int fromRow, int fromCol, int toRow, int toCol, Color color) {

    //Move
    if (board[toRow][toCol] == '.') {
        //First white pawn move check
        if (color == Color::White && fromRow == 7 && (toRow == 6 || toRow == 5)) {
            return true;
        }
        //First black pawn move check
        if (color == Color::Black  && fromRow == 2 && (toRow == 3 || toRow == 4)) {
            return true;
        }
        //White pawn move check
        if (color == Color::White  &&  fromRow - toRow > 0 && fromCol == toCol) {
            return true;
        }
        //Black pawn move check
        if (color == Color::Black &&  fromRow - toRow < 0 && fromCol == toCol) {
            return true;
        }
    }

    return false;
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

