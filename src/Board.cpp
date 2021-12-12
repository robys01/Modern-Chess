//
// Created by Robert on 12/9/2021.
//
#include <iostream>
#include "../headers/Board.h"


Board::Board(const int boardHeight, sf::Color color1, sf::Color color2)
        : squareSize((float)boardHeight / 8.0f), color1(color1), color2(color2) {

    font.loadFromFile("resources/arial.ttf");
    setBoard();
    setRows();
    setColumns();
    setThemes();
}

Board::~Board() = default;

void Board::setBoard() {
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            board[i * 8 + j].setPosition(squareSize * i, squareSize * j);
            board[i * 8 + j].setSize(sf::Vector2f(squareSize, squareSize));
            board[i * 8 + j].setFillColor(((i + j) % 2 ? color1 : color2));
        }
    }
}

void Board::setRows() {
    for(int i = 0; i < 8; i++) {
        row[i].setFont(font);
        row[i].setString(char('8' - i));
        row[i].setPosition(squareSize / 32, 0.0f + i * squareSize);
        row[i].setCharacterSize((int) squareSize / 4);
        row[i].setFillColor((i % 2 ? color2 : color1));
    }
}

void Board::setColumns() {
    for(int i = 0; i < 8; i++) {
        column[i].setFont(font);
        column[i].setString(char('a' + i));
        column[i].setPosition(squareSize * 0.81f + i * squareSize, (squareSize * 8) * 0.96f);
        column[i].setCharacterSize((int) squareSize / 4);
        column[i].setFillColor((i % 2 ? color1 : color2));
    }
}
void Board::setThemes() {
    themes.emplace_back(sf::Color(139,69,19), sf::Color(222,184,135));  // Light Brown & Brown
    themes.emplace_back(sf::Color(159, 90, 253), sf::Color(192, 192, 192)); // Purple & Silver
    themes.emplace_back(sf::Color(22, 22, 22), sf::Color::White); // Black & White
    themes.emplace_back(sf::Color::Blue, sf::Color::Red);
    themes.emplace_back(sf::Color(184, 139, 74), sf::Color(227, 193, 111)); // Yellow Theme
}

void Board::changeTheme(const std::string& str) {
    static unsigned long long x = 0;
    if(str == "next") {
        x++;
        x %= themes.size();
    } else if(str == "previous") {
        x--;
        x > themes.size() ? x = themes.size() - 1 : x = x;
    }
    changeColors(themes[x].first, themes[x].second);
}


void Board::changeColors(sf::Color Color1, sf::Color Color2) {
    this->color1 = Color1;
    this->color2 = Color2;

    for(int i = 0; i < 8; i++) {
        row[i].setFillColor((i % 2 ? color2 : color1));
        column[i].setFillColor((i % 2 ? color1 : color2));
        for(int j = 0; j < 8; j++)
            board[i * 8 + j].setFillColor((i + j) % 2 ? color1 : color2);
    }
}

void Board::drawBoard(sf::RenderWindow &window) {
    for(int i = 0; i < 64; i++)
        window.draw(board[i]);
    for(int i = 0; i < 8; i++) {
        window.draw(row[i]);
        window.draw(column[i]);
    }
}

std::ostream &operator<<(std::ostream &os, const Board &board1) {

    for(int i = 0; i < 8; i++, os << '\n')
        for(int j = 0; j < 8; j++)
            os << board1.board[i * 8 + j].getPosition().x << ' ' << board1.board[i * 8 + j].getPosition().y << "  ";


    return os;
}



