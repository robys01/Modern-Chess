#include "Game.h"

int main() {

    Game sah;
    std::cout << sah;

    Player p1("Robert", true, 1337);
    Player p2("Bot", false, 1200);
    sah.setWhite(p1);
    sah.setBlack(p2);

    std::cout << sah;
    return 0;
}
