//
// Created by Robert on 11/18/2021.
//

#ifndef MODERN_CHESS_PLAYER_H
#define MODERN_CHESS_PLAYER_H

#include <iostream>

class Player {
    std::string name;
    bool whiteSide;
    int elo = 800;
    // bool isComputer

public:

    Player();

    Player(const std::string &name, bool whiteSide, int elo);

    ~Player() = default;

    friend std::ostream &operator<<(std::ostream &os, const Player &player);

    Player &operator=(const Player &copy);

    int getElo() const;

    void setElo(int elo);

    std::string getName();

    void setName(std::string &name);

    bool isWhiteSide() const;

    void setWhiteSide(bool whiteSide);
};

#endif //MODERN_CHESS_PLAYER_H
