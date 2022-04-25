//
// Created on 4/20/22.
//
#include "Truck.h"

int Truck::idCounter = TRUCK_START_ID;


Truck::Truck():status("idle") {
    id = idCounter++;
    x = std::rand()%21-10;
    y = std::rand()%21-10;
}

Truck::Truck(int _id): id(_id), x(0), y(0), status("") {}

Truck::Truck(int _id, int _x, int _y, std::string _status):id(_id), x(_x), y(_y), status(_status) {}
