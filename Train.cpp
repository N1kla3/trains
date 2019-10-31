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

Train::Train(int trade, int passenger, int stationId) : number(stationId) {
    for(int i = 0; i < trade; i++){
        Carriage carr(TRADE);
        carriages.push_back(carr);
    }

    for(int i = 0; i < passenger; i++){
        Carriage carr(PASSENGER);
        carriages.push_back(carr);
    }

    for(Carriage carr : carriages){
        maxPassengerCapacity += carr.passengerCapacity;
        maxTradeCapacity += carr.tradeCapacity;
    }
}

float Train::getMovespeed() {
    return 100 - ((float)curentCapacity / 30);
}