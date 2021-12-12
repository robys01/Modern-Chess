//
// Created by Robert on 11/18/2021.
//

#include <iostream>
#include "../headers/Game.h"

Game::Game() :
        window(sf::VideoMode(WIDTH, WIDTH), "Modern Chess", sf::Style::Close),
        chessBoard(WIDTH) {

    setPieces();

}

Game::~Game() = default;

void Game::run() {
    std::cout << chessBoard;
    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                window.close();
            if (e.type == sf::Event::KeyPressed) {
                if (e.key.code == sf::Keyboard::Right) {
                    chessBoard.changeTheme();
                } else if (e.key.code == sf::Keyboard::Left)
                    chessBoard.changeTheme("previous");
            }
        }
        window.clear(sf::Color::Black);
        drawGame(window);
        window.display();
    }
}

void Game::drawGame(sf::RenderWindow &window) {
    chessBoard.drawBoard(window);
    for (int i = 0; i < 64; i++)
        pieces[i].drawPiece(window);

}


std::ostream &operator<<(std::ostream &os, const Game &game) {
    for (int i = 0; i < 64; i++)
        std::cout << game.pieces[i].getCode() << ((i + 1) % 8 ? ' ' : '\n');


    return os;
}

void Game::setPieces() {

    Piece bpawn(PieceType::Pawn, Side::BLACK);
    Piece brook(PieceType::Rook, Side::BLACK);
    Piece bknight(PieceType::Knight, Side::BLACK);
    Piece bbishop(PieceType::Bishop, Side::BLACK);
    Piece bqueen(PieceType::Queen, Side::BLACK);
    Piece bking(PieceType::King, Side::BLACK);

    Piece wpawn(PieceType::Pawn, Side::WHITE);
    Piece wrook(PieceType::Rook, Side::WHITE);
    Piece wknight(PieceType::Knight, Side::WHITE);
    Piece wbishop(PieceType::Bishop, Side::WHITE);
    Piece wqueen(PieceType::Queen, Side::WHITE);
    Piece wking(PieceType::King, Side::WHITE);

    Piece empty(PieceType::Empty, Side::EMPTY);


    pieces.emplace_back(brook);
    pieces.emplace_back(bknight);
    pieces.emplace_back(bbishop);
    pieces.emplace_back(bqueen);
    pieces.emplace_back(bking);
    pieces.emplace_back(bbishop);
    pieces.emplace_back(bknight);
    pieces.emplace_back(brook);

    for (int i = 0; i < 8; i++)
        pieces.emplace_back(bpawn);

    for (int i = 0; i < 32; i++)
        pieces.emplace_back(empty);

    for (int i = 0; i < 8; i++)
        pieces.emplace_back(wpawn);

    pieces.emplace_back(wrook);
    pieces.emplace_back(wknight);
    pieces.emplace_back(wbishop);
    pieces.emplace_back(wqueen);
    pieces.emplace_back(wking);
    pieces.emplace_back(wbishop);
    pieces.emplace_back(wknight);
    pieces.emplace_back(wrook);

    for (int i = 0; i < 64; i++) {
        pieces[i].setPosition(squareWidth * (i % 8) + squareWidth / 2.0f, (squareWidth * (i / 8)) + squareWidth / 2.0f);
//        pieces[i].setPosition(squareWidth * (i % 8), (squareWidth *  (i / 8))); // in case Origin is (0, 0)

        pieces[i].setScale(1 * scale, 1 * scale);
        std::cout << pieces[i] << ((i + 1) % 8 ? ' ' : '\n');
    }

}
