//
// Created by Robert on 12/12/2021.
//
#include "../headers/Piece.h"
#include <iostream>


/// Class Piece
Piece::Piece() {
    code = 0;
    side = Side::EMPTY;

}

Piece::~Piece() = default;

void Piece::canMove() {
    std::cout << "Ce sa muti?\n";
}

void Piece::setPosition(float x, float y) {
    pSprite.setPosition(x, y);
}

void Piece::drawPiece(sf::RenderWindow &window) {
    window.draw(pSprite);
}

std::ostream &operator<<(std::ostream &os, const Piece &piece) {
    os << piece.code;
    return os;
}

void Piece::setScale(float x, float y) {
    pSprite.setScale(x, y);
}

void Piece::setOrigin(float x, float y) {
    pSprite.setOrigin(x, y);
}


/// Class Pawn
Pawn::Pawn(const Side &side) {
    this->side = side;
    code = (1 << 2) + (int) side;
    pSprite.setTexture(side == Side::WHITE ? Textures::whitePawn : Textures::blackPawn);
    pSprite.setOrigin(pSprite.getTexture()->getSize().x / 2, pSprite.getTexture()->getSize().y / 2);
}

Pawn::~Pawn() = default;

void Pawn::canMove() {
    std::cout << "Doar in fata\n";
}


/// Class Knight(int)side
Knight::Knight(const Side &side) {
    this->side = side;
    code = (1 << 3) + (int) side;
    pSprite.setTexture(side == Side::WHITE ? Textures::whiteKnight : Textures::blackKnight);
    pSprite.setOrigin(pSprite.getTexture()->getSize().x / 2, pSprite.getTexture()->getSize().y / 2);
}

Knight::~Knight() {

}

void Knight::canMove() {
    Piece::canMove();
}


/// Class Bishop
Bishop::Bishop(const Side &side) {
    this->side = side;
    code = (1 << 4) + (int) side;
    pSprite.setTexture(side == Side::WHITE ? Textures::whiteBishop : Textures::blackBishop);
    pSprite.setOrigin(pSprite.getTexture()->getSize().x / 2, pSprite.getTexture()->getSize().y / 2);
}

Bishop::~Bishop() {

}

void Bishop::canMove() {
    Piece::canMove();
}

/// Class Rook
Rook::Rook(const Side &side) {
    this->side = side;
    code = (1 << 5) + (int) side;
    pSprite.setTexture(side == Side::WHITE ? Textures::whiteRook : Textures::blackRook);
    pSprite.setOrigin(pSprite.getTexture()->getSize().x / 2, pSprite.getTexture()->getSize().y / 2);
}

Rook::~Rook() {

}

void Rook::canMove() {
    Piece::canMove();
}

/// Class Queen
Queen::Queen(const Side &side) {
    this->side = side;
    code = (1 << 6) + (int) side;
    pSprite.setTexture(side == Side::WHITE ? Textures::whiteQueen : Textures::blackQueen);
    pSprite.setOrigin(pSprite.getTexture()->getSize().x / 2, pSprite.getTexture()->getSize().y / 2);
}

Queen::~Queen() {

}

void Queen::canMove() {
    Piece::canMove();
}

/// Class King
King::King(const Side &side) {
    this->side = side;
    code = (1 << 7) + (int) side;
    pSprite.setTexture(side == Side::WHITE ? Textures::whiteKing : Textures::blackKing);
    pSprite.setOrigin(pSprite.getTexture()->getSize().x / 2, pSprite.getTexture()->getSize().y / 2);
}

King::~King() {

}

void King::canMove() {
    Piece::canMove();
}
