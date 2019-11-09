
#include "Map.h"
#include "iostream"
int main()
{
    sf::RenderWindow window(sf::VideoMode().getDesktopMode(), "trainsss");

    auto *map = new Map();
    sf::Clock clock;
    int pause = 1;
    sf::Image image;
    image.loadFromFile("C:/Users/Kolya/CLionProjects/trainLab/pictures/gaben.png");
    image.createMaskFromColor( sf::Color::White, 0 );
    sf::Texture gabenTexture;
    gabenTexture.loadFromImage(image);
    sf::Sprite *gabenSprite;

    while (window.isOpen()) {

        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 10005000;


        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }else if(event.type == sf::Event::KeyPressed) {
                    if(event.key.code == sf::Keyboard::Space) {
                        if(pause){
                            pause = 0;
                            gabenSprite = new sf::Sprite(gabenTexture);
                            gabenSprite->setPosition(400, 0);
                            window.draw(*gabenSprite);
                            window.display();
                        }else if(!pause){
                            pause = 1;
                            delete gabenSprite;
                        }
                    }
                }
                }
            if(pause) {
                map->getInfo();
                window.clear();
                map->drawMap(&window, time);
                window.display();
            }
        }
    }
    return 0;
}