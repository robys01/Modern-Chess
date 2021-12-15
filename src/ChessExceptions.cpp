//
// Created by Robert on 12/15/2021.
//

#include "../headers/ChessExceptions.h"


error_chess::error_chess(const std::string &arg) : runtime_error("Chess error: " + arg) {}


error_fen::error_fen() : error_chess("Invalid FEN board.\n") {}


error_open::error_open(const std::string &arg) : error_chess("Failed to open \"" + arg + '\"') {}
