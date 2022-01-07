#include <iostream>
#include "headers/Game.h"

/*
 * Notations in binary code:
 *
*  Pawn    = 0000 0100
*  Knight  = 0000 1000
*  Bishop  = 0001 0000
*  Rook    = 0010 0000
*  Queen   = 0100 0000
*  King    = 1000 0000
*
*  Black   = 0000 0001
*  White   = 0000 0010
 *
*/

int main() {

    auto sah = Game::get_app();
    std::cout << *sah << '\n';
    sah->run();

    return 0;
}
