#define CPPHTTPLIB_IMPL
#include "httplib.h"
#include "../include/chess-engine/board.h"
#include <iostream>
#include <string>
using namespace httplib;

int main() {
    Server svr;
    svr.Post("/", [](const Request &req, Response &res) {
        Board* board = new Board(req.body);
        board->getAllLegalMoves(Color::White);
        board->PrintBoard();
        delete board;
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_content("e5", "text/plain");
    });

    std::cout << "Listening on port 8080..." << std::endl;
    svr.listen("0.0.0.0", 8080);
    return 0;
}
