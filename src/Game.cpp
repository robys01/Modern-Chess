//
// Created by Robert on 11/18/2021.
//

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "../headers/Game.h"
#include "../headers/ChessExceptions.h"

Game::Game() :
        window(sf::VideoMode(WIDTH, HEIGHT), "Modern Chess", sf::Style::Close),
        chessBoard(HEIGHT) {

    try {
        readFEN("board.txt");
        setPieces();
    } catch (error_chess &error) {
        std::cerr << error.what();
        std::exit(1);
    }
    for (int i = 0; i < 64; i++)
        std::cout << (i % 8) + (i / 8) * 8 << ((i + 1) % 8 ? " " : "\n");

    std::cout << '\n';
    std::cout << "Nr moves: " << nrMoves << "\nWhite turn? " << whiteTurn << '\n';
}

Game::~Game() {
    std::cout << "Chess ended successfully\n";
};

void Game::run() {
    std::cout << chessBoard;
    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                window.close();
            if (e.type == sf::Event::KeyPressed) {
                if (e.key.code == sf::Keyboard::Right) {
                    chessBoard.changeTheme();
                } else if (e.key.code == sf::Keyboard::Left)
                    chessBoard.changeTheme("previous");
            }
            if (e.type == sf::Event::KeyPressed) {
                if (e.key.code == sf::Keyboard::R) {
                    pieces.clear();
                    readFEN("board.txt");
                    setPieces();
                }
            }

            ////// Move mechanics //////
            if (e.type == e.MouseButtonPressed) {
                if (e.mouseButton.button == sf::Mouse::Left) {
                    if ((0 <= e.mouseButton.x) && (e.mouseButton.x <= HEIGHT) &&
                        (0 <= e.mouseButton.y) && (e.mouseButton.y <= HEIGHT)) {

                        unsigned int buttonPos((e.mouseButton.x / squareSize) +
                                               ((e.mouseButton.y / squareSize) * (8 * (HEIGHT / window.getSize().y))));
                        pieces[buttonPos]->canMove();
                        std::cout << buttonPos << ' ';

                        if (isPiece(buttonPos))
                            dragMove(buttonPos);
                    }
                }
            }////////////////////////////////
        }

        drawGame();
        window.display();
    }
}

void Game::drawGame() {
    window.clear(sf::Color::Black);
    chessBoard.drawBoard(window);
    for (auto &it: possibleMoves)
        window.draw(it);
    for (auto &it: pieces)
        it->drawPiece(window);
}

std::ostream &operator<<(std::ostream &os, const Game &game) {
    for (unsigned int i = 0; i < game.pieces.size(); i++)
        std::cout << (*game.pieces[i]) << ((i + 1) % 8 ? " " : "\n");

    return os;
}

void Game::readFEN(const std::string &args) {
    std::ifstream fin(args);
    if (!fin.is_open())
        throw error_open(args);

    std::string s;
    fin >> s;

    /// Board representation
    int i, nrElements = 0, nrKings = 0;
    for (i = 0; i < (int) s.size(); i++) {
        if (s[i] == 'K' || s[i] == 'k')
            nrKings++;
        if (nrKings > 2)
            throw error_fen();

        if (s[i] >= '1' && s[i] <= '9') {
            nrElements += (int) s[i] - '0';
            for (int j = (int) (s[i] - '0'); j > 0; j--)
                pieces.push_back(std::make_shared<EmptySpace>());
        }

        auto side = std::isupper(s[i]) ? Side::WHITE : Side::BLACK; // <cctype>
        switch (std::toupper(s[i])) {
            case 'P':
                pieces.push_back(std::make_shared<Pawn>(side));
                nrElements++;
                break;
            case 'N':
                pieces.push_back(std::make_shared<Knight>(side));
                nrElements++;
                break;
            case 'B':
                pieces.push_back(std::make_shared<Bishop>(side));
                nrElements++;
                break;
            case 'R':
                pieces.push_back(std::make_shared<Rook>(side));
                nrElements++;
                break;
            case 'Q':
                pieces.push_back(std::make_shared<Queen>(side));
                nrElements++;
                break;
            case 'K':
                pieces.push_back(std::make_shared<King>(side));
                nrElements++;
                break;
        }
    }
    if (nrKings != 2)
        throw error_fen();

    if (nrElements != 64)
        throw error_fen();

    /// Player's turn
    fin >> s;
    if (s == "w")
        whiteTurn = true;
    else if (s == "b")
        whiteTurn = false;
    else
        throw error_fen();

    /// Castling privileges
    fin >> s;
    for (auto &it: s) {
        switch (it) {
            case 'K':
                whiteCastleK = true;
                break;
            case 'Q':
                whiteCastleQ = true;
                break;
            case 'k':
                blackCastleK = true;
                break;
            case 'q':
                blackCastleQ = true;
                break;
            default:
                throw error_fen();
        }
    }
    if (pieces[3]->getCode() != 129)    /// If Black King isn't in the right spot, he is not allowed to castle
        blackCastleK = blackCastleQ = false;
    if (pieces[60]->getCode() != 130)   /// Same for the White King
        whiteCastleK = whiteCastleQ = false;


    /// En Passant possible move
    fin >> s;
    if (s == "-")
        enPassant = 0;
    else if (s[0] > 'h' || s[0] < 'a' || s[1] < '1' || s[1] > '8')
        throw error_fen();
    else
        enPassant = (int) ('8' - s[1]) * 8 + (int) (s[0] - 'a');

    /// Number of moves and number of moves without capture (for the 50 move rule)
    fin >> s;
    nrMovesWithoutCapture = std::stoi(s);
    fin >> s;
    nrMoves = std::stoi(s);

    fin.close();
}

void Game::setPieces() {
    for (unsigned int i = 0; i < pieces.size(); i++) {

        pieces[i]->setPosition(squareWidth * (i % 8) + squareWidth / 2.0f,
                               (squareWidth * (i / 8)) + squareWidth / 2.0f);
        pieces[i]->setScale(1 * scale, 1 * scale);
    }
}

bool Game::isPiece(unsigned int i) {
    if (pieces[i]->getCode() == 0) {
        resetPossibleMoves();
        return false;
    }
    if (nrMoves % 2 != whiteTurn)    /// Wrong Piece Selected
        return false;
    return true;
}

void Game::drawPossibleMove(unsigned int val) {
    float x = (val % 8) * squareSize;
    float y = (val / 8) * squareSize;

    possibleMoves[val].setPosition(x, y);
    possibleMoves[val].setSize(sf::Vector2f(squareSize, squareSize));
    possibleMoves[val].setFillColor(sf::Color(0, 255, 255, 100));
}

void Game::resetPossibleMoves() {
    for (auto &it: possibleMoves)
        it.setFillColor(sf::Color::Transparent);
}


void Game::dragMove(unsigned int buttonPos) {
///// You won't be able to drag a black piece on white's turn, and vice versa
//    if (nrMoves % 2 == pieces[buttonPos]->getCode() % 2)
//        return;

    resetPossibleMoves();

    std::vector<unsigned int> moves;
    if (pieces[buttonPos]->getCode() == 5 + (int) whiteTurn) {
        moves = pawnMoves(buttonPos);
        for (auto m: moves) {
            std::cout << (char) ((m % 8) + 'a') << 8 - m / 8 << ' ';
            drawPossibleMove(m);
        }
        std::cout << '\n';

    } else if (pieces[buttonPos]->getCode() == 9 + (int) whiteTurn) {
        moves = knightMoves(buttonPos);
        for (auto m: moves) {
            std::cout << (char) ((m % 8) + 'a') << 8 - m / 8 << ' ';
            drawPossibleMove(m);
        }
        std::cout << '\n';

    } else if (pieces[buttonPos]->getCode() == 17 + (int) whiteTurn) {
        moves = bishopMoves(buttonPos);

        for (auto m: moves) {
            std::cout << (char) ((m % 8) + 'a') << 8 - m / 8 << ' ';
            drawPossibleMove(m);
        }
        std::cout << '\n';

    } else if (pieces[buttonPos]->getCode() == 33 + (int) whiteTurn) {
        moves = rookMoves(buttonPos);
        for (auto m: moves) {
            std::cout << (char) ((m % 8) + 'a') << 8 - m / 8 << ' ';
            drawPossibleMove(m);
        }
        std::cout << '\n';

    } else if (pieces[buttonPos]->getCode() == 65 + (int) whiteTurn) {
        moves = queenMoves(buttonPos);
        for (auto m: moves) {
            std::cout << (char) ((m % 8) + 'a') << 8 - m / 8 << ' ';
            drawPossibleMove(m);
        }
        std::cout << '\n';

    } else if (pieces[buttonPos]->getCode() == 129 + (int) whiteTurn) {
        moves = kingMoves(buttonPos);
        for (auto m: moves) {
            std::cout << (char) ((m % 8) + 'a') << 8 - m / 8 << ' ';
            drawPossibleMove(m);
        }
        std::cout << '\n';
    }


    ////// Drag mechanics //////
    float x = pieces[buttonPos]->getPosition().x;
    float y = pieces[buttonPos]->getPosition().y;

    unsigned int buttonRelease;
    while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i pos = sf::Mouse::getPosition(window);

        /// Keep the piece on table when cursor is out of bounds
        if (pos.x >= HEIGHT) pos.x = HEIGHT;
        if (pos.y >= HEIGHT) pos.y = HEIGHT;
        if (pos.x <= 0) pos.x = 0;
        if (pos.y <= 0) pos.y = 0;

        pieces[buttonPos]->setPosition((float) pos.x, (float) pos.y);
        buttonRelease = (pos.x / squareSize) +
                        ((pos.y / squareSize) * (8 * (HEIGHT / window.getSize().y)));
        drawGame();
        pieces[buttonPos]->drawPiece(window);
        window.display();
    }
    std::cout << buttonRelease << '\n';
    /////////////////////////////////////

    for (auto m: moves) {
        if (buttonRelease == m) {
            make_move(buttonPos, buttonRelease);
            resetPossibleMoves();
            return;
        }
    }

    /// Not a valid move
    pieces[buttonPos]->setPosition(x, y);
}

void Game::make_move(unsigned int start, unsigned int destination) {
    pieces[start]->setPosition(squareWidth * (destination % 8) + squareWidth / 2.0f,
                               (squareWidth * (destination / 8)) + squareWidth / 2.0f);
    pieces[destination] = pieces[start]->clone();
    pieces[start] = std::make_shared<EmptySpace>();  /// Becomes empty space

    nrMoves++;
    whiteTurn = !whiteTurn;

    std::cout << '\n';
    std::cout << "Nr moves: " << nrMoves << '\n' << (whiteTurn ? "White Turn" : "Black Turn") << '\n';
}

std::vector<unsigned int> Game::pawnMoves(unsigned i) {
    std::vector<unsigned int> moves;

    if (pieces[i]->getCode() & (int) Side::BLACK) {
        // Promote
        if (i > 55) return moves;
        // Simple move
        if (pieces[i + 8]->getCode() == 0)
            moves.push_back(i + 8);

        // Possible 2 squares move
        if (i >= 8 && i <= 15)
            if (pieces[i + 16]->getCode() == 0)
                moves.push_back(i + 16);

        // Left capture black pawn
        if (i % 8 != 0 && pieces[i + 7]->getCode() & (int) Side::WHITE)
            moves.push_back(i + 7);
        // Right capture black pawn
        if ((i + 1) % 8 != 0 && pieces[i + 9]->getCode() & (int) Side::WHITE)
            moves.push_back(i + 9);

    } else if (pieces[i]->getCode() & (int) Side::WHITE) {
        // Promote
        if (i < 8) return moves;

        // Simple move
        if (pieces[i - 8]->getCode() == 0)
            moves.push_back(i - 8);

        // Possible 2 squares move
        if (i >= 47 && i <= 56)
            if (pieces[i - 16]->getCode() == 0)
                moves.push_back(i - 16);

        // Left capture white pawn
        if (i % 8 != 0 && pieces[i - 9]->getCode() & (int) Side::BLACK)
            moves.push_back(i - 9);
        // Right capture black pawn
        if ((i + 1) % 8 != 0 && pieces[i - 7]->getCode() & (int) Side::BLACK)
            moves.push_back(i - 7);

    }
    return moves;

}

std::vector<unsigned int> Game::knightMoves(unsigned int pos) {
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

std::vector<unsigned int> Game::bishopMoves(unsigned int pos) {
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

std::vector<unsigned int> Game::rookMoves(unsigned int pos) {
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

std::vector<unsigned int> Game::queenMoves(unsigned int pos) {
    auto moves = bishopMoves(pos);
    auto m1 = rookMoves(pos);

    for (unsigned int &i: m1)
        moves.push_back(i);

    return moves;
}

std::vector<unsigned int> Game::kingMoves(unsigned int pos) {
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

    /// Castling mechanics
    if (pieces[pos]->getSide() == Side::WHITE) {

    } else {

    }

    return moves;
}

bool inCheck(unsigned int pos) {
    // TODO
//    int i = pos / 8;
//    int j = pos % 8;
//
//    int di[] = {};
//    int dj[] = {};
    return false;
}
