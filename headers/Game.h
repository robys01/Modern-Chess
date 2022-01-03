//
// Created by Robert on 11/18/2021.
//

#ifndef MODERN_CHESS_GAME_H
#define MODERN_CHESS_GAME_H

#include <memory>
#include "Board.h"
#include "Piece.h"

const int WIDTH = 512;  // momentan global, in viitor citite din fisier
const int HEIGHT = 512;
const int squareSize = HEIGHT / 8; // used for Board positions

const float squareWidth = HEIGHT / 8.0f;    // used for Positioning Pieces
const float defaultWIDTH = 448.0f;
const float scale = HEIGHT / defaultWIDTH;

class Game {
    sf::RenderWindow window;
    Board chessBoard;
    std::vector<std::shared_ptr<Piece>> pieces;
    std::array<sf::RectangleShape, 64> possibleMoves;

    bool whiteChecked = false;
    bool blackChecked = false;

    bool whiteTurn;
    bool whiteCastleK;
    bool whiteCastleQ;
    bool blackCastleK;
    bool blackCastleQ;

    int enPassant;
    int nrMoves;
    int nrMovesWithoutCapture;

public:
    Game();
    ~Game();

    void run();
    void drawGame();
    void readFEN(const std::string& args);
    void setPieces();
    friend std::ostream &operator<<(std::ostream &os, const Game &game);

    bool isPiece(unsigned int i);
    void dragMove(unsigned int buttonPos);
    void drawPossibleMove(unsigned int val);
    void resetPossibleMoves();
    void make_move(unsigned int start, unsigned int destination);

    std::vector<unsigned int> pawnMoves(unsigned int i);
    std::vector<unsigned int> knightMoves(unsigned int pos);
    std::vector<unsigned int> bishopMoves(unsigned int pos);
    std::vector<unsigned int> rookMoves(unsigned int pos);
    std::vector<unsigned int> queenMoves(unsigned int pos);
    std::vector<unsigned int> kingMoves(unsigned int pos);
};

#endif //MODERN_CHESS_GAME_H
