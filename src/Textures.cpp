//
// Created by Robert on 12/13/2021.
//

#include <iostream>
#include "../headers/Textures.h"
#include "../headers/ChessExceptions.h"

sf::Texture Textures::loadTexture(const std::string &str) {
    sf::Texture texture;
    if (!texture.loadFromFile(str))
        throw error_open(str);  // std::cout << "Failed to open" << str << '\n';
    texture.setSmooth(true);
    return texture;
}

thread_local sf::Texture Textures::whitePawn = Textures::loadTexture("resources/wP.png");
thread_local sf::Texture Textures::whiteKnight = Textures::loadTexture("resources/wN.png");
thread_local sf::Texture Textures::whiteBishop = Textures::loadTexture("resources/wB.png");
thread_local sf::Texture Textures::whiteRook = Textures::loadTexture("resources/wR.png");
thread_local sf::Texture Textures::whiteQueen = Textures::loadTexture("resources/wQ.png");
thread_local sf::Texture Textures::whiteKing = Textures::loadTexture("resources/wK.png");

thread_local sf::Texture Textures::blackPawn = Textures::loadTexture("resources/bP.png");
thread_local sf::Texture Textures::blackKnight = Textures::loadTexture("resources/bN.png");
thread_local sf::Texture Textures::blackBishop = Textures::loadTexture("resources/bB.png");
thread_local sf::Texture Textures::blackRook = Textures::loadTexture("resources/bR.png");
thread_local sf::Texture Textures::blackQueen = Textures::loadTexture("resources/bQ.png");
thread_local sf::Texture Textures::blackKing = Textures::loadTexture("resources/bK.png");