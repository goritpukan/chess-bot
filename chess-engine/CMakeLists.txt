cmake_minimum_required(VERSION 4.0)
project(ChessEngine)

set(CMAKE_CXX_STANDARD 20)

add_executable(ChessEngine main.cpp)

target_link_libraries(ChessEngine PRIVATE cpp-httplib)