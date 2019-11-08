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
    int id, capacity, x ,y;
    if(file.is_open()) {
        while (file >> id >> capacity >> x >> y) {
            if (capacity == 1) {
                auto *station = new TradeStation(id-1, capacity, (float) x, (float) y);
                stations.push_back(*station);
            } else if (capacity == 2) {
                auto *station = new PassStation(id-1, capacity, (float) x, (float) y);
                stations.push_back(*station);
            } else {
                auto *station = new Station(id-1, capacity, (float) x, (float) y);
                stations.push_back(*station);
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
            trains.push_back(*train);
            stations[num - 1].getTrain();
        }
    }
}

void Map::initializeTrains() {
    for(Station &station : stations){
        for(Train &train : trains){
            if(station.getNumber() == train.getNumber()) {
                if(getNextStation(station.getNumber()) >= 0) {
                    station.loseTrain();
                    int number = station.getNumber();
                    train.nextStation = getNextStation(number);
                    stations[train.nextStation].getTrain();
                    float x = stations[number].getX();
                    float y = stations[number].getY();
                    float xDiff = stations[number].getX() - stations[train.nextStation].getX();
                    float yDiff = stations[number].getY() - stations[train.nextStation].getY();
                    train.initSprite(x, y, xDiff, yDiff);
                }else train.trainSprite = nullptr;
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
                railSprites.push_back(*railway);
            }
        }
    }
}

void Map::drawStations(sf::RenderWindow *window) {
    for(Station &station : stations){
        window->draw(station.stationSprite);
    }
}

void Map::drawRailways(sf::RenderWindow *window) {
    for(railWay &i : railSprites){
        window->draw(i.sprite);
    }
}

int Map::getNextStation(int number) {
    if(number < size){
    for(int i = 0; i < size; i++){
        if(i == number) continue;
        if(field[number][i]){
            if(!stations[i].haveTrain())
                return i;
        }
    }
}
    return -1;
}

void Map::drawTrains(sf::RenderWindow *window, float time) {
    for(Train &train : trains){
        int number = train.getNumber();
        if(train.trainSprite == nullptr){
            if(getNextStation(number) >= 0) {
                if(train.nextStation != 100){
                    train.setNumber(train.nextStation);
                    number = train.getNumber();
                }
                stations[number].loseTrain();
                train.nextStation = getNextStation(number);
                stations[train.nextStation].getTrain();
                float x = stations[number].getX();
                float y = stations[number].getY();
                float xDiff = stations[number].getX() - stations[train.nextStation].getX();
                float yDiff = stations[number].getY() - stations[train.nextStation].getY();
                train.initSprite(x, y, xDiff, yDiff);
            }
        }else {
            bool isTrainGettoStation = (round(train.trainSprite->getPosition().x) > stations[train.nextStation].getX()
                    && round(train.trainSprite->getPosition().x) <stations[train.nextStation].getX() + 100)
                                       &&
                    ((round(train.trainSprite->getPosition().y) > stations[train.nextStation].getY())
                    && round(train.trainSprite->getPosition().y) <stations[train.nextStation].getY() + 100);

            if (isTrainGettoStation) {
                train.deleteSprite();
                stations[train.nextStation].handleTrain(&train);
            } else if (train.trainSprite != nullptr) {
                train.moveTrain(window, time);
            }
        }
    }
}

void Map::drawMap(sf::RenderWindow *window, float time) {
    window->draw(mapSprite);
    drawRailways(window);
    drawTrains(window, time);
    drawStations(window);
}

Map::Map() {
    mapTexture.loadFromFile(mapView);
    mapSprite.setTexture(mapTexture);
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
