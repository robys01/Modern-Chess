//
// Created by Robert on 12/12/2021.
//

#ifndef MODERN_CHESS_PIECE_H
#define MODERN_CHESS_PIECE_H

#include "Textures.h"

enum class PieceType {
    Empty, Pawn, Knight, Bishop, Rook, Queen, King
};
enum class Side {
    EMPTY, BLACK, WHITE
};



class Piece {
protected:
    int code;
    PieceType pieceType;
    Side side;

    sf::Texture pTexture;
    sf::Sprite pSprite;

//    float squareSize = 64;
    float pieceSize = 60;

public:
    Piece();
    Piece(PieceType pieceType, Side side);
    Piece(const Piece &piece);
    ~Piece();

    int loadTextures();
    void drawPiece(sf::RenderWindow &window);
    void setPosition(float x, float y);
    void setScale(float x, float y);
    int getCode() const;

    Piece operator=(const Piece &piece);
    friend std::ostream &operator<<(std::ostream &os, const Piece &piece);

};


#endif //MODERN_CHESS_PIECE_H
