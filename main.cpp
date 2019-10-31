
#include "Map.h"
#include "iostream"
int main()
{
    auto *d = new TradeStation(2, 2,412,400);
    Train *train = new Train(2, 3, 2);
    d->getTrain(train);

    sf::RenderWindow window(sf::VideoMode().getDesktopMode(), "trainsss");
    /*sf::Sprite shape;
    sf::Texture grass;
    sf::Image image;
    image.loadFromFile( "C:/Users/Kolya/CLionProjects/trainLab/pictures/Untitled.png" );
    image.createMaskFromColor( sf::Color::Black, 0 );
    sf::Texture texTank;
    texTank.loadFromImage( image, sf::IntRect( 0, 0, 600, 600 ) );
    sf::Sprite sprTank;
    sprTank.setTexture( texTank );
    shape.setRotation(shape.getRotation() + 45);

    grass.loadFromFile("C:/Users/Kolya/CLionProjects/trainLab/pictures/grass.png", sf::IntRect( 500, 500, 800, 800 ));
    shape.setTexture(grass);*/


    auto *map = new Map();
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            /*if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                shape.move(5, 2.5);
            }*/
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        map->initMap(&window);
        window.display();
    }
    return 0;
}