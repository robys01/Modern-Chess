//
// Created by Robert on 12/13/2021.
//

#ifndef MODERN_CHESS_TEXTURES_H
#define MODERN_CHESS_TEXTURES_H


#include <SFML/Graphics.hpp>

class Textures {
public:
    thread_local static sf::Texture whitePawn;
    thread_local static sf::Texture whiteKnight;
    thread_local static sf::Texture whiteBishop;
    thread_local static sf::Texture whiteRook;
    thread_local static sf::Texture whiteQueen;
    thread_local static sf::Texture whiteKing;

    thread_local static sf::Texture blackPawn;
    thread_local static sf::Texture blackKnight;
    thread_local static sf::Texture blackBishop;
    thread_local static sf::Texture blackRook;
    thread_local static sf::Texture blackQueen;
    thread_local static sf::Texture blackKing;

    static sf::Texture loadTexture(const std::string& str);
};


#endif //MODERN_CHESS_TEXTURES_H
