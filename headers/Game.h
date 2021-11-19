//
// Created by Robert on 11/18/2021.
//

#ifndef MODERN_CHESS_GAME_H
#define MODERN_CHESS_GAME_H

#include <vector>
#include <string>
#include "Board.h"
#include "Player.h"

class Game {

    Board board;
    Player playerWhite, playerBlack;
    std::vector<std::string> moveHistory;
    bool gameEnded;

public:
    Game();
    ~Game() = default;

    friend std::ostream &operator<<(std::ostream &os, Game &game);
    void showBoard();
    void setWhite(Player &player);

    Player getWhite() const;

    void setBlack(Player &player);

    Player getBlack() const;
};

#endif //MODERN_CHESS_GAME_H
