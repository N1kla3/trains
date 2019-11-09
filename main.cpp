
#include "Map.h"
#include "iostream"
int main()
{
    sf::RenderWindow window(sf::VideoMode().getDesktopMode(), "trainsss");

    auto *map = new Map();
    sf::Clock clock;

    while (window.isOpen()) {

        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 500 ;


        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }
            map->getInfo();
            window.clear();
            map->drawMap(&window, time);
            window.display();
        }
    }
    return 0;
}