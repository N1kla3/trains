//
// Created by Kolya on 10/19/2019.
//

#include "Map.h"

#include <cmath>

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
    int id, type, x ,y;
    if(file.is_open()) {
        while (file >> id >> type >> x >> y) {
            if (type == 1) {
                auto *station = new TradeStation(id, type, (float) x, (float) y);
                stations.push_back(*station);
            } else if (type == 2) {
                auto *station = new PassStation(id, type, (float) x, (float) y);
                stations.push_back(*station);
            } else {
                auto *station = new Station(id, type, (float) x, (float) y);
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
            auto *train = new Train(trade, passenger, num);
            trains.push_back(*train);
        }
    }
}

void Map::initializeTrains() {
    for(Station station : stations){
        for(Train train : trains){
            if(station.getNumber() == train.getNumber()) {
                station.getTrain(&train);
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

void Map::drawMap(sf::RenderWindow *window) {
    mapTexture.loadFromFile(mapView);
    mapSprite.setTexture(mapTexture);
    window->draw(mapSprite);
    drawRailways(window);
    drawStations(window);
}

Map::Map() {
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