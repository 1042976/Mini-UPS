//
// Created on 4/20/22.
//

#ifndef FINALPROJECT_TRUCK_H
#define FINALPROJECT_TRUCK_H

#include <string>
#include <cstdlib>
#include "Common.h"
class Truck {
public:
    static int idCounter;
    int id;
    int x;
    int y;
    std::string status;
    Truck();
    Truck(int _id);
    Truck(int _id, int _x, int _y, std::string _status);
};



#endif //FINALPROJECT_TRUCK_H
