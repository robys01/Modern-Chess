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





/*
#include <iostream>
#include <fstream>
#include "../headers/Board.h"
#include <string>   // For getline(in, s);


 static const char pieces_[14] = {'.', 'p', 'n', 'b', 'r', 'q', 'k', 'P', 'N', 'B', 'R', 'Q', 'K'};

enum class piece_val{ empty = 0,
    blackPawn = 5, blackKnight = 9, blackBishop = 17, blackRook = 33, blackQueen = 65, blackKing = 129,
    whitePawn = 6, whiteKnight = 10, whiteBishop = 18, whiteRook = 34, whiteQueen = 66, whiteKing = 130
};

std::array<std::array<int, 8>, 8> classicBoard;


// Constructor
Board::Board() {
    boxes.resize(dim);
    for(int i = 0; i < dim; i++)
        boxes[i].resize(dim);
    readFEN();
    resetBoard();
    fillBoard();
    std::cout << "Board Created\n";
}
// Copy Constructor
Board::Board(const Board &copy) {
    for (int i = 0; i < dim; i++)
        for (int j = 0; j < dim; j++)
            this->boxes[i][j] = copy.boxes[i][j];
}
Board::~Board() {
    std::cout << "Board Removed\n";
};

// Operator=
Board &Board::operator=(const Board &board) {
    for (int i = 0; i < dim; i++)
        for (int j = 0; j < dim; j++)
            this->boxes[i][j] = board.boxes[i][j];

    return *this;
}
// Stream output Operator
std::ostream &operator<<(std::ostream &os, const Board &board) {
    for (int i = 0; i < 8; i++, os << '\n') {
        os << 8 - i << "  ";
        for (int j = 0; j < 8; j++)
            os << Board::decode(board.boxes[i][j]) << ' ';
    }
    os << "   ";
    for (int i = 0; i < 8; i++)
        os << (char) ('a' + i) << ' ';
    os << '\n';
    return os;
}

void Board::readFEN() {    // Incomplete
    std::ifstream in("board.txt");
    std::string s;
    getline(in, s);

    int row = 0, column = 0;
    for(int k = 0; s[k] != ' '; k++) {

        if(s[k] == '/') {
            row++;
            column = 0;
            continue;
        }

        if(s[k] > '0' && s[k] < '9') {
            int lenght = s[k] - '0';
            for(int j = column; j < column + lenght; j++)
                classicBoard[row][j] = static_cast<int>(piece_val::empty);
            column +=lenght;

        }

        switch(s[k]) {

            case 'p':
                classicBoard[row][column] = static_cast<int>(piece_val::blackPawn);
                column++;
                break;
            case 'b':
                classicBoard[row][column] = static_cast<int>(piece_val::blackBishop);
                column++;
                break;
            case 'n':
                classicBoard[row][column] = static_cast<int>(piece_val::blackKnight);
                column++;
                break;
            case 'r':
                classicBoard[row][column] = static_cast<int>(piece_val::blackRook);
                column++;
                break;
            case 'q':
                classicBoard[row][column] = static_cast<int>(piece_val::blackQueen);
                column++;
                break;
            case 'k':
                classicBoard[row][column] = static_cast<int>(piece_val::blackKing);
                column++;
                break;
            case 'P':
                classicBoard[row][column] = static_cast<int>(piece_val::whitePawn);
                column++;
                break;
            case 'B':
                classicBoard[row][column] = static_cast<int>(piece_val::whiteBishop);
                column++;
                break;
            case 'N':
                classicBoard[row][column] = static_cast<int>(piece_val::whiteKnight);
                column++;
                break;
            case 'R':
                classicBoard[row][column] = static_cast<int>(piece_val::whiteRook);
                column++;
                break;
            case 'Q':
                classicBoard[row][column] = static_cast<int>(piece_val::whiteQueen);
                column++;
                break;
            case 'K':
                classicBoard[row][column] = static_cast<int>(piece_val::whiteKing);
                column++;
                break;
        }

    }
}

void Board::resetBoard() {
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            boxes[i][j] = static_cast<int>(piece_val::empty);
}

void Board::fillBoard() {
    for(int i = 0; i < dim; i++)
        for(int j = 0; j < dim; j++)
            this->boxes[i][j] = classicBoard[i][j];
}

char Board::decode(int x) {
    int k;
    auto piesa = static_cast<piece_val>(x);

    switch (piesa) {
        default:
            k = 0;
            break;

        case piece_val::whitePawn:
            k = 7;
            break;

        case piece_val::whiteKnight:
            k = 8;
            break;

        case piece_val::whiteBishop:
            k = 9;
            break;

        case piece_val::whiteRook:
            k = 10;
            break;

        case piece_val::whiteQueen:
            k = 11;
            break;

        case piece_val::whiteKing:
            k = 12;
            break;

        case piece_val::blackPawn:
            k = 1;
            break;

        case piece_val::blackKnight:
            k = 2;
            break;

        case piece_val::blackBishop:
            k = 3;
            break;

        case piece_val::blackRook:
            k = 4;
            break;

        case piece_val::blackQueen:
            k = 5;
            break;

        case piece_val::blackKing:
            k = 6;
            break;
    }

    return pieces_[k];
}
*/