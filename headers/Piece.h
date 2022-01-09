//
// Created by Robert on 12/12/2021.
//

#ifndef MODERN_CHESS_PIECE_H
#define MODERN_CHESS_PIECE_H

#include "Textures.h"
#include <memory>

enum class Side {
    EMPTY = 0, BLACK = 1, WHITE = 2
};

/// Class Piece is abstract
class Piece {
protected:
    int code;
    Side side;

    sf::Sprite pSprite;

public:
    explicit Piece(const Side& side);
    virtual ~Piece();
    virtual void isPressed() = 0;

    virtual std::vector<unsigned int> canMove(std::vector<std::shared_ptr<Piece>> &pieces, unsigned int pos) = 0;

    void drawPiece(sf::RenderWindow &window);
    void setPosition(float x, float y);
    sf::Vector2f getPosition();
    void setScale(float x, float y);

    int getCode() const;
    Side getSide() const;

    friend std::ostream& operator<<(std::ostream& os, const Piece& piece);

    virtual std::shared_ptr<Piece> clone() const = 0;
};


class Pawn : public Piece {

public:
    explicit Pawn(const Side& side);
    void isPressed() override;

    std::vector<unsigned int> canMove(std::vector<std::shared_ptr<Piece>> &pieces, unsigned int pos) override;

    std::shared_ptr<Piece> clone() const override;
};


class Knight : public Piece {
public:
    explicit Knight(const Side& side);
    void isPressed() override;

    std::vector<unsigned int> canMove(std::vector<std::shared_ptr<Piece>> &pieces, unsigned int pos) override;

    std::shared_ptr<Piece> clone() const override;
};


class Bishop : public Piece {
public:
    explicit Bishop( const Side& side);
    void isPressed() override;

    std::vector<unsigned int> canMove(std::vector<std::shared_ptr<Piece>> &pieces, unsigned int pos) override;

    std::shared_ptr<Piece> clone() const override;
};


class Rook : public Piece {
public:
    explicit Rook(const Side& side);
    void isPressed() override;

    std::vector<unsigned int> canMove(std::vector<std::shared_ptr<Piece>> &pieces, unsigned int pos) override;

    std::shared_ptr<Piece> clone() const override;
};


class Queen : public Piece {
public:
    explicit Queen(const Side& side);
    void isPressed() override;

    std::vector<unsigned int> canMove(std::vector<std::shared_ptr<Piece>> &pieces, unsigned int pos) override;

    std::shared_ptr<Piece> clone() const override;
};


class King : public Piece {
public:
    explicit King(const Side& side);
    void isPressed() override;

    std::vector<unsigned int> canMove(std::vector<std::shared_ptr<Piece>> &pieces, unsigned int pos) override;

    std::shared_ptr<Piece> clone() const override;
};

/// Used for the empty spaces on the chess board
class EmptySpace : public Piece {

public:
    EmptySpace();
    void isPressed() override;

    std::vector<unsigned int> canMove(std::vector<std::shared_ptr<Piece>> &pieces, unsigned int pos) override;

    std::shared_ptr<Piece> clone() const override;
};


#endif //MODERN_CHESS_PIECE_H
