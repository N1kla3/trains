//
// Created by Kolya on 10/17/2019.
//

#ifndef TRAINLAB_TRAIN_H
#define TRAINLAB_TRAIN_H

#define TRADE 'a'
#define PASSENGER 'b'

#include <vector>
#include "SFML/include/SFML/Audio.hpp"
#include "SFML/include/SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include <cmath>

class Carriage{
private:
    const char type;
    int passengerCapacity = 0;
    int tradeCapacity = 0;
public:
    explicit Carriage(const char);
    friend class Train;
};

class Train {
private:
    int number;
    std::vector<Carriage> carriages;
    int maxPassengerCapacity;
    int maxTradeCapacity;
    int currPassenCapacity;
    int currTradeCapacity;
    float movespeed;
    const std::string trainView = "C:/Users/Kolya/CLionProjects/trainLab/pictures/train.png";
    sf::Image image;
    sf::Texture trainTextur;
    float xWayToStation;
    float yWayToStation;
    float xPixelMove;
    float yPixelMove;
    void initPixelMove();
public:
    sf::Sprite *trainSprite;
    int nextStation;
    float getY(){return yWayToStation;}
    float getX(){return xWayToStation;}
    static float calculateLength(float x, float y);
    static double calculateRotation(float x, float y, float lentgh);

    void initSprite(float x, float y, float xDiff, float yDiff);
    void deleteSprite();
    void moveTrain(sf::RenderWindow *window, float time);

    int getPassengerCapacity(){return currPassenCapacity;}
    int getMaxPassenCapacity(){return maxPassengerCapacity;}
    int getTradeCapacity(){return currTradeCapacity;}
    int getMaxTradeCapacity(){return maxTradeCapacity;}
    void setTradeProd(int setter){currTradeCapacity  = setter;}
    void setPassengers(int setter){currPassenCapacity  = setter;}
    int getNumber(){return number;}
    void setNumber(int setter){number = setter;}
    float getMovespeed();
    Train(int trade, int passenger, int stationId);
};



#endif //TRAINLAB_TRAIN_H
