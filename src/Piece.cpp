//
// Created by Robert on 12/12/2021.
//
#include "../headers/Piece.h"
#include <iostream>


/// Class Piece
Piece::Piece(const Side &side) : code(0), side(side) {}

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
Pawn::Pawn(const Side &side) : Piece(side) {
    code = (1 << 2) + (int) side;
    pSprite.setTexture(side == Side::WHITE ? Textures::whitePawn : Textures::blackPawn);
    pSprite.setOrigin(pSprite.getTexture()->getSize().x / 2, pSprite.getTexture()->getSize().y / 2);
}

Pawn::~Pawn() = default;

void Pawn::isPressed() {
    std::cout << "Un pas inainte, 0 inapoi\n";
}

std::shared_ptr<Piece> Pawn::clone() const {
    return std::make_shared<Pawn>(*this);
}

std::vector<unsigned int> Pawn::canMove(std::vector<std::shared_ptr<Piece>> &pieces, unsigned int pos) {
    /// Could've done it way better but it worked on the first try so... :P
    std::vector<unsigned int> moves;

    if (pieces[pos]->getCode() & (int) Side::BLACK) {
        // Promote
        if (pos > 55) return moves;
        // Simple move
        if (pieces[pos + 8]->getCode() == 0)
            moves.push_back(pos + 8);

        // Possible 2 squares move
        if (pos >= 8 && pos <= 15)
            if (pieces[pos + 16]->getCode() == 0 && pieces[pos + 8]->getCode() == 0)
                moves.push_back(pos + 16);

        // Left capture black pawn
        if (pos % 8 != 0 && pieces[pos + 7]->getSide() == Side::WHITE)
            moves.push_back(pos + 7);
        // Right capture black pawn
        if ((pos + 1) % 8 != 0 && pieces[pos + 9]->getSide() == Side::WHITE)
            moves.push_back(pos + 9);

    } else if (pieces[pos]->getCode() & (int) Side::WHITE) {
        // Promote
        if (pos < 8) return moves;

        // Simple move
        if (pieces[pos - 8]->getCode() == 0)
            moves.push_back(pos - 8);

        // Possible 2 squares move
        if (pos >= 47 && pos <= 56)
            if (pieces[pos - 16]->getCode() == 0 && pieces[pos - 8]->getCode() == 0)
                moves.push_back(pos - 16);

        // Left capture white pawn
        if (pos % 8 != 0 && pieces[pos - 9]->getCode() & (int) Side::BLACK)
            moves.push_back(pos - 9);
        // Right capture black pawn
        if ((pos + 1) % 8 != 0 && pieces[pos - 7]->getCode() & (int) Side::BLACK)
            moves.push_back(pos - 7);

    }

    return moves;
}


/// Class Knight
Knight::Knight(const Side &side) : Piece(side) {
    code = (1 << 3) + (int) side;
    pSprite.setTexture(side == Side::WHITE ? Textures::whiteKnight : Textures::blackKnight);
    pSprite.setOrigin(pSprite.getTexture()->getSize().x / 2, pSprite.getTexture()->getSize().y / 2);
}

Knight::~Knight() {

}

void Knight::isPressed() {
    std::cout << "Rapa dunga dunga, la piratu-i Punga\n";
}

std::shared_ptr<Piece> Knight::clone() const {
    return std::make_shared<Knight>(*this);
}

std::vector<unsigned int> Knight::canMove(std::vector<std::shared_ptr<Piece>> &pieces, unsigned int pos) {
    std::vector<unsigned int> moves;

    int di[] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int dj[] = {-1, 1, -2, 2, -2, 2, -1, 1};

    int i = pos / 8;
    int j = pos % 8;

    for (int d = 0; d < 8; d++) {
        int i_next = i + di[d];
        int j_next = j + dj[d];
        if (i_next >= 0 && i_next < 8 && j_next >= 0 && j_next < 8) {
            unsigned int m = i_next * 8 + j_next;
            if (pieces[m]->getSide() != pieces[pos]->getSide())
                moves.push_back(m);
        }
    }
    return moves;
}


/// Class Bishop
Bishop::Bishop(const Side &side) : Piece(side) {
    code = (1 << 4) + (int) side;
    pSprite.setTexture(side == Side::WHITE ? Textures::whiteBishop : Textures::blackBishop);
    pSprite.setOrigin(pSprite.getTexture()->getSize().x / 2, pSprite.getTexture()->getSize().y / 2);
}

Bishop::~Bishop() {

}

void Bishop::isPressed() {
    std::cout << "Dumnezeu sa va binecuvanteze\n";
}

std::shared_ptr<Piece> Bishop::clone() const {
    return std::make_shared<Bishop>(*this);
}

std::vector<unsigned int> Bishop::canMove(std::vector<std::shared_ptr<Piece>> &pieces, unsigned int pos) {
    std::vector<unsigned int> moves;

    int i = pos / 8;
    int j = pos % 8;

    int di[] = {1, 1, -1, -1};
    int dj[] = {1, -1, 1, -1};

    for (int d = 0; d < 4; d++) {
        int i_next = i + di[d];
        int j_next = j + dj[d];
        while (i_next >= 0 && i_next < 8 && j_next >= 0 && j_next < 8) {
            unsigned int m = i_next * 8 + j_next;
            if (pieces[m]->getSide() == pieces[pos]->getSide())
                break;
            else if (pieces[m]->getSide() == Side::EMPTY)
                moves.push_back(m);
            else {
                moves.push_back(m);
                break;
            }

            i_next += di[d];
            j_next += dj[d];
        }

    }
    return moves;
}

/// Class Rook
Rook::Rook(const Side &side) : Piece(side) {
    code = (1 << 5) + (int) side;
    pSprite.setTexture(side == Side::WHITE ? Textures::whiteRook : Textures::blackRook);
    pSprite.setOrigin(pSprite.getTexture()->getSize().x / 2, pSprite.getTexture()->getSize().y / 2);
}

Rook::~Rook() {

}

void Rook::isPressed() {
    std::cout << "Vine tura cu viteza\n";
}

std::shared_ptr<Piece> Rook::clone() const {
    return std::make_shared<Rook>(*this);
}

std::vector<unsigned int> Rook::canMove(std::vector<std::shared_ptr<Piece>> &pieces, unsigned int pos) {
    std::vector<unsigned int> moves;
    int i = pos / 8;
    int j = pos % 8;

    int di[] = {0, 1, 0, -1};
    int dj[] = {1, 0, -1, 0};

    for (int d = 0; d < 4; d++) {
        int i_next = i + di[d];
        int j_next = j + dj[d];
        while (i_next >= 0 && i_next < 8 && j_next >= 0 && j_next < 8) {
            unsigned int m = i_next * 8 + j_next;
            if (pieces[m]->getSide() == pieces[pos]->getSide())
                break;
            else if (pieces[m]->getSide() == Side::EMPTY)
                moves.push_back(m);
            else {
                moves.push_back(m);
                break;
            }

            i_next += di[d];
            j_next += dj[d];
        }

    }
    return moves;
}

/// Class Queen
Queen::Queen(const Side &side) : Piece(side) {
    code = (1 << 6) + (int) side;
    pSprite.setTexture(side == Side::WHITE ? Textures::whiteQueen : Textures::blackQueen);
    pSprite.setOrigin(pSprite.getTexture()->getSize().x / 2, pSprite.getTexture()->getSize().y / 2);
}

Queen::~Queen() {

}

void Queen::isPressed() {
    std::cout << "Ma duc unde vreau\n";
}

std::shared_ptr<Piece> Queen::clone() const {
    return std::make_shared<Queen>(*this);
}

std::vector<unsigned int> Queen::canMove(std::vector<std::shared_ptr<Piece>> &pieces, unsigned int pos) {
    auto rook = std::make_shared<Rook>(Side::WHITE);
    auto bishop = std::make_shared<Bishop>(Side::WHITE);

    auto moves = bishop->canMove(pieces, pos);
    auto m1 = rook->canMove(pieces, pos);

    for (unsigned int &i: m1)
        moves.push_back(i);

    return moves;
}

/// Class King
King::King(const Side &side) : Piece(side) {
    code = (1 << 7) + (int) side;
    pSprite.setTexture(side == Side::WHITE ? Textures::whiteKing : Textures::blackKing);
    pSprite.setOrigin(pSprite.getTexture()->getSize().x / 2, pSprite.getTexture()->getSize().y / 2);
}

King::~King() {

}

void King::isPressed() {
    std::cout << "El Patron\n";
}

std::shared_ptr<Piece> King::clone() const {
    return std::make_shared<King>(*this);
}

std::vector<unsigned int> King::canMove(std::vector<std::shared_ptr<Piece>> &pieces, unsigned int pos) {
    std::vector<unsigned int> moves;

    int i = pos / 8;
    int j = pos % 8;

    int di[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dj[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int d = 0; d < 8; d++) {
        int i_next = i + di[d];
        int j_next = j + dj[d];

        int m = i_next * 8 + j_next;
        if (i_next >= 0 && i_next < 8 && j_next >= 0 && j_next < 8 &&
            pieces[pos]->getSide() != pieces[m]->getSide())
            moves.push_back(m);
    }
    return moves;
}

EmptySpace::EmptySpace() : Piece(Side::EMPTY) {}

EmptySpace::~EmptySpace() = default;

void EmptySpace::isPressed() {
    std::cout << "Ce sa muti?\n";
}

std::shared_ptr<Piece> EmptySpace::clone() const {
    return std::make_shared<EmptySpace>(*this);
}

std::vector<unsigned int> EmptySpace::canMove(std::vector<std::shared_ptr<Piece>> &pieces, unsigned int pos) {
    return {};
}
