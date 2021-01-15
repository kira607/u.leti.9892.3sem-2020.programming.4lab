#include "truck_list.h"

TruckList::TruckList()
{
    head = nullptr;
    tail = nullptr;
    size = 0;
}

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

Truck *TruckList::Insert(const Truck &truck, int index)
{
    _check_index(index);
    auto new_node = new Truck(truck);
    auto target_node = Get(index);

    if(index == 0)
    {
        new_node->next = target_node;
        new_node->prev = nullptr;
        target_node->prev = new_node;
        head = new_node;
    }
    else 
    {
        new_node->next = target_node;
        new_node->prev = target_node->prev;
        target_node->prev = new_node;
        new_node->prev->next = new_node;
    }

    ++size;
    return new_node;
}

void TruckList::Delete(int index)
{
    _check_index(index);

    if(size == 1 && index == 0)
    {
        Free();
        return;
    }

    if(index == 0)
    {
        Truck *new_head = head->next;
        delete head;
        head = new_head;
        head->prev = nullptr;
        --size;
        return;
    }

    if(index == size - 1)
    {
        Truck *new_tail = tail->prev;
        delete tail;
        tail = new_tail;
        tail->next = nullptr;
        --size;
        return;
    }

    auto p = Get(index);

    if (!p)
    {
        return;
    }

    p->next->prev = p->prev;
    p->prev->next = p->next;
    delete p;
    --size;
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