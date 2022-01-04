//
// Created by Robert on 12/12/2021.
//
#include "../headers/Piece.h"
#include <iostream>


/// Class Piece
Piece::Piece(const Side& side) : code(0), side(side) {}

Piece::~Piece() = default;


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

int Piece::getCode() const {
    return code;
}

sf::Vector2f Piece::getPosition() {
    sf::Vector2f pos = pSprite.getPosition();
    return pos;
}

Side Piece::getSide() const {
    return this->side;
}


/// Class Pawn
Pawn::Pawn(const Side &side) : Piece(side){
    code = (1 << 2) + (int) side;
    pSprite.setTexture(side == Side::WHITE ? Textures::whitePawn : Textures::blackPawn);
    pSprite.setOrigin(pSprite.getTexture()->getSize().x / 2, pSprite.getTexture()->getSize().y / 2);
}

Pawn::~Pawn() = default;

void Pawn::canMove() {
    std::cout << "Un pas inainte, 0 inapoi\n";
}

std::shared_ptr<Piece> Pawn::clone() const {
    return std::make_shared <Pawn>(*this);
}


/// Class Knight
Knight::Knight(const Side &side) : Piece(side) {
    code = (1 << 3) + (int) side;
    pSprite.setTexture(side == Side::WHITE ? Textures::whiteKnight : Textures::blackKnight);
    pSprite.setOrigin(pSprite.getTexture()->getSize().x / 2, pSprite.getTexture()->getSize().y / 2);
}

Knight::~Knight() {

}

void Knight::canMove() {
    std::cout<<"Rapa dunga dunga, la piratu-i Punga\n";
}

std::shared_ptr<Piece> Knight::clone() const {
    return std::make_shared <Knight>(*this);
}


/// Class Bishop
Bishop::Bishop(const Side &side) : Piece(side) {
    code = (1 << 4) + (int) side;
    pSprite.setTexture(side == Side::WHITE ? Textures::whiteBishop : Textures::blackBishop);
    pSprite.setOrigin(pSprite.getTexture()->getSize().x / 2, pSprite.getTexture()->getSize().y / 2);
}

Bishop::~Bishop() {

}

void Bishop::canMove() {
    std::cout<<"Dumnezeu sa va binecuvanteze\n";
}

std::shared_ptr<Piece> Bishop::clone() const {
    return std::make_shared <Bishop>(*this);
}

/// Class Rook
Rook::Rook(const Side &side) : Piece(side) {
    code = (1 << 5) + (int) side;
    pSprite.setTexture(side == Side::WHITE ? Textures::whiteRook : Textures::blackRook);
    pSprite.setOrigin(pSprite.getTexture()->getSize().x / 2, pSprite.getTexture()->getSize().y / 2);
}

Rook::~Rook() {

}

void Rook::canMove() {
    std::cout<<"Vine tura cu viteza\n";
}

std::shared_ptr<Piece> Rook::clone() const {
    return std::make_shared <Rook>(*this);
}

/// Class Queen
Queen::Queen(const Side &side) : Piece(side) {
    code = (1 << 6) + (int) side;
    pSprite.setTexture(side == Side::WHITE ? Textures::whiteQueen : Textures::blackQueen);
    pSprite.setOrigin(pSprite.getTexture()->getSize().x / 2, pSprite.getTexture()->getSize().y / 2);
}

Queen::~Queen() {

}

void Queen::canMove() {
    std::cout<<"Ma duc unde vreau\n";
}

std::shared_ptr<Piece> Queen::clone() const {
    return std::make_shared <Queen>(*this);
}

/// Class King
King::King(const Side &side) : Piece(side) {
    code = (1 << 7) + (int) side;
    pSprite.setTexture(side == Side::WHITE ? Textures::whiteKing : Textures::blackKing);
    pSprite.setOrigin(pSprite.getTexture()->getSize().x / 2, pSprite.getTexture()->getSize().y / 2);
}

King::~King() {

}

void King::canMove() {
    std::cout<<"El Patron\n";
}

std::shared_ptr<Piece> King::clone() const {
    return std::make_shared <King>(*this);
}

EmptySpace::EmptySpace() : Piece(Side::EMPTY) {}

EmptySpace::~EmptySpace() = default;

void EmptySpace::canMove() {
    std::cout << "Ce sa muti?\n";
}

std::shared_ptr<Piece> EmptySpace::clone() const {
    return std::make_shared <EmptySpace>(*this);
}
