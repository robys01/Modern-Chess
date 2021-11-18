//
// Created by Robert on 11/18/2021.
//

#ifndef MODERN_CHESS_BOARD_H
#define MODERN_CHESS_BOARD_H

#include <iostream>
#include <fstream>
#include <array>
#include <vector>

/*
 * Notations in binary code:
 *
*  Pawn    = 0000 0100
*  Knight  = 0000 1000
*  Bishop  = 0001 0000
*  Rook    = 0010 0000
*  Queen   = 0100 0000
*  King    = 1000 0000
*
*  Black   = 0000 0001
*  White   = 0000 0010
 *
 *  Changed implicit notation.
*/


class Board {
    const int dim = 8;
    std::vector<std::vector<int>> boxes;    // std::vector<std::vector<int>> boxes(dim, std::vector<int>(dim)) doesn't work in a class ???

public:
    // Constructor
    Board();

    // Copy Constructor
    Board(const Board &copy);

    ~Board() {
        std::cout << "Board Removed\n";
    }

    // Operator=
    Board &operator=(const Board &board);

    // Stream output Operator
    friend std::ostream &operator<<(std::ostream &os, const Board &board);

    void readFEN();


    void resetBoard();

    void fillBoard();

    static const char decode(int x);
};

#endif //MODERN_CHESS_BOARD_H
