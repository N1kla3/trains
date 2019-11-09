// Created by Kolya on 10/17/2019.
//

#include "Station.h"


void Station::handleTrain(Train *train){
    std::cout << "its just Fork";
}

void TradeStation::handleTrain(Train *train) {
    int trainTradefreeSpace = train->getMaxTradeCapacity() - train->getTradeCapacity();
    if(trainTradefreeSpace > train->getTradeCapacity()){
        downloading(train);
    }else{
        unloading(train);
    }
}

void PassStation::handleTrain(Train *train) {
    int trainPassfreeSpace = train->getMaxPassenCapacity() - train->getPassengerCapacity();
    if(trainPassfreeSpace > train->getPassengerCapacity()){
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
    int freeSpace = train->getMaxTradeCapacity() - train->getTradeCapacity();
    if(product >= 100 && freeSpace >= 100){
        product -= 100;
        train->setTradeProd(train->getTradeCapacity() + 100);
    }else{
        if(product <= freeSpace){
            train->setTradeProd(train->getTradeCapacity() + product);
            product = 0;
        }else  if(product > freeSpace){
            train->setTradeProd(train->getTradeCapacity() + freeSpace);
            product -= freeSpace;
        }
    }
}

void TradeStation::unloading(Train *train) {
    int freeSpace = maxProduct - product;
    if(train->getTradeCapacity() >= 100 && freeSpace >= 100){
        product += 100;
        train->setTradeProd(train->getTradeCapacity() - 100);
    }else{
        if(product <= freeSpace){
            product += train->getTradeCapacity();
            train->setTradeProd(0);
        }else  if(product > freeSpace){
            train->setTradeProd(train->getTradeCapacity() - freeSpace);
            product += freeSpace;
        }
    }
}

void PassStation::downloading(Train *train) {
    int freeSpace = train->getMaxPassenCapacity() - train->getPassengerCapacity();
    if(product >= 100 && freeSpace >= 100){
        product -= 100;
        train->setPassengers(train->getPassengerCapacity() + 100);
    }else{
        if(product <= freeSpace){
            train->setPassengers(train->getPassengerCapacity() + product);
            product = 0;
        }else  if(product > freeSpace){
            train->setPassengers(train->getPassengerCapacity() + freeSpace);
            product -= freeSpace;
        }
    }
}

void PassStation::unloading(Train *train) {
    int freeSpace = maxProduct - product;
    if(train->getPassengerCapacity() >= 100 && freeSpace >= 100){
        product += 100;
        train->setPassengers(train->getPassengerCapacity() - 100);
    }else{
        if(product <= freeSpace){
            product += train->getPassengerCapacity();
            train->setPassengers(0);
        }else  if(product > freeSpace){
            train->setPassengers(train->getPassengerCapacity() - freeSpace);
            product += freeSpace;
        }
    }
}
