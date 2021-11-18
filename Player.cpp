//
// Created by Robert on 11/18/2021.
//

#include "Player.h"


Player::Player() {
    whiteSide = true;
}

Player::Player(const std::string &name, bool whiteSide, int elo) : name(name), whiteSide(whiteSide), elo(elo){}

std::ostream &operator<<(std::ostream &os, const Player &player) {
    os << (player.whiteSide ? "\tWhite: " : "\tBlack: ") << player.name << " (" << player.elo << ")\n";
    return os;
}

Player &Player::operator=(const Player &copy) {
    this->name = copy.name;
    this->whiteSide = copy.whiteSide;
    this->elo = copy.elo;
    return *this;
}

// Getters and Setters
int Player::getElo() const {
    return elo;
}

void Player::setElo(int elo) {
    this->elo = elo;
}

std::string Player::getName() {
    return this->name;
}

void Player::setName(std::string &name) {
    this->name = name;
}

bool Player::isWhiteSide() const {
    return whiteSide;
}

void Player::setWhiteSide(bool whiteSide) {
    Player::whiteSide = whiteSide;
}
