//
// Created by Kolya on 10/19/2019.
//

#include "Map.h"


void Map::createField(){
    field = new int*[size];
    for(int i = 0; i < size; i++){
        field[i] = new int[size];
    }
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            field[i][j] = 0;
        }
    }
}

void Map::readField() {
    std::ifstream file("C:/Users/Kolya/CLionProjects/trainLab/Map.txt");
    if(file.is_open()){
        createField();
        int a, b;
        while (file >> a >> b){
            field[a-1][b-1] = 1;
            field[b-1][a-1] = 1;
        }
    }
}

void Map::readStations(){
    std::ifstream file("C:/Users/Kolya/CLionProjects/trainLab/stations.txt");
    int id, type, capacity, x ,y;
    if(file.is_open()) {
        while (file >> id >> type >> capacity >> x >> y) {
            if (type == 1) {
                auto *station = new TradeStation( type,id-1, capacity, (float) x, (float) y);
                stations.push_back(station);
            } else if (type == 2) {
                auto *station = new PassStation( type, id-1,capacity, (float) x, (float) y);
                stations.push_back(station);
            } else {
                auto *station = new Station(type,id-1,  capacity, (float) x, (float) y);
                stations.push_back(station);
            }Map::amountOfStations++;
        }
    }
    size = Map::amountOfStations;
}

void Map::readTrain() {
    std::ifstream file("C:/Users/Kolya/CLionProjects/trainLab/trains.txt");
    int num, trade, passenger;
    if(file.is_open()){
        while(file >> num >> trade >> passenger){
            auto *train = new Train(trade, passenger, num-1);
            trains.push_back(train);
            stations[num - 1]->getTrain();
        }
    }
}

void Map::initText() {
    font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
    textPassCapacity.setPosition(1130, 50);
    textPassCapacity.setFont(font);
    textPassCapacity.setString("Passenger capacity ");
    textPassCapacity.setCharacterSize(24);
    textPassCapacity.setFillColor(sf::Color::Green);

    textTradeCapacity.setFont(font);
    textTradeCapacity.setPosition(1130, 250);
    textTradeCapacity.setString("Trade capacity ");
    textTradeCapacity.setCharacterSize(24);
    textTradeCapacity.setFillColor(sf::Color::Green);

    textMoveSpeed.setFont(font);
    textMoveSpeed.setPosition(1130, 450);
    textMoveSpeed.setString("Movespeed ");
    textMoveSpeed.setCharacterSize(24);
    textMoveSpeed.setFillColor(sf::Color::Green);

    textPassInfo.setFont(font);
    textPassInfo.setPosition(1130, 150);
    textPassInfo.setCharacterSize(24);
    textPassInfo.setFillColor(sf::Color::Red);

    textTradeInfo.setFont(font);
    textTradeInfo.setPosition(1130, 350);
    textTradeInfo.setCharacterSize(24);
    textTradeInfo.setFillColor(sf::Color::Red);

    textSpeedInfo.setFont(font);
    textSpeedInfo.setPosition(1130, 550);
    textSpeedInfo.setCharacterSize(24);
    textSpeedInfo.setFillColor(sf::Color::Red);

}

void Map::initializeTrains() {
    for(Station *station : stations){
        for(Train *train : trains){
            if(station->getNumber() == train->getNumber()) {
                if(getNextStation(station->getNumber()) >= 0) {
                    station->loseTrain();
                    int number = station->getNumber();
                    train->nextStation = getNextStation(number);
                    stations[train->nextStation]->getTrain();
                    float x = stations[number]->getX();
                    float y = stations[number]->getY();
                    float xDiff = stations[number]->getX() - stations[train->nextStation]->getX();
                    float yDiff = stations[number]->getY() - stations[train->nextStation]->getY();
                    train->initSprite(x, y, xDiff, yDiff);
                }else train->trainSprite = nullptr;
                break;
            }
        }
    }
}

void Map::makeRailways() {
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            if (field[i][j] == 1) {
                auto *railway = new railWay(this, i, j);
                railSprites.push_back(railway);
            }
        }
    }
}

void Map::drawStations(sf::RenderWindow *window) {
    for(Station *station : stations){
        window->draw(station->stationSprite);
    }
}

void Map::drawRailways(sf::RenderWindow *window) {
    for(railWay *i : railSprites){
        window->draw(i->sprite);
    }
}

int Map::getNextStation(int number) {
    if(number < size){
    for(int i = 0; i < size; i++){
        if(i == number) continue;
        if(field[number][i]){
            if(!stations[i]->haveTrain())
                return i;
        }
    }
}
    return -1;
}

void Map::drawText(sf::RenderWindow *window) {
    window->draw(textTradeCapacity);
    window->draw(textTradeInfo);
    window->draw(textPassCapacity);
    window->draw(textPassInfo);
    window->draw(textMoveSpeed);
    window->draw(textSpeedInfo);
}

void Map::drawTrains(sf::RenderWindow *window, float time) {
    for(Train *train : trains){
        int number = train->getNumber();
        if(train->trainSprite == nullptr){
            if(getNextStation(number) >= 0) {
                stations[number]->loseTrain();
                train->nextStation = getNextStation(number);
                stations[train->nextStation]->getTrain();
                float x = stations[number]->getX();
                float y = stations[number]->getY();
                float xDiff = stations[number]->getX() - stations[train->nextStation]->getX();
                float yDiff = stations[number]->getY() - stations[train->nextStation]->getY();
                train->initSprite(x, y, xDiff, yDiff);
            }
        }else {
            bool isTrainGettoStation = (round(train->trainSprite->getPosition().x) > stations[train->nextStation]->getX()
                    && round(train->trainSprite->getPosition().x) <stations[train->nextStation]->getX() + 100)
                                       &&
                    ((round(train->trainSprite->getPosition().y) > stations[train->nextStation]->getY())
                    && round(train->trainSprite->getPosition().y) <stations[train->nextStation]->getY() + 100);

            if (isTrainGettoStation) {
                train->deleteSprite();
                stations[train->nextStation]->handleTrain(train);
                train->setNumber(stations[train->nextStation]->getNumber());
            } else if (train->trainSprite != nullptr) {
                train->moveTrain(window, time);
            }
        }
    }
}

void Map::setText(Train *train, Station *station) {
    if(train == nullptr) {
        if(station->getType() == 1) {
            textSpeedInfo.setString("none");
            textTradeInfo.setString(std::to_string(station->getProduct()));
            textPassInfo.setString("none");
        }else if(station->getType() == 2){
            textSpeedInfo.setString("none");
            textTradeInfo.setString("none");
            textPassInfo.setString(std::to_string(station->getProduct()));
        }else {
            textSpeedInfo.setString("none");
            textTradeInfo.setString("none");
            textPassInfo.setString("none");
        }
    }else if(station == nullptr){
        textSpeedInfo.setString(std::to_string(train->getMovespeed()));
        textTradeInfo.setString(std::to_string(train->getTradeCapacity()));
        textPassInfo.setString(std::to_string(train->getPassengerCapacity()));
    }
}

void Map::getInfo() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        for(Station *station : stations){
            if((sf::Mouse::getPosition().x > station->getX()) && (sf::Mouse::getPosition().x < station->getX() + 200)
            &&
            (sf::Mouse::getPosition().y > station->getY()) && (sf::Mouse::getPosition().y < station->getY() + 200))
            {
                setText(nullptr, station);
                return;
            }
        }
        for(Train *train : trains) {
            if (train->trainSprite != nullptr) {
                if ((sf::Mouse::getPosition().x > train->trainSprite->getPosition().x - 100)
                    && (sf::Mouse::getPosition().x < train->trainSprite->getPosition().x + 100)
                    &&
                    (sf::Mouse::getPosition().y > train->trainSprite->getPosition().y - 100)
                    && (sf::Mouse::getPosition().y < train->trainSprite->getPosition().y + 100)) {
                    setText(train, nullptr);
                    return;
                }
            }
        }
    }
}

void Map::drawMap(sf::RenderWindow *window, float time) {
    window->draw(mapSprite);
    window->draw(menuSprite);
    drawRailways(window);
    drawTrains(window, time);
    drawStations(window);
    drawText(window);
}

Map::Map() {
    initText();
    mapTexture.loadFromFile(mapView);
    menuTexture.loadFromFile(menuView);
    mapSprite.setTexture(mapTexture);
    menuSprite.setTexture(menuTexture);
    menuSprite.setPosition(1100, 0);
    readStations();
    createField();
    readField();
    readTrain();
    initializeTrains();
    makeRailways();
}

Map::~Map() {
    for(int i = 0; i < size; i++){
        delete  [] field[i];
    }
    delete [] field;
}
