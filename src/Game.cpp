//
// Created by Robert on 11/18/2021.
//

#include <iostream>
#include <fstream>
#include <string>
#include "../headers/Game.h"
#include "../headers/ChessExceptions.h"

Game::Game() :
        window(sf::VideoMode(WIDTH, WIDTH), "Modern Chess", sf::Style::Close),
        chessBoard(WIDTH) {

    try {
        readFEN("board.txt");
        setPieces();
    } catch (error_chess &error) {
        std::terminate();   // implicit si std::cerr << error.what();
    }
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
    for (auto &it: pieces)
        it->drawPiece(window);
}


std::ostream &operator<<(std::ostream &os, const Game &game) {
    for (unsigned int i = 0; i < game.pieces.size(); i++)
        std::cout << (*game.pieces[i]) << ((i + 1) % 8 ? " " : "\n");

    return os;
}

void Game::readFEN(std::string args) {
    std::ifstream fin(args);
    if (!fin.is_open())
        throw error_open(args);

    std::string s;
    getline(fin, s);

    int i, nrElements = 0, nrKings = 0;
    for (i = 0; s[i] != ' '; i++) {
        if (s[i] == 'K' || s[i] == 'k')
            nrKings++;
        if (nrKings > 2)
            throw error_fen();

        if (s[i] >= '1' && s[i] <= '9') {
            nrElements += (int) s[i] - '0';
            for (int j = (int) (s[i] - '0'); j > 0; j--)
                pieces.push_back(std::make_shared<Piece>());
        }

        switch (s[i]) {
            case 'p':
                pieces.push_back(std::make_shared<Pawn>(Side::BLACK));
                nrElements++;
                break;
            case 'P':
                pieces.push_back(std::make_shared<Pawn>(Side::WHITE));
                nrElements++;
                break;

            case 'n':
                pieces.push_back(std::make_shared<Knight>(Side::BLACK));
                nrElements++;
                break;
            case 'N':
                pieces.push_back(std::make_shared<Knight>(Side::WHITE));
                nrElements++;
                break;

            case 'b':
                pieces.push_back(std::make_shared<Bishop>(Side::BLACK));
                nrElements++;
                break;
            case 'B':
                pieces.push_back(std::make_shared<Bishop>(Side::WHITE));
                nrElements++;
                break;

            case 'r':
                pieces.push_back(std::make_shared<Rook>(Side::BLACK));
                nrElements++;
                break;
            case 'R':
                pieces.push_back(std::make_shared<Rook>(Side::WHITE));
                nrElements++;
                break;

            case 'q':
                pieces.push_back(std::make_shared<Queen>(Side::BLACK));
                nrElements++;
                break;
            case 'Q':
                pieces.push_back(std::make_shared<Queen>(Side::WHITE));
                nrElements++;
                break;

            case 'k':
                pieces.push_back(std::make_shared<King>(Side::BLACK));
                nrElements++;
                break;
            case 'K':
                pieces.push_back(std::make_shared<King>(Side::WHITE));
                nrElements++;
                break;

        }
    }
    if (nrKings != 2)
        throw error_fen();

    if (nrElements != 64)
        throw error_fen();

    fin.close();
}

void Game::setPieces() {
    for (unsigned int i = 0; i < pieces.size(); i++) {

        pieces[i]->setPosition(squareWidth * (i % 8) + squareWidth / 2.0f,
                               (squareWidth * (i / 8)) + squareWidth / 2.0f);
        pieces[i]->setScale(1 * scale, 1 * scale);
//        std::cout << (*pieces[i]) << ((i + 1) % 8 ? ' ' : '\n');
    }
}
