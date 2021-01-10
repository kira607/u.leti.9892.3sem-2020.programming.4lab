#include "truck_list.h"

Truck *TruckList::Get(int index) const
{
    _check_index(index);

    auto p = head;
    for(int i = 0; i < index; ++i)
    {
        if(p->next)
            p = p->next;
        else
            return nullptr;
    }
    return p;
}

Truck *TruckList::Add(const Truck &truck)
{
    auto *new_node = new Truck(truck);

    if (size == 0)
    {
        head = new_node;
        tail = new_node;
        new_node->prev = nullptr;
        new_node->next = nullptr;
    }
    else
    {
        new_node->prev = tail;
        new_node->prev->next = new_node;
        new_node->next = nullptr;
        tail = new_node;
    }

    ++size;
    return new_node;
}

void TruckList::Free()
{
    Truck *p = head;
    while(p != nullptr)
    {
        Truck *next = p->next;
        delete p;
        p = next;
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
}

void TruckList::_check_index(const int &index) const
{
    if (index < 0 || index >= size)
    {
        std::stringstream message;
        message << "Index out of range (possible [0-" << size-1 << "], given " << index << ")";
        throw std::out_of_range(message.str().c_str());
    }
}