//
// Created by Kolya on 10/17/2019.
//

#ifndef TRAINLAB_STATION_H
#define TRAINLAB_STATION_H

#include "Train.h"

class Station {
private:
    const std::string picture = "C:/Users/Kolya/CLionProjects/trainLab/pictures/tradeStation.png";
protected:
    Train *arrivedTrain;
    bool hasTrain;
    int number;
    float cordX;
    float cordY;
    int product;
    sf::Image image;
    sf::Texture stationTexture;
    const int maxProduct;
    virtual void unloading(){std::cout << "df";};
    virtual void downloading(){std::cout << "sdfs";};
    virtual void initSprite(float x, float y, std::string picturePath);
    Station(int capacity) : maxProduct(capacity) {}
public:
    sf::Sprite stationSprite;

    float getX(){return cordX;}
    float getY(){return cordY;}
    void loseTrain(Train *arrivedTrain);
    bool haveTrain(){return hasTrain;}
    void getTrain(Train *train);
    int getNumber(){return number;}
    Station(int id, int capacity, float x, float y)
            :maxProduct(capacity), cordY(y), cordX(x){
        number = id;
        product = maxProduct - 100;
        hasTrain = false;
        arrivedTrain = nullptr;
        initSprite(x, y, picture);
    }
};

class TradeStation : public Station{
private:
    const std::string picture  = "C:/Users/Kolya/CLionProjects/trainLab/pictures/passStation.png";
public:
    void downloading()override;
    void unloading()override;
    TradeStation(int id, int capacity, float x, float y)
            :Station(capacity){
        number = id;
        cordX = x;
        cordY = y;
        initSprite(x, y, picture);
    }
};

class PassStation : public Station{
private:
    const std::string picture = "C:/Users/Kolya/CLionProjects/trainLab/pictures/passStation.png" ;
public:
    void downloading()override;
    void unloading()override;
    PassStation(int id, int capacity, float x, float y)
            :Station(capacity){
        number = id;
        cordX = x;
        cordY = y;
        initSprite(x, y, picture);
    }
};

#endif //TRAINLAB_STATION_H
