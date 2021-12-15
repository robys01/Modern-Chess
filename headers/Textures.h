//
// Created by Robert on 12/13/2021.
//

#ifndef MODERN_CHESS_TEXTURES_H
#define MODERN_CHESS_TEXTURES_H


#include <SFML/Graphics.hpp>

class Textures {
public:
    static sf::Texture whitePawn;
    static sf::Texture whiteKnight;
    static sf::Texture whiteBishop;
    static sf::Texture whiteRook;
    static sf::Texture whiteQueen;
    static sf::Texture whiteKing;

    static sf::Texture blackPawn;
    static sf::Texture blackKnight;
    static sf::Texture blackBishop;
    static sf::Texture blackRook;
    static sf::Texture blackQueen;
    static sf::Texture blackKing;

    static sf::Texture loadTexture(const std::string& str);
};


#endif //MODERN_CHESS_TEXTURES_H
