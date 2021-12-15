//
// Created by Robert on 12/15/2021.
//

#ifndef MODERN_CHESS_CHESSEXCEPTIONS_H
#define MODERN_CHESS_CHESSEXCEPTIONS_H

#include <stdexcept>

class error_chess : public std::runtime_error {
public:
    error_chess(const std::string &arg);
};


class error_fen : public error_chess {
public:
    error_fen();
};


class error_open : public error_chess {
public:
    error_open(const std::string &arg);
};

#endif //MODERN_CHESS_CHESSEXCEPTIONS_H
