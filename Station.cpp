//
// Created by Kolya on 10/17/2019.
//

#include "Station.h"


 void Station::getTrain(Train *train){
    hasTrain = true;
    arrivedTrain = train;
    if(train->getMaxPassenCapacity() > train->getPassengerCapacity() ||
                train->getMaxTradeCapacity() > train->getTradeCapacity()){
        downloading();
    }else{
        unloading();
    }
}
void Station::loseTrain() {
    hasTrain = false;
    arrivedTrain = nullptr;
}

void Station::initSprite(float x, float y) {
    image.loadFromFile( picture );
    image.createMaskFromColor( sf::Color::White, 0 );
    stationTexture.loadFromImage( image, sf::IntRect( 0, 0, 150, 150 ) );
    stationSprite.setTexture(stationTexture);
    stationSprite.setPosition(x, y);
}

void TradeStation::initSprite(float x, float y) {
    image.loadFromFile( picture );
    image.createMaskFromColor( sf::Color::White, 0 );
    stationTexture.loadFromImage( image, sf::IntRect( 0, 0, 150, 150 ) );
    stationSprite.setTexture(stationTexture);
    stationSprite.setPosition(x, y);
}

void PassStation::initSprite(float x, float y) {
    image.loadFromFile( picture );
    image.createMaskFromColor( sf::Color::White, 0 );
    stationTexture.loadFromImage( image, sf::IntRect( 0, 0, 150, 150 ) );
    stationSprite.setTexture(stationTexture);
    stationSprite.setPosition(x, y);
}

void TradeStation::downloading() {
    int trainFreeSpace = arrivedTrain->getMaxTradeCapacity() -
                         arrivedTrain->getTradeCapacity();

    if(product > trainFreeSpace){
        product -= trainFreeSpace;
        arrivedTrain->setTradeProd(arrivedTrain->getMaxTradeCapacity());
    }else{
        arrivedTrain->setTradeProd(arrivedTrain->getTradeCapacity() + product);
        product = 0;
    }
}

void TradeStation::unloading() {
    int stationFreeSpace = maxProduct - product;
    if(arrivedTrain->getTradeCapacity() < stationFreeSpace) {
        product += arrivedTrain->getTradeCapacity();
        arrivedTrain->setTradeProd(0);
    }else{
        product = maxProduct;
        arrivedTrain->setTradeProd(arrivedTrain->getTradeCapacity() - stationFreeSpace);
    }
}

void PassStation::downloading() {
    int trainFreeSpace = arrivedTrain->getMaxPassenCapacity() -
                         arrivedTrain->getPassengerCapacity();

    if(product > trainFreeSpace){
        product -= trainFreeSpace;
        arrivedTrain->setPassengers(arrivedTrain->getMaxPassenCapacity());
    }else{
        arrivedTrain->setPassengers(arrivedTrain->getPassengerCapacity() + product);
        product = 0;
    }
}

void PassStation::unloading() {
    int stationFreeSpace = maxProduct - product;
    if(arrivedTrain->getPassengerCapacity() < stationFreeSpace) {
        product += arrivedTrain->getPassengerCapacity();
        arrivedTrain->setPassengers(0);
    }else{
        product = maxProduct;
        arrivedTrain->setPassengers(arrivedTrain->getTradeCapacity() - stationFreeSpace);
    }
}