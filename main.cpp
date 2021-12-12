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

    Game sah;
//    std::cout<<sah;
    sah.run();

    return 0;
}





/*
int main() {

    sf::RenderWindow window(sf::VideoMode(512, 512), "Modern Chess", sf::Style::Close);

    Board tabla(512);
    std::cout << tabla;

    while(window.isOpen()) {
        sf::Event e;
        while(window.pollEvent(e)) {
            if(e.type == sf::Event::Closed)
                window.close();
            if(e.type == sf::Event::MouseButtonPressed)
                if(e.mouseButton.button == sf::Mouse::Right) {
                    tabla.changeTheme();
                }
            if(e.type == sf::Event::KeyPressed) {
                if (e.key.code == sf::Keyboard::Right) {
                    tabla.changeTheme();
                } else if(e.key.code == sf::Keyboard::Left)
                    tabla.changeTheme("previous");
            }
        }
        window.clear(sf::Color::Black);

        tabla.drawBoard(window);

        window.display();
    }

    return 0;
}*/
