//
// Created by Robert on 11/18/2021.
//

#include "../headers/Game.h"

Game::Game() : tabla(512){
    playerWhite = Player("Player1", true, 1200);
    playerBlack = Player("Player2", false, 800);
    this->gameEnded = false;
//        std::cout << "In Game Constructor\n";
}

std::ostream &operator<<(std::ostream &os, Game &game) {
    os << game.playerBlack  << game.playerWhite << '\n';
    return os;
}



// Getters and Setters
void Game::setWhite(Player &player) {
    this->playerWhite = player;
}

Player Game::getWhite() const {
    return this->playerWhite;
}

void Game::setBlack(Player &player) {
    this->playerBlack = player;
}

Player Game::getBlack() const {
    return this->playerBlack;
}
