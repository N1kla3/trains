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
    const float cordX;
    const float cordY;
    int product;
    sf::Image image;
    sf::Texture stationTexture;
    const int maxProduct;
    virtual void unloading(){std::cout << "df";};
    virtual void downloading(){std::cout << "sdfs";};
    virtual void initSprite(float x, float y);
public:
    sf::Sprite stationSprite;

    const float getX(){return cordX;}
    const float getY(){return cordY;}
    void loseTrain();
    bool haveTrain(){return hasTrain;}
    void getTrain(Train *train);
    int getNumber(){return number;}
    Station(int id, int capacity, float x, float y):maxProduct(capacity), cordY(y), cordX(x){
        number = id;
        product = maxProduct - 100;
        hasTrain = false;
        initSprite(x, y);
    }
};

class TradeStation : public Station{
private:
    const std::string picture  = "C:/Users/Kolya/CLionProjects/trainLab/pictures/passStation.png";
public:
    void downloading()override;
    void unloading()override;
    void initSprite(float x, float y)override;
    TradeStation(int id, int capacity, float x, float y):Station(id, capacity, x, y){
        initSprite(x, y);
    }
};

class PassStation : public Station{
private:
    const std::string picture = "C:/Users/Kolya/CLionProjects/trainLab/pictures/passStation.png" ;
public:
    void downloading()override;
    void unloading()override;
    void initSprite(float x, float y)override;
    PassStation(int id, int capacity, float x, float y):Station(id, capacity, x, y){
        initSprite(x, y);
    }
};

#endif //TRAINLAB_STATION_H
