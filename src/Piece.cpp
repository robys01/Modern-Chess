//
// Created by Robert on 12/12/2021.
//
#include "../headers/Piece.h"
#include <iostream>


Piece::Piece(){

}

Piece::Piece(PieceType pieceType, Side side) {

    switch(pieceType) {
        case PieceType::Pawn:
            code = (1 << 2) + 1 + (side == Side::WHITE);
            pTexture = side == Side::WHITE ? Textures::whitePawn : Textures::blackPawn;
            break;
        case PieceType::Knight:
            code = (1 << 3) + 1 + (side == Side::WHITE);
            pTexture = side == Side::WHITE ? Textures::whiteKnight : Textures::blackKnight;
            break;
        case PieceType::Bishop:
            code = (1 << 4) + 1 + (side == Side::WHITE);
            pTexture = side == Side::WHITE ? Textures::whiteBishop : Textures::blackBishop;
            break;
        case PieceType::Rook:
            code = (1 << 5) + 1 + (side == Side::WHITE);
            pTexture = side == Side::WHITE ? Textures::whiteRook : Textures::blackRook;
            break;
        case PieceType::Queen:
            code = (1 << 6) + 1 + (side == Side::WHITE);
            pTexture = side == Side::WHITE ? Textures::whiteQueen : Textures::blackQueen;
            break;
        case PieceType::King:
            code = (1 << 7) + 1 + (side == Side::WHITE);
            pTexture = side == Side::WHITE ? Textures::whiteKing : Textures::blackKing;
            break;
        case PieceType::Empty:
            code = 0;
            break;
    }
//    pieceSize = (float)(pTexture.getSize().x + pTexture.getSize().y) / 2.0f;

    pSprite.setOrigin(pieceSize / 2.0f, pieceSize / 2.0f);
//    pSprite.setColor((side == Side::WHITE ? sf::Color::Green : sf::Color::Red));
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
    pSprite = piece.pSprite;        // Both of them are required, Sprite's operator= doesn't
    pSprite.setTexture(pTexture);   // copy the image, resulting a white square

    return *this;
}

std::ostream &operator<<(std::ostream &os, const Piece &piece) {
    os << piece.code;
    return os;
}
