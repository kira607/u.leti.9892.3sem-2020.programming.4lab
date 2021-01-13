#ifndef LAB3_TRUCK_LIST_H
#define LAB3_TRUCK_LIST_H

#include <iostream>
#include <sstream>

#include "truck.h"

struct TruckList
{
    Truck *head;
    Truck *tail;
    int size;

    [[nodiscard]] Truck *Get(int index) const;
    Truck *Add(const Truck &truck);
    Truck *Insert(const Truck &truck); // ToDo: implement
    void Delete(int index); // ToDo: implement
    void Free();
    void _check_index(const int &index) const;
};

#endif //LAB3_TRUCK_LIST_H
