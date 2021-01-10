#ifndef LAB3_TRUCK_H
#define LAB3_TRUCK_H

#include <string>

struct Truck
{
    int id;
    float capacity;
    int transportation_distance;
    std::string brand;
    Truck *prev;
    Truck *next;

    Truck();
    Truck(const Truck &truck);
};

#endif //LAB3_TRUCK_H
