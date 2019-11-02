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
    const int number;
    std::vector<Carriage> carriages;
    int maxPassengerCapacity;
    int maxTradeCapacity;
    int currPassenCapacity;
    int currTradeCapacity;
    int curentCapacity;
    const std::string trainView = "";
    sf::Texture trainTextur;
    sf::Sprite trainSprite;
public:
    int getPassengerCapacity(){
        return currPassenCapacity;
    }
    int getMaxPassenCapacity(){
        return maxPassengerCapacity;
    }
    int getTradeCapacity(){
        return currTradeCapacity;
    }
    int getMaxTradeCapacity(){
        return maxTradeCapacity;
    }
    void setTradeProd(int setter){
        currTradeCapacity  = setter;
    }
    void setPassengers(int setter){
        currPassenCapacity  = setter;
    }
    int getNumber(){
        return number;
    }
    float getMovespeed();
    Train(int trade, int passenger, int stationId);
};



#endif //TRAINLAB_TRAIN_H
