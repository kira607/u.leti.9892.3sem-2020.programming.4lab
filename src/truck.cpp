#include "truck.h"

Truck::Truck()
{
    id = -1;
    brand = "";
    capacity = 0.f;
    transportation_distance = 0;
    prev = nullptr;
    next = nullptr;
}

Truck::Truck(const Truck &truck)
{
    id = truck.id;
    brand = truck.brand;
    capacity = truck.capacity;
    transportation_distance = truck.transportation_distance;
    prev = nullptr;
    next = nullptr;
}