// Created by Kolya on 10/17/2019.
//

#include "Station.h"


void Station::handleTrain(Train *train){
    if(train->getMaxPassenCapacity() > train->getPassengerCapacity() ||
                train->getMaxTradeCapacity() > train->getTradeCapacity()){
        downloading(train);
    }else{
        unloading(train);
    }
}

void Station::getTrain() {
    hasTrain = true;
}

void Station::loseTrain() {
    hasTrain = false;
}

void Station::initSprite(float x, float y, const std::string picturePath) {
    image.loadFromFile(picturePath );
    image.createMaskFromColor( sf::Color::White, 0 );
    stationTexture.loadFromImage( image, sf::IntRect( 0, 0, 150, 150 ) );
    stationSprite.setTexture(stationTexture);
    stationSprite.setPosition(x, y);
}


void TradeStation::downloading(Train *train) {
    int trainFreeSpace = train->getMaxTradeCapacity() -
                         train->getTradeCapacity();

    if(product > trainFreeSpace){
        product -= trainFreeSpace;
        train->setTradeProd(train->getMaxTradeCapacity());
    }else{
        train->setTradeProd(train->getTradeCapacity() + product);
        product = 0;
    }
}

void TradeStation::unloading(Train *train) {
    int stationFreeSpace = maxProduct - product;
    if(train->getTradeCapacity() < stationFreeSpace) {
        product += train->getTradeCapacity();
        train->setTradeProd(0);
    }else{
        product = maxProduct;
        train->setTradeProd(train->getTradeCapacity() - stationFreeSpace);
    }
}

void PassStation::downloading(Train *train) {
    int trainFreeSpace = train->getMaxPassenCapacity() -
                         train->getPassengerCapacity();

    if(product > trainFreeSpace){
        product -= trainFreeSpace;
        train->setPassengers(train->getMaxPassenCapacity());
    }else{
        train->setPassengers(train->getPassengerCapacity() + product);
        product = 0;
    }
}

void PassStation::unloading(Train *train) {
    int stationFreeSpace = maxProduct - product;
    if(train->getPassengerCapacity() < stationFreeSpace) {
        product += train->getPassengerCapacity();
        train->setPassengers(0);
    }else{
        product = maxProduct;
        train->setPassengers(train->getTradeCapacity() - stationFreeSpace);
    }
}