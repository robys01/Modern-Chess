//
// Created by Robert on 11/18/2021.
//

#include "Board.h"

static const char *unicode_pieces[14] = {".", "♙", "♘", "♗", "♖", "♕", "♔", "♟", "♞", "♝", "♜", "♛", "♚"};
static const char pieces_[14] = {'.', 'p', 'n', 'b', 'r', 'q', 'k', 'P', 'N', 'B', 'R', 'Q', 'K'};

enum class piece{ empty = 0,
    blackPawn = 5, blackKnight = 9, blackBishop = 17, blackRook = 33, blackQueen = 65, blackKing = 129,
    whitePawn = 6, whiteKnight = 10, whiteBishop = 18, whiteRook = 34, whiteQueen = 66, whiteKing = 130
};

std::array<std::array<int, 8>, 8> classicBoard;


// Constructor
Board::Board() {
    boxes.resize(dim);
    for(int i = 0; i < dim; i++)
        boxes[i].resize(dim);
    readFEN();
    resetBoard();
    fillBoard();
    std::cout << "Board Created\n";
}
// Copy Constructor
Board::Board(const Board &copy) {
    for (int i = 0; i < dim; i++)
        for (int j = 0; j < dim; j++)
            this->boxes[i][j] = copy.boxes[i][j];
}
// Operator=
Board &Board::operator=(const Board &board) {
    for (int i = 0; i < dim; i++)
        for (int j = 0; j < dim; j++)
            this->boxes[i][j] = board.boxes[i][j];

    std::cout << "Operator=";
    return *this;
}
// Stream output Operator
std::ostream &operator<<(std::ostream &os, const Board &board) {
    for (int i = 0; i < 8; i++, os << '\n') {
        os << 8 - i << "  ";
        for (int j = 0; j < 8; j++)
            os << Board::decode(board.boxes[i][j]) << ' ';   // Unicode characters are incorrectly displayed in JetBrains terminal
    }
    os << "   ";
    for (int i = 0; i < 8; i++)
        os << (char) ('a' + i) << ' ';
    os << '\n';
    return os;
}

void Board::readFEN() {    // Incomplete
    std::ifstream in("board.txt");
    std::string s;
    getline(in, s);

    int row = 0, column = 0;
    for(int k = 0; s[k] != ' '; k++) {

        if(s[k] == '/') {
            row++;
            column = 0;
            continue;
        }

        if(s[k] > '0' && s[k] < '9') {
            int lenght = s[k] - '0';
            for(int j = column; j < column + lenght; j++)
                classicBoard[row][j] = static_cast<int>(piece::empty);
            column +=lenght;

        }

        switch(s[k]) {

            case 'p':
                classicBoard[row][column] = static_cast<int>(piece::blackPawn);
                column++;
                break;
            case 'b':
                classicBoard[row][column] = static_cast<int>(piece::blackBishop);
                column++;
                break;
            case 'n':
                classicBoard[row][column] = static_cast<int>(piece::blackKnight);
                column++;
                break;
            case 'r':
                classicBoard[row][column] = static_cast<int>(piece::blackRook);
                column++;
                break;
            case 'q':
                classicBoard[row][column] = static_cast<int>(piece::blackQueen);
                column++;
                break;
            case 'k':
                classicBoard[row][column] = static_cast<int>(piece::blackKing);
                column++;
                break;
            case 'P':
                classicBoard[row][column] = static_cast<int>(piece::whitePawn);
                column++;
                break;
            case 'B':
                classicBoard[row][column] = static_cast<int>(piece::whiteBishop);
                column++;
                break;
            case 'N':
                classicBoard[row][column] = static_cast<int>(piece::whiteKnight);
                column++;
                break;
            case 'R':
                classicBoard[row][column] = static_cast<int>(piece::whiteRook);
                column++;
                break;
            case 'Q':
                classicBoard[row][column] = static_cast<int>(piece::whiteQueen);
                column++;
                break;
            case 'K':
                classicBoard[row][column] = static_cast<int>(piece::whiteKing);
                column++;
                break;
        }


    }
}

void Board::resetBoard() {
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            boxes[i][j] = 0;
}

void Board::fillBoard() {
    for(int i = 0; i < dim; i++)
        for(int j = 0; j < dim; j++)
            this->boxes[i][j] = classicBoard[i][j];
}

const char Board::decode(int x) {
    int k;
    auto piesa = static_cast<piece>(x);

    switch (piesa) {
        default:
            k = 0;
            break;

        case piece::whitePawn:   // White Pawn
            k = 7;
            break;

        case piece::whiteKnight:   // White Knight
            k = 8;
            break;

        case piece::whiteBishop:   // White Bishop
            k = 9;
            break;

        case piece::whiteRook:   // White Rook
            k = 10;
            break;

        case piece::whiteQueen:   // White Queen
            k = 11;
            break;

        case piece::whiteKing:   // White King
            k = 12;
            break;

        case piece::blackPawn:    // Black Pawn
            k = 1;
            break;

        case piece::blackKnight:    // Black Knight
            k = 2;
            break;

        case piece::blackBishop:    // Black Bishop
            k = 3;
            break;

        case piece::blackRook:    // Black Rook
            k = 4;
            break;

        case piece::blackQueen:    // Black Queen
            k = 5;
            break;

        case piece::blackKing:    // Black King
            k = 6;
            break;
    }

    return pieces_[k];
}
