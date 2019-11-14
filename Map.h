//
// Created by Kolya on 10/19/2019.
//

#ifndef TRAINLAB_MAP_H
#define TRAINLAB_MAP_H

#include <fstream>
#include "Station.h"


class Map {
private:
    class railWay {
        const std::string imagePath = "C:/Users/Kolya/CLionProjects/trainLab/pictures/railways.png";
        sf::Image image;
        sf::Texture railway;
    public:
        sf::Sprite sprite;
        explicit railWay(Map *map, int beginStationId, int endStationId) {

            float xDiff = map->stations[beginStationId]->getX() - map->stations[endStationId]->getX();
            float yDiff = map->stations[beginStationId]->getY() - map->stations[endStationId]->getY();

            image.loadFromFile(imagePath);
            image.createMaskFromColor( sf::Color::White, 0 );

            float length  = Train::calculateLength(xDiff, yDiff);

            railway.loadFromImage(image, sf::IntRect(0, 0, length, 100 ));
            railway.setSmooth(true);

            sprite.setTexture(railway);
            sprite.setPosition(map->stations[beginStationId]->getX() + 75, map->stations[beginStationId]->getY() + 75);
            sprite.setOrigin(0, 50);
            sprite.rotate((float) Train::calculateRotation(xDiff, yDiff, length));
        }
    };

    std::vector<Train*> trains;
    std::vector<Station*> stations;
    std::vector<railWay*> railways;
    Train * infoTrain = nullptr;
    Station * infoStation = nullptr;

    int amountOfStations = 0;
    int size;
    int** field;
    void createField();
    int getNextStation(int currStationId);

    void readField();
    void readStations();
    void readTrain();

    void initializeTrains();
    void makeRailways();

    void drawStations(sf::RenderWindow *window);
    void drawRailways(sf::RenderWindow *window);
    void drawTrains(sf::RenderWindow *window, float time);

    const std::string mapView = "C:/Users/Kolya/CLionProjects/trainLab/pictures/map.png";
    const std::string menuView = "C:/Users/Kolya/CLionProjects/trainLab/pictures/menu.png";
    sf::Texture mapTexture;
    sf::Texture menuTexture;
    sf::Sprite mapSprite;
    sf::Sprite menuSprite;

    sf::Font font;
    sf::Text textPassCapacity;
    sf::Text textPassInfo;
    sf::Text textMaxPassCapacity;
    sf::Text textTradeCapacity;
    sf::Text textTradeInfo;
    sf::Text textMaxTradeCapacity;
    sf::Text textMoveSpeed;
    sf::Text textSpeedInfo;
    void initText();
    void drawText(sf::RenderWindow * window);
    void setText(Train * train, Station * station);
public:
    void getInfo();
    void drawMap(sf::RenderWindow *window, float time);
    Map();
    ~Map();
};

#endif //TRAINLAB_MAP_H
