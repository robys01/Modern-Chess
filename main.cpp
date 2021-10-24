#include <iostream>
#include <vector>

const int dim = 8;

class Piece {
    enum pieceType {
        Pawn, Knight, Bishop, Rook, Queen, King
    };
    int pieceID;
    /*
     *  Pawn    = 00000001
     *  Bishop  = 00000010
     *  Knight  = 00000011
     *  Rook    = 00000100
     *  Queen   = 00001000
     *  Rook    = 00010000
     *
     *  Black   = 01000000
     *  White   = 10000000
     */

public:



};

class Board {
    static const int dim = 8;
    int boxes[dim][dim];    // std::vector<std::vector<int>> mat(dim, std::vector<int>(dim)) doesn't work in a class ???
    std::vector<Piece> pieces;
//    Square[][] boxes;
public:
    // Constructor
    Board() {
        resetBoard();
        fillBoard();
        std::cout << "Board Created\n";
    }

    // Copy Constructor
    Board(const Board &copie) {
        for (int i = 0; i < dim; i++)
            for (int j = 0; j < dim; j++)
                this->boxes[i][j] = copie.boxes[i][j];
    }

    virtual ~Board() {
        std::cout << "Board Removed\n";
    }

    // Operator=
    Board &operator=(const Board &board) {
        for (int i = 0; i < dim; i++)
            for (int j = 0; j < dim; j++)
                this->boxes[i][j] = board.boxes[i][j];

        std::cout << "Operator=";
        return *this;
    }

    // Stream output Operator
    friend std::ostream &operator<<(std::ostream &os, const Board &board) {
        os << "The board is:\n";
        for (int i = 0; i < 8; i++, os << '\n')
            for (int j = 0; j < 8; j++)
                os << board.boxes[i][j] << ' ';
        return os;
    }

    void resetBoard() {
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                boxes[i][j] = 0;
    }

    void fillBoard() {

    }

};

class Game {

    Board board;
    bool game_status;

public:
    Game() {
//        board = new Board();
        std::cout << "In Game Constructor";
    }

    virtual ~Game() {
        std::cout << "In Game Destructor";
    }
};

//using namespace std;
int main() {

    Board masa_joc;
    std::cout << masa_joc;


    std::cout << "Modern Chess!" << '\n';
    return 0;
}
