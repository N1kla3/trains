//
// Created by Kolya on 10/19/2019.
//

#include "Map.h"


void Map::createField(){
    field = new int*[amountOfStations];
    for(int i = 0; i < amountOfStations; i++){
        field[i] = new int[amountOfStations];
    }
    for(int i = 0; i < amountOfStations; i++){
        for(int j = 0; j < amountOfStations; j++){
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
            switch (type) {
                case TRADES :{
                    auto *station = new TradeStation( type,id-1, capacity, (float) x, (float) y);
                    stations.push_back(station);
                    break;
                }
                case PASSENGERS : {
                    auto *station = new PassStation(type, id - 1, capacity, (float) x, (float) y);
                    stations.push_back(station);
                    break;
                }
                default: {
                    auto *station = new Station(type,id-1,  capacity, (float) x, (float) y);
                    stations.push_back(station);
                    break;
                }
            }amountOfStations++;
        }
    }
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
    const float menuCoordX = 1130;
    const float offsetY = 70;

    font.loadFromFile("C:/Windows/Fonts/Arial.ttf");

    textPassCapacity.setPosition(menuCoordX, offsetY);
    textPassCapacity.setFont(font);
    textPassCapacity.setString("Passenger capacity ");
    textPassCapacity.setCharacterSize(24);
    textPassCapacity.setFillColor(sf::Color::Blue);

    textPassInfo.setFont(font);
    textPassInfo.setPosition(menuCoordX, offsetY * 2);
    textPassInfo.setCharacterSize(24);
    textPassInfo.setFillColor(sf::Color::Green);

    textMaxPassCapacity.setFont(font);
    textMaxPassCapacity.setPosition(menuCoordX, offsetY * 3);
    textMaxPassCapacity.setCharacterSize(24);
    textMaxPassCapacity.setFillColor(sf::Color::Red);

    textTradeCapacity.setFont(font);
    textTradeCapacity.setPosition(menuCoordX, offsetY * 4);
    textTradeCapacity.setString("Trade capacity ");
    textTradeCapacity.setCharacterSize(24);
    textTradeCapacity.setFillColor(sf::Color::Blue);

    textTradeInfo.setFont(font);
    textTradeInfo.setPosition(menuCoordX, offsetY * 5);
    textTradeInfo.setCharacterSize(24);
    textTradeInfo.setFillColor(sf::Color::Green);

    textMaxTradeCapacity.setFont(font);
    textMaxTradeCapacity.setPosition(menuCoordX, offsetY * 6);
    textMaxTradeCapacity.setCharacterSize(24);
    textMaxTradeCapacity.setFillColor(sf::Color::Red);

    textMoveSpeed.setFont(font);
    textMoveSpeed.setPosition(menuCoordX, offsetY * 7);
    textMoveSpeed.setString("Movespeed ");
    textMoveSpeed.setCharacterSize(24);
    textMoveSpeed.setFillColor(sf::Color::Blue);

    textSpeedInfo.setFont(font);
    textSpeedInfo.setPosition(menuCoordX, offsetY * 8);
    textSpeedInfo.setCharacterSize(24);
    textSpeedInfo.setFillColor(sf::Color::Green);

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
    for (int i = 0; i < amountOfStations; i++) {
        for (int j = i; j < amountOfStations; j++) {
            if (field[i][j] == 1) {
                auto *railway = new railWay(this, i, j);
                railways.push_back(railway);
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
    for(railWay *i : railways){
        window->draw(i->sprite);
    }
}

int Map::getNextStation(int currStationId) {
    if(currStationId < amountOfStations){
    for(int i = 0; i < amountOfStations; i++){
        if(i == currStationId) continue;
        if(field[currStationId][i]){
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
    window->draw(textMaxTradeCapacity);
    window->draw(textPassCapacity);
    window->draw(textPassInfo);
    window->draw(textMaxPassCapacity);
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
        if(station->getType() == TRADES) {
            textSpeedInfo.setString("none");
            textTradeInfo.setString(std::to_string(station->getProduct()));
            textMaxTradeCapacity.setString(std::to_string(station->getMaxProduct()));
            textPassInfo.setString("none");
            textMaxPassCapacity.setString("none");
        }else if(station->getType() == PASSENGERS){
            textSpeedInfo.setString("none");
            textTradeInfo.setString("none");
            textMaxTradeCapacity.setString("none");
            textPassInfo.setString(std::to_string(station->getProduct()));
            textMaxPassCapacity.setString(std::to_string(station->getMaxProduct()));
        }else {
            textSpeedInfo.setString("none");
            textTradeInfo.setString("none");
            textMaxTradeCapacity.setString("none");
            textPassInfo.setString("none");
            textMaxPassCapacity.setString("none");
        }
    }else if(station == nullptr){
        textSpeedInfo.setString(std::to_string(train->getMovespeed()));
        textTradeInfo.setString(std::to_string(train->getTradeCapacity()));
        textMaxTradeCapacity.setString(std::to_string(train->getMaxTradeCapacity()));
        textPassInfo.setString(std::to_string(train->getPassengerCapacity()));
        textMaxPassCapacity.setString(std::to_string(train->getMaxPassenCapacity()));
    }
}

void Map::getInfo() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(infoStation != nullptr)
            infoStation->stationSprite.setScale(1, 1);
        if(infoTrain != nullptr)
            if(infoTrain->trainSprite != nullptr)
                infoTrain->trainSprite->setScale(1, 1);

        for(Station *station : stations){
            float stationSize = 200;
            bool stationClicked = (sf::Mouse::getPosition().x > station->getX()) && (sf::Mouse::getPosition().x < station->getX() + stationSize)
                                  &&
                                  (sf::Mouse::getPosition().y > station->getY()) && (sf::Mouse::getPosition().y < station->getY() + stationSize);
            if(stationClicked)
            {
                setText(nullptr, station);
                infoStation = station;
                infoStation->stationSprite.setScale(1.5, 1.5);
                return;
            }
        }
        for(Train *train : trains) {
            if (train->trainSprite != nullptr) {
                float trainSize = 100;
                bool trainClicked = (sf::Mouse::getPosition().x > train->trainSprite->getPosition().x - trainSize)
                                    && (sf::Mouse::getPosition().x < train->trainSprite->getPosition().x + trainSize)
                                    &&
                                    (sf::Mouse::getPosition().y > train->trainSprite->getPosition().y - trainSize)
                                    && (sf::Mouse::getPosition().y < train->trainSprite->getPosition().y + trainSize);
                if (trainClicked) {
                    setText(train, nullptr);
                    infoTrain = train;
                    train->trainSprite->setScale(1.5 , 1.5);
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
    for(int i = 0; i < amountOfStations; i++){
        delete  [] field[i];
    }
    delete [] field;

    for(Station *station : stations)
        delete station;
    stations.clear();

    for(Train *train : trains) {
        train->deleteSprite();
        delete train;
    }
    trains.clear();
}
