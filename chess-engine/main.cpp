#define CPPHTTPLIB_IMPL
#include "httplib.h"
#include <iostream>
#include <string>
using namespace httplib;

int main() {
    Server svr;
    svr.Get("/", [](const Request& req, Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_content("e5", "text/plain");
    });

    std::cout << "Listening on port 8080..." << std::endl;
    svr.listen("0.0.0.0", 8080);
    return 0;
}
