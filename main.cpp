#include <iostream>
#include <vector>

/*
 * Notations in binary code:
 *
*  Pawn    = 00000001
*  Knight  = 00000010
*  Bishop  = 00000100
*  Rook    = 00001000
*  Queen   = 00010000
*  King    = 00100000
*
*  Black   = 01000000
*  White   = 10000000
*/

static const char *unicode_pieces[14] = {".", "♙", "♘", "♗", "♖", "♕", "♔", "♟", "♞", "♝", "♜", "♛", "♚"};
                                    //    0    1     2     3    4     5     6    7     8    9    10    11    12

static const int classicBoard[8][8] = {
        72, 66, 68, 80, 96, 68, 66, 72,
        65, 65, 65, 65, 65, 65, 65, 65,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        129, 129, 129, 129, 129, 129, 129, 129,
        136, 130, 132, 144, 160, 132, 130, 136};

class Board {
    int dim = 8;
    std::vector<std::vector<int>> boxes;    // std::vector<std::vector<int>> boxes(dim, std::vector<int>(dim)) doesn't work in a class ???
public:
    // Constructor
    Board() {

        boxes.resize(dim);
        for(int i = 0; i < dim; i++)
            boxes[i].resize(dim);
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
//        for(int i = 0; i < dim; i++)
//            boxes[i].erase();
//        boxes.erase();
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
        for (int i = 0; i < 8; i++, os << '\n') {
            os << 8 - i << "  ";
            for (int j = 0; j < 8; j++)
                os << decode(board.boxes[i][j]) << ' ';   // Unicode characters are incorrectly displayed in JetBrains terminal
        }
        os << "   ";
        for (int i = 0; i < 8; i++)
            os << (char) ('a' + i) << ' ';
        os << '\n';
        return os;
    }


    void resetBoard() {
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                boxes[i][j] = 0;
    }

    void fillBoard() {
        for(int i = 0; i < dim; i++)
            for(int j = 0; j < dim; j++)
                this->boxes[i][j] = classicBoard[i][j];
    }

    static const char *decode(int x) {
        int k;
        switch (x) {
            default:
                k = 0;
                break;

            case 129:   // White Pawn
                k = 7;
                break;

            case 130:   // White Knight
                k = 8;
                break;

            case 132:   // White Bishop
                k = 9;
                break;

            case 136:   // White Rook
                k = 10;
                break;

            case 144:   // White Queen
                k = 11;
                break;

            case 160:   // White King
                k = 12;
                break;

            case 65:    // Black Pawn
                k = 1;
                break;

            case 66:    // Black Knight
                k = 2;
                break;

            case 68:    // Black Bishop
                k = 3;
                break;

            case 72:    // Black Rook
                k = 4;
                break;

            case 80:    // Black Queen
                k = 5;
                break;

            case 96:    // Black King
                k = 6;
                break;
        }

        return unicode_pieces[k];
    }
};

class Player {
    std::string name;
    bool whiteSide;
    int elo = 800;
    // bool isComputer

public:

    Player() {
        whiteSide = true;
    };

    Player(const std::string &name, bool whiteSide, int elo) : name(name), whiteSide(whiteSide), elo(elo){}

    virtual ~Player() { }

    friend std::ostream &operator<<(std::ostream &os, const Player &player) {
        os << "Name: " << player.name << "\nColor: " << (player.whiteSide ? "White\n" : "Black\n")
           << "Rating: " << player.elo <<'\n';
        return os;
    }

    int getElo() const {
        return elo;
    }

    void setElo(int elo) {
        this->elo = elo;
    }

    std::string getName() {
        return this->name;
    }

    void setName(std::string &name) {
        this->name = name;
    }

    bool isWhiteSide() const {
        return whiteSide;
    }

    void setWhiteSide(bool whiteSide) {
        Player::whiteSide = whiteSide;
    }

};

class Game {

    Board board;
    Player playerWhite, playerBlack;
    std::vector<std::string> moveHistory;
    bool gameStatus;    // gameStatus == true ->  game is currently on
                        // gameStatus == false -> game ended
public:
    Game() {
        playerWhite = Player("Player1", true, 1200);
        playerBlack = Player("Player2", false, 800);
        this->gameStatus = true;
//        std::cout << "In Game Constructor\n";
    }
    virtual ~Game() = default;

    friend std::ostream &operator<<(std::ostream &os, Game &game) {
        os  << "\tBlack: " << game.playerBlack.getName() << " (" << game.playerBlack.getElo() << ")\n";
//        showBoard();  Error
        os  << "\tWhite: " << game.playerWhite.getName() << " (" << game.playerWhite.getElo() << ")\n";
        return os;
    }
    void showBoard() {
        std::cout << this->board;
    }

};

int main() {

    Game sah;

    std::cout << sah;

    std::cout << "Modern Chess!" << '\n';
    return 0;
}
