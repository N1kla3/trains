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
    int freeSpace = arrivedTrain->getMaxTradeCapacity() -
                    arrivedTrain->getTradeCapacity();

    if(product > freeSpace){
        product -= freeSpace;
        arrivedTrain->addTradeProd(freeSpace);
    }else{
        arrivedTrain->addTradeProd(product);
        product = 0;
    }
}

void TradeStation::unloading() {
    int freeSpace = maxProduct - product;
    if(arrivedTrain->getTradeCapacity() < freeSpace) {
        product += arrivedTrain->getTradeCapacity();
        arrivedTrain->redTradeProd(arrivedTrain->getTradeCapacity());
    }else{
        product = maxProduct;
        arrivedTrain->redTradeProd(freeSpace);
    }
}

void PassStation::downloading() {
    int freeSpace = arrivedTrain->getMaxPassenCapacity() -
                    arrivedTrain->getPassengerCapacity();

    if(product > freeSpace){
        product -= freeSpace;
        arrivedTrain->addPassengers(freeSpace);
    }else{
        arrivedTrain->addPassengers(product);
        product = 0;
    }
}

void PassStation::unloading() {
    int freeSpace = maxProduct - product;
    if(arrivedTrain->getPassengerCapacity() < freeSpace) {
        product += arrivedTrain->getPassengerCapacity();
        arrivedTrain->redPassengers(arrivedTrain->getPassengerCapacity());
    }else{
        product = maxProduct;
        arrivedTrain->redPassengers(freeSpace);
    }
}