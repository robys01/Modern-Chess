//
// Created by Robert on 12/12/2021.
//

#ifndef MODERN_CHESS_PIECE_H
#define MODERN_CHESS_PIECE_H

#include <SFML/Graphics.hpp>

enum class PieceType {
    Empty, Pawn, Knight, Bishop, Rook, Queen, King
};
enum class Side {
    EMPTY, BLACK, WHITE
};



class Piece {
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

private:
    sf::Texture whitePawnTexture;
    sf::Texture whiteKnightTexture;
    sf::Texture whiteBishopTexture;
    sf::Texture whiteRookTexture;
    sf::Texture whiteQueenTexture;
    sf::Texture whiteKingTexture;

    sf::Texture blackPawnTexture;
    sf::Texture blackKnightTexture;
    sf::Texture blackBishopTexture;
    sf::Texture blackRookTexture;
    sf::Texture blackQueenTexture;
    sf::Texture blackKingTexture;
};


#endif //MODERN_CHESS_PIECE_H
