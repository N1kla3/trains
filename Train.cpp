//
// Created by Kolya on 10/17/2019.
//

#include "Train.h"

Carriage::Carriage(const char typ) : type(typ) {
    if(typ == TRADE){
        passengerCapacity = 0;
        tradeCapacity = 80;
    }else if(typ == PASSENGER){
        passengerCapacity = 50;
        tradeCapacity = 0;
    }
}

Train::Train(int trade, int passenger, int stationId)
        : number(stationId) {
    maxTradeCapacity = 0;
    maxPassengerCapacity = 0;
    for(int i = 0; i < trade; i++){
        Carriage carr(TRADE);
        carriages.push_back(carr);
        maxTradeCapacity += carr.tradeCapacity;
    }

    for(int i = 0; i < passenger; i++){
        Carriage carr(PASSENGER);
        carriages.push_back(carr);
        maxPassengerCapacity += carr.passengerCapacity;
    }
    currPassenCapacity = 0;
    currTradeCapacity = 0;
    nextStation = 100;
}

void Train::deleteSprite() {
    delete trainSprite;
    trainSprite = nullptr;
}

float Train::getMovespeed() {
    float relation = ((float)((float)(currPassenCapacity + currTradeCapacity)/(float)(maxPassengerCapacity + maxTradeCapacity)))*100;
    return 100 - relation;
}

void Train::initPixelMove() {
    float r = 1;
    float z = 1;
    if(fabsf(yWayToStation) > fabsf(xWayToStation)){
        z = fabsf(xWayToStation / yWayToStation);
    }else r = fabsf(yWayToStation / xWayToStation);

    if((yWayToStation < 0 && xWayToStation < 0) || (yWayToStation > 0 && xWayToStation > 0)){
        xPixelMove = ((0 - movespeed) / (yWayToStation / fabsf(yWayToStation))) * z;
        yPixelMove = ((0 - movespeed) / (xWayToStation / fabsf(xWayToStation))) * r;
    }else {
        xPixelMove = (movespeed / (yWayToStation / fabsf(yWayToStation))) * z;
        yPixelMove = (movespeed / (xWayToStation / fabsf(xWayToStation))) * r;
    }
}

void Train::initSprite(float x, float y, float xDiff, float yDiff) {
    movespeed = getMovespeed();
    image.loadFromFile(trainView);
    image.createMaskFromColor( sf::Color::White, 0 );

    float length  = Train::calculateLength(xDiff, yDiff);

    trainTextur.loadFromImage(image, sf::IntRect(0, 0, length, 100 ));
    trainTextur.setSmooth(true);
    trainSprite = new sf::Sprite;
    trainSprite->setTexture(trainTextur);
    trainSprite->setPosition(x + 75, y + 75);
    trainSprite->setOrigin(0, 50);
    trainSprite->rotate((float) Train::calculateRotation(xDiff, yDiff, length));
    this->yWayToStation = yDiff;
    this->xWayToStation = xDiff;
    initPixelMove();
}

void Train::moveTrain(sf::RenderWindow *window, float time) {

    trainSprite->move(xPixelMove * time, yPixelMove * time);
    sf::Vector2f lol = trainSprite->getPosition();
    std::cout << lol.x << std::ends;
    std::cout << lol.y << std::endl;
    window->draw(*trainSprite);
}

double Train::calculateRotation(float x, float y, float lentgh) {
    double res = 0;
    float result = 0;
    if((x > 0 && y > 0) || (x < 0 && y > 0)){
        result = fabsf(y) / lentgh;
    }else if((x > 0 && y < 0) || (x < 0 && y < 0)){
        result = fabsf(x) / lentgh;
    }
    res = (asin((double)result)*(180/3.14159265359));
    if(x > 0 && y < 0){
        res = 90 + res;
    }else if (x > 0 && y > 0){
        res += 180;
    }else if(x < 0 && y > 0){
        res = 360 - res;
    }else if (x < 0 && y < 0){
        res = 90 - res;
    }
    return res;
}

float Train::calculateLength(float x, float y) {
    float res = (std::sqrt(x*x + y*y));
    return res;
}
