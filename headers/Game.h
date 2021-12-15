//
// Created by Robert on 11/18/2021.
//

#ifndef MODERN_CHESS_GAME_H
#define MODERN_CHESS_GAME_H

#include <memory>
#include "Board.h"
#include "Piece.h"

const int WIDTH = 512;  // momentan global, in viitor citite din fisier
const float squareWidth = WIDTH / 8.0f;

const float defaultWIDTH = 448.0f;
const float scale = WIDTH / defaultWIDTH;

class Game {
    sf::RenderWindow window;
    Board chessBoard;
    std::vector<std::shared_ptr<Piece>> pieces;


public:
    Game();
    ~Game();

    void run();
    void drawGame(sf::RenderWindow &window);
    void readFEN(std::string args);
    void setPieces();
    friend std::ostream &operator<<(std::ostream &os, const Game &game);
};

#endif //MODERN_CHESS_GAME_H
