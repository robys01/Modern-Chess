//
// Created by Robert on 12/13/2021.
//

#include <iostream>
#include "../headers/Textures.h"

sf::Texture Textures::loadTexture(const std::string& str) {
    sf::Texture texture;
    if (!texture.loadFromFile(str))
        std::cout << "Failed to open" << str << '\n';
    texture.setSmooth(true);
    return texture;
}

sf::Texture Textures::whitePawn = Textures::loadTexture("resources/wP.png");
sf::Texture Textures::whiteKnight = Textures::loadTexture("resources/wN.png");
sf::Texture Textures::whiteBishop = Textures::loadTexture("resources/wB.png");
sf::Texture Textures::whiteRook = Textures::loadTexture("resources/wR.png");
sf::Texture Textures::whiteQueen = Textures::loadTexture("resources/wQ.png");
sf::Texture Textures::whiteKing = Textures::loadTexture("resources/wK.png");

sf::Texture Textures::blackPawn = Textures::loadTexture("resources/bP.png");
sf::Texture Textures::blackKnight = Textures::loadTexture("resources/bN.png");
sf::Texture Textures::blackBishop = Textures::loadTexture("resources/bB.png");
sf::Texture Textures::blackRook = Textures::loadTexture("resources/bR.png");
sf::Texture Textures::blackQueen = Textures::loadTexture("resources/bQ.png");
sf::Texture Textures::blackKing = Textures::loadTexture("resources/bK.png");