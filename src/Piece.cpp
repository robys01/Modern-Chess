//
// Created by Robert on 12/12/2021.
//
#include "../headers/Piece.h"
#include <iostream>


Piece::Piece(){
    if(loadTextures())
        std::cout << "Could not load textures";
}

Piece::Piece(PieceType pieceType, Side side) {
    if(loadTextures())
        std::cout << "Could not load textures"; // EXIT() ?

    switch(pieceType) {
        case PieceType::Pawn:
            code = (1 << 2) + 1 + (side == Side::WHITE);
            pTexture = side == Side::WHITE ? whitePawnTexture : blackPawnTexture;
            break;
        case PieceType::Knight:
            code = (1 << 3) + 1 + (side == Side::WHITE);
            pTexture = side == Side::WHITE ? whiteKnightTexture : blackKnightTexture;
            break;
        case PieceType::Bishop:
            code = (1 << 4) + 1 + (side == Side::WHITE);
            pTexture = side == Side::WHITE ? whiteBishopTexture : blackBishopTexture;
            break;
        case PieceType::Rook:
            code = (1 << 5) + 1 + (side == Side::WHITE);
            pTexture = side == Side::WHITE ? whiteRookTexture : blackRookTexture;
            break;
        case PieceType::Queen:
            code = (1 << 6) + 1 + (side == Side::WHITE);
            pTexture = side == Side::WHITE ? whiteQueenTexture : blackQueenTexture;
            break;
        case PieceType::King:
            code = (1 << 7) + 1 + (side == Side::WHITE);
            pTexture = side == Side::WHITE ? whiteKingTexture : blackKingTexture;
            break;
        case PieceType::Empty:
            code = 0;
            break;
    }
//    pieceSize = (float)(pTexture.getSize().x + pTexture.getSize().y) / 2.0f;

    pSprite.setOrigin(pieceSize / 2.0f, pieceSize / 2.0f);

    pTexture.setSmooth(true);
    pSprite.setTexture(pTexture);

}
Piece::Piece(const Piece &piece) {
    code = piece.code;
    pieceType = piece.pieceType;
    side = piece.side;

    pTexture = piece.pTexture;
    pSprite = piece.pSprite;        // Both of them are required, Sprite operator= doesn't
    pSprite.setTexture(pTexture);   // copy the image, resulting a white square
}


Piece::~Piece() = default;

int Piece::loadTextures() {

    if(!whitePawnTexture.loadFromFile("resources/wP.png"))
        return EXIT_FAILURE;
    if(!whiteKnightTexture.loadFromFile("resources/wN.png"))
        return EXIT_FAILURE;
    if(!whiteBishopTexture.loadFromFile("resources/wB.png"))
        return EXIT_FAILURE;
    if(!whiteRookTexture.loadFromFile("resources/wR.png"))
        return EXIT_FAILURE;
    if(!whiteQueenTexture.loadFromFile("resources/wQ.png"))
        return EXIT_FAILURE;
    if(!whiteKingTexture.loadFromFile("resources/wK.png"))
        return EXIT_FAILURE;

    if(!blackPawnTexture.loadFromFile("resources/bP.png"))
        return EXIT_FAILURE;
    if(!blackKnightTexture.loadFromFile("resources/bN.png"))
        return EXIT_FAILURE;
    if(!blackBishopTexture.loadFromFile("resources/bB.png"))
        return EXIT_FAILURE;
    if(!blackRookTexture.loadFromFile("resources/bR.png"))
        return EXIT_FAILURE;
    if(!blackQueenTexture.loadFromFile("resources/bQ.png"))
        return EXIT_FAILURE;
    if(!blackKingTexture.loadFromFile("resources/bK.png"))
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

void Piece::drawPiece(sf::RenderWindow &window) {
    window.draw(pSprite);
}

void Piece::setPosition(float x, float y) {
    pSprite.setPosition(x, y);
}

void Piece::setScale(float x, float y) {
    pSprite.setScale(x, y);
}

int Piece::getCode() const {
    return code;
}

Piece Piece::operator=(const Piece &piece) {
    code = piece.code;
    pieceType = piece.pieceType;
    side = piece.side;

    pTexture = piece.pTexture;
    pSprite = piece.pSprite;
    pSprite.setTexture(pTexture);

    return *this;
}

std::ostream &operator<<(std::ostream &os, const Piece &piece) {
    os << piece.code;
    return os;
}
