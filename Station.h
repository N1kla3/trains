//
// Created by Kolya on 10/17/2019.
//

#ifndef TRAINLAB_STATION_H
#define TRAINLAB_STATION_H

#include "Train.h"

class Station {
private:
    const std::string picture = "C:/Users/Kolya/CLionProjects/trainLab/pictures/fork.png";
protected:
    int type;
    bool hasTrain;
    int number;
    float cordX;
    float cordY;
    int product;
    const int maxProduct;
    sf::Image image;
    sf::Texture stationTexture;
    virtual void unloading(Train *train) {std::cout << "it is not a station";};
    virtual void downloading(Train *train) {std::cout << "it is not a station";};
    virtual void initSprite(float x, float y, std::string picturePath);
    Station(int capacity) : maxProduct(capacity) {
        product = maxProduct - 100;
        hasTrain = false;
    }
public:
    sf::Sprite stationSprite;

    float getX(){return cordX;}
    float getY(){return cordY;}
    int getType(){return type;}
    int getProduct(){return product;}
    int getMaxProduct(){return maxProduct;}
    void loseTrain();
    void getTrain();
    virtual void handleTrain(Train *train);
    bool haveTrain(){return hasTrain;}
    int getNumber(){return number;}
    Station(int type, int id, int capacity, float x, float y)
            :type(type), maxProduct(capacity), cordY(y), cordX(x){
        number = id;
        product = maxProduct - 100;
        hasTrain = false;
        initSprite(x, y, picture);
    }
};

class TradeStation : public Station{
private:
    const std::string picture  = "C:/Users/Kolya/CLionProjects/trainLab/pictures/tradeStation.png";
public:
    void downloading(Train *train) override;
    void unloading(Train *train) override;
    void handleTrain(Train *train)override;
    TradeStation(int type, int id, int capacity, float x, float y)
            :Station(capacity){
        this->type = type;
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
    void downloading(Train *train) override;
    void unloading(Train *train) override;
    void handleTrain(Train *train)override;
    PassStation(int type, int id, int capacity, float x, float y)
            :Station(capacity){
        this->type = type;
        number = id;
        cordX = x;
        cordY = y;
        initSprite(x, y, picture);
    }
};

#endif //TRAINLAB_STATION_H
