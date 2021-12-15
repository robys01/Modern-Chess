//
// Created by Robert on 12/8/2021.
//
#ifndef MODERN_CHESS_BOARD_H
#define MODERN_CHESS_BOARD_H


#include <SFML/Graphics.hpp>    // includes vector & array ???
//#include <vector>
//#include <array>

class Board {
    float squareSize;
    std::array<sf::RectangleShape, 64> board;
    std::array<sf::Text, 8> row, column;

    std::vector<std::pair<sf::Color, sf::Color>> themes;
    sf::Color color1;
    sf::Color color2;
    sf::Font font;

    static const sf::Color defaultColor1;
    static const sf::Color defaultColor2;

public:
    // Constructor and Destructor
    Board(int boardHeight, sf::Color color1 = defaultColor1, sf::Color color2 = defaultColor2);
    ~Board();

    void setBoard();
    void setRows();
    void setColumns();
    void setThemes();
    void changeTheme(const std::string& str = std::string("next"));
    void changeColors(sf::Color Color1, sf::Color Color2);
    void drawBoard(sf::RenderWindow &window);
    friend std::ostream &operator<<(std::ostream &os, const Board &board1);
};

#endif //MODERN_CHESS_BOARD_H
