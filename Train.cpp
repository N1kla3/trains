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
}

float Train::getMovespeed() {
    return 1000;
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
    trainSprite->setPosition(x + 75, y + 65);
    trainSprite->rotate((float) Train::calculateRotation(xDiff, yDiff, length));
    this->y = yDiff;
    this->x = xDiff;
}

void Train::moveTrain(sf::RenderWindow *window, float time) {
    float xMove;
    float yMove;
    if((y < 0 && x < 0) || (y > 0 && x > 0)){
        xMove = ((0-movespeed)/y)*time;
        yMove = ((0-movespeed)/x)*time;
    }else {
        xMove = (movespeed/y)*time;
        yMove = (movespeed/x)*time;
    }
    trainSprite->move(xMove, yMove);
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
        res = 180 - res;
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
