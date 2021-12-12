//
// Created by Robert on 11/18/2021.
//

#ifndef MODERN_CHESS_GAME_H
#define MODERN_CHESS_GAME_H

#include "Board.h"
#include "Piece.h"

const int WIDTH = 512;
const float squareWidth = WIDTH / 8.0f;

const float defaultWIDTH = 488.0f;
const float scale = WIDTH / defaultWIDTH;

class Game {
    sf::RenderWindow window;
    Board chessBoard;
    std::vector<Piece> pieces;


public:
    Game();
    ~Game();

    void run();
    void drawGame(sf::RenderWindow &window);
    void setPieces();
    friend std::ostream &operator<<(std::ostream &os, const Game &game);
};

#endif //MODERN_CHESS_GAME_H
