//
// Created by Robert on 11/18/2021.
//

#ifndef MODERN_CHESS_GAME_H
#define MODERN_CHESS_GAME_H

#include <memory>
#include "Board.h"
#include "Piece.h"
#include "PieceStats.h"

const int WIDTH = 600;  // momentan global, in viitor citite din fisier
const int HEIGHT = 600;
const int squareSize = HEIGHT / 8; // used for Board positions

const float squareWidth = HEIGHT / 8.0f;    // used for Positioning Pieces
const float defaultWIDTH = 448.0f;
const float scale = HEIGHT / defaultWIDTH;

class Game {
    sf::RenderWindow window;
    Board chessBoard;
    std::vector<std::shared_ptr<Piece>> pieces;
    std::array<sf::RectangleShape, 64> possibleMoves;

    /// Chess mechanics variables
    bool whiteChecked = false;
    bool blackChecked = false;
    bool gameOver = false;

    unsigned int whiteKingPos;
    unsigned int blackKingPos;

    bool whiteTurn;
    bool whiteCastleK;
    bool whiteCastleQ;
    bool blackCastleK;
    bool blackCastleQ;

    int enPassant;
    int nrMoves;
    int nrMovesWithoutCapture;

    PieceStats<Side::WHITE> whiteStats;
    PieceStats<Side::BLACK> blackStats;

public:
    void run();
    static Game& get_app();

private:
    Game();
    ~Game();
    void drawGame();
    void readFEN(const std::string& args);
    void setPieces();
    void setPiece(unsigned int pos);
    friend std::ostream &operator<<(std::ostream &os, const Game &game);
    void printPieces();
    void showInfo();

    bool isPiece(unsigned int i);
    void drawPossibleMove(unsigned int val);
    void resetPossibleMoves();

    void addEnPassantMoves(unsigned int pos, std::vector<unsigned int> &moves);
    void addCastlingKingSide(unsigned int pos, std::vector<unsigned int> &moves);
    void addCastlingQueenSide(unsigned int pos, std::vector<unsigned int> &moves);
    std::vector<unsigned int> legalMoves(unsigned int buttonPos);
    void dragMove(unsigned int buttonPos);
    void make_move(unsigned int start, unsigned int destination);
    void make_castle(unsigned int pos, Side side);
    void castleCheck();


    bool isCheck(Side kingSide, unsigned int position = 64);
    bool isCheckmate(Side kingSide);
};

#endif //MODERN_CHESS_GAME_H
