//
// Created by Robert on 11/18/2021.
//

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "../headers/Game.h"
#include "../headers/ChessExceptions.h"

Game *Game::chess = nullptr;

Game::Game() :
        window(sf::VideoMode(WIDTH, HEIGHT), "Modern Chess", sf::Style::Close),
        chessBoard(HEIGHT) {
    window.setFramerateLimit(144);
    try {
        readFEN("board.txt");
        setPieces();
    } catch (error_chess &error) {
        std::cerr << error.what();
        std::exit(1);
    }
    for (int i = 0; i < 64; i++)
        std::cout << (i % 8) + (i / 8) * 8 << ((i + 1) % 8 ? " " : "\n");
    for (const auto &it: pieces)
        if (it->getCode())
            it->getSide() == Side::WHITE ? whiteStats.addPiece(it->getCode()) : blackStats.addPiece(it->getCode());

    showInfo();
}

Game::~Game() {
    std::cout << "Chess ended successfully!\n";
}

Game *Game::get_app() {
    if (chess == nullptr) chess = new Game;
    return chess;
}

void Game::run() {
    std::cout << *chess;
    while (window.isOpen()) {
        sf::Event e{};
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                window.close();
            if (e.type == sf::Event::Resized) {
                std::cout << "Width: " << window.getSize().x << '\n';
                std::cout << "Height: " << window.getSize().y << '\n';
            }
            if (e.type == sf::Event::KeyPressed) {
                if (e.key.code == sf::Keyboard::Right)  /// Change board theme
                    chessBoard.changeTheme();
                else if (e.key.code == sf::Keyboard::Left)
                    chessBoard.changeTheme("previous");
                else if (e.key.code == sf::Keyboard::R) {    /// Reset
                    pieces.clear();
                    resetPossibleMoves();
                    readFEN("board.txt");
                    setPieces();
                    std::cout << "Board has been reset\n";
                }
            }
            ////// Move mechanics //////
            if (e.type == e.MouseButtonPressed) {
                if (e.mouseButton.button == sf::Mouse::Left) {
                    if ((0 <= e.mouseButton.x) && (e.mouseButton.x <= HEIGHT) &&
                        (0 <= e.mouseButton.y) && (e.mouseButton.y <= HEIGHT)) {

                        unsigned int buttonPos((e.mouseButton.x / squareSize) +
                                               ((e.mouseButton.y / squareSize) * (8 * (HEIGHT / window.getSize().y))));
                        pieces[buttonPos]->isPressed();
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
    delete chess;
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

void Game::printPieces() {
    for (unsigned int i = 0; i < pieces.size(); i++)
        std::cout << (*pieces[i]) << ((i + 1) % 8 ? " " : "\n");
}

void Game::showInfo() {
    std::cout << '\n';
    std::cout << "Nr moves: " << nrMoves << "\nWhite turn? " << (whiteTurn ? "Yes" : "No") << '\n';
    std::cout << whiteStats << blackStats;
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
        /// Sets the position of the Kings
        if (s[i] == 'k') blackKingPos = nrElements;
        else if (s[i] == 'K') whiteKingPos = nrElements;

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
    if (s[0] == '-')
        whiteCastleK = whiteCastleQ = false;
    else if (s[1] == '-')
        blackCastleK = blackCastleQ = false;
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
            case '-':
                break;
            default:
                throw error_fen();
        }
    }
    if (pieces[4]->getCode() != 129)    /// If Black King isn't in the right spot, he is not allowed to castle
        blackCastleK = blackCastleQ = false;
    if (pieces[60]->getCode() != 130)   /// Same for the White King
        whiteCastleK = whiteCastleQ = false;


    /// En Passant possible move
    fin >> s;
    if (s == "-")
        enPassant = -1;
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
    for (unsigned int i = 0; i < pieces.size(); i++)
        setPiece(i);
}

void Game::setPiece(unsigned int pos) {
    pieces[pos]->setPosition(squareWidth * (pos % 8) + squareWidth / 2.0f,
                             (squareWidth * (pos / 8)) + squareWidth / 2.0f);
    pieces[pos]->setScale(1 * scale, 1 * scale);
}

bool Game::isPiece(unsigned int i) {
    if (pieces[i]->getCode() == 0) {
        resetPossibleMoves();
        return false;
    }
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

void Game::addEnPassantMoves(unsigned int pos, std::vector<unsigned int> &moves) {
    if (pieces[pos]->getCode() == 5) {         /// Black Pawn

        if ((pos % 8) && pieces[pos - 1]->getSide() == Side::WHITE && enPassant == (int) pos + 7)
            moves.push_back(pos + 7);

        if (((pos + 1) % 8) && pieces[pos + 1]->getSide() == Side::WHITE && enPassant == (int) pos + 9)
            moves.push_back(pos + 9);

    } else if (pieces[pos]->getCode() == 6) {   /// White Pawn

        if ((pos % 8) && pieces[pos - 1]->getSide() == Side::BLACK && enPassant == (int) pos - 9)
            moves.push_back(pos - 9);

        if (((pos + 1) % 8) && pieces[pos + 1]->getSide() == Side::BLACK && enPassant == (int) pos - 7)
            moves.push_back(pos - 7);
    }
}

std::vector<unsigned int> Game::legalMoves(unsigned int buttonPos) {
    /**
     * This functions generates all legal moves of a piece selected.
     */
    std::vector<unsigned int> moves;

    /// Right turn condition
    if (pieces[buttonPos]->getSide() == (whiteTurn ? Side::WHITE : Side::BLACK))
        moves = pieces[buttonPos]->canMove(pieces, buttonPos);

    /// Add En Passant
    if (pieces[buttonPos]->getCode() == 5 + (int) whiteTurn)
        addEnPassantMoves(buttonPos, moves);

    ///// Can't move pinned Pieces /////    ... and can't move until is not Check anymore
    for (unsigned int it = 0; it < moves.size();) {
        auto aux = pieces[moves[it]]->clone();
        pieces[moves[it]] = pieces[buttonPos]->clone();
        pieces[buttonPos] = std::make_shared<EmptySpace>();

        if (pieces[moves[it]]->getCode() ==
            129 + (int) whiteTurn)    /// If a King is selected, updates the position of it
            whiteTurn ? whiteKingPos = moves[it] : blackKingPos = moves[it];

        if (isCheck(pieces[moves[it]]->getSide())) {
            if (pieces[moves[it]]->getCode() == 129 + (int) whiteTurn)    /// Restores the position of the King
                whiteTurn ? whiteKingPos = buttonPos : blackKingPos = buttonPos;

            pieces[buttonPos] = pieces[moves[it]]->clone();
            pieces[moves[it]] = aux->clone();
            moves.erase(moves.begin() + it);
            continue;
        }
        if (pieces[moves[it]]->getCode() == 129 + (int) whiteTurn)  /// Restores the position of the King
            whiteTurn ? whiteKingPos = buttonPos : blackKingPos = buttonPos;

        pieces[buttonPos] = pieces[moves[it]]->clone();
        pieces[moves[it]] = aux->clone();
        it++;
    }
    /////////////////////////////////////////
    return moves;
}

void Game::dragMove(unsigned int buttonPos) {

    resetPossibleMoves();

    auto moves = legalMoves(buttonPos);
    for (auto &m: moves) {
        std::cout << (char) ((m % 8) + 'a') << 8 - m / 8 << ' ';
        drawPossibleMove(m);
    }
    std::cout << '\n';

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

    if (std::any_of(moves.begin(), moves.end(), [buttonRelease](const auto a) { return a == buttonRelease; })) {
        make_move(buttonPos, buttonRelease);
        resetPossibleMoves();
        printPieces();
        whiteChecked = blackChecked = false;
        if (isCheck(Side::WHITE)) {
            std::cout << "White King check!\n";
            whiteChecked = true;
        } else if (isCheck(Side::BLACK)) {
            std::cout << "Black King check!\n";
            blackChecked = true;
        }
        /// DRAW CONDITIONS
        if ((isCheckmate(Side::WHITE) && whiteTurn && !whiteChecked) ||
            (isCheckmate(Side::BLACK) && !whiteTurn && !blackChecked))
            std::cout << "Stalemate!";
        else if (nrMovesWithoutCapture >= 50)
            std::cout << "Draw by the 50 move rule!";
        // Draw by repetition

        /// CHECKMATE
        if (whiteChecked && isCheckmate(Side::WHITE))
            std::cout << "Checkmate! Black won!";
        else if (blackChecked && isCheckmate(Side::BLACK))
            std::cout << "Checkmate! White won!";

        return;
    }

    /// Not a valid move
    pieces[buttonPos]->setPosition(x, y);
}

void Game::make_move(unsigned int start, unsigned int destination) {

    if (pieces[destination]->getSide() != Side::EMPTY) { /// Piece Captured
        nrMovesWithoutCapture = -1;

        (whiteTurn ? blackStats.addPiece(pieces[destination]->getCode(), true)
                   : whiteStats.addPiece(pieces[destination]->getCode(), true));
    } else if (enPassant == (int) destination &&
               pieces[start]->getCode() == 5 + (int) whiteTurn) {    /// En Passant Capture
        nrMovesWithoutCapture = -1;
        pieces[destination + (whiteTurn ? 8 : -8)] = std::make_shared<EmptySpace>();

        (whiteTurn ? blackStats.addPiece(5, true)
                   : whiteStats.addPiece(6, true));

    }

    pieces[start]->setPosition(squareWidth * (destination % 8) + squareWidth / 2.0f,
                               (squareWidth * (destination / 8)) + squareWidth / 2.0f);
    pieces[destination] = pieces[start]->clone();
    pieces[start] = std::make_shared<EmptySpace>();  /// Becomes empty space

    enPassant = -1;
    if (pieces[destination]->getCode() == 5 + (int) whiteTurn &&    /// Set En Passant
        (int) (start - destination) == 16 * (whiteTurn ? 1 : -1)) {
        enPassant = (int) destination + (whiteTurn ? 8 : -8);
    } else if (pieces[destination]->getCode() == 5 && destination > 55) {   /// Black Pawn Promote
        pieces[destination] = std::make_shared<Queen>(Side::BLACK);
        setPiece(destination);
        whiteStats.addPiece(5, true);
        whiteStats.addPiece(65);
    } else if (pieces[destination]->getCode() == 6 && destination < 8) {  /// White Pawn Promote
        pieces[destination] = std::make_shared<Queen>(Side::WHITE);
        setPiece(destination);
        whiteStats.addPiece(6, true);
        whiteStats.addPiece(66);
    } else if (start == whiteKingPos || start == blackKingPos) /// Updates the position of the Kings
        start == whiteKingPos ? whiteKingPos = destination : blackKingPos = destination;

    nrMoves++;
    nrMovesWithoutCapture++;
    whiteTurn = !whiteTurn;
    showInfo();
}


bool Game::isCheck(Side kingSide, unsigned int position) {
    /**
     * This function returns true if the King of the 'kingSide' color is in check.
     * It generates all possible moves from the King and verifies if there is any other piece from the opposite color.
     * This function is needed because more pieces can give a Check at the same time (discovery checks)
     */

    const unsigned int kingPos = (position != 64 ? position
                                                 : (kingSide == Side::WHITE ? whiteKingPos : blackKingPos));
    std::vector<unsigned int> moves;

    /// Pawn Checks
    if (kingSide == Side::WHITE && kingPos > 16) {
        if ((pieces[kingPos - 7]->getCode() == 5 && (kingPos + 1) % 8 != 0) ||
            (pieces[kingPos - 9]->getCode() == 5 && kingPos % 8 != 0)) {
            return true;
        }

    } else if (kingSide == Side::BLACK && kingPos < 48) {
        if ((pieces[kingPos + 7]->getCode() == 6 && kingPos % 8 != 0) ||
            (pieces[kingPos + 9]->getCode() == 6 && (kingPos + 1) % 8 != 0)) {
            return true;
        }
    }

    static std::array<std::shared_ptr<Piece>, 5> staticPieces = {
            std::make_shared<Knight>(Side::WHITE),
            std::make_shared<Bishop>(Side::WHITE),
            std::make_shared<Rook>(Side::WHITE),
            std::make_shared<Queen>(Side::WHITE),
            std::make_shared<King>(Side::WHITE)};

    for (auto &piece: staticPieces) {
        moves = piece->canMove(pieces, kingPos);
        for (unsigned int i: moves)
            if (kingSide != pieces[i]->getSide()
                && pieces[i]->getSide() != Side::EMPTY
                && pieces[i]->getCode() == piece->getCode() - (kingSide == Side::WHITE ? 1 : 0)) {
                return true;
            }
    }
    return false;
}

bool Game::isCheckmate(Side kingSide) {
    /**
     * This function checks if there is any possible move for the pieces of the same color as the King.
     * If there's not any possible move, it is checkmate. It is also used for the draw condition.
     */

    for (unsigned int it = 0; it < 64; it++) {
        if (pieces[it]->getSide() == kingSide) {
            std::vector<unsigned int> moves = legalMoves(it);
            if (!moves.empty())
                return false;
        }
    }
    return true;
}
