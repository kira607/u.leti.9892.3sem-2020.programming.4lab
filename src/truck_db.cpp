#include "truck_db.h"

void TruckDataBase::PrintAll() const
{
    std::cout << std::left
              << std::setw(4)  << "id "
              << std::setw(14) << "brand "
              << std::setw(10)  << "capacity "
              << std::setw(5)  << "transportation_distance\n";
    for(int i = 0; i < list.size; ++i)
    {
        Print(i);
    }
}

void TruckDataBase::Print(int index, bool print_header) const
{
    list._check_index(index);
    auto p = list.Get(index);
    if(print_header)
    {
        std::cout << std::left
                  << std::setw(4) << "id "
                  << std::setw(14) << "brand "
                  << std::setw(10) << "capacity "
                  << std::setw(5) << "transportation_distance\n";
    }
    std::cout << std::left
              << std::setw(3)  << p-> id << " "
              << std::setw(13) << p->brand << " "
              << std::setw(9)  << p->capacity << " "
              << std::setw(5)  << p->transportation_distance << "\n";
}

void TruckDataBase::Add()
{
    Truck new_element;
    new_element.id = list.size > 0 ? list.Get(list.size-1)->id + 1 : 0;
    Input(new_element.brand, "brand: ");
    Input(new_element.capacity, "capacity: ");
    Input(new_element.transportation_distance, "transportation distance: ");
    list.Add(new_element);
}

void TruckDataBase::Clear()
{
    list.Free();
}

void TruckDataBase::Load(const std::string& db_path)
{
    Truck truck{};

    io::CSVReader<4> in(db_path);
    in.read_header(io::ignore_extra_column, "id", "brand", "capacity", "transportation_distance");
    while(in.read_row(truck.id, truck.brand, truck.capacity, truck.transportation_distance))
    {
        list.Add(truck);
    }
}

void TruckDataBase::Save(const std::string& db_path) const
{
    std::ofstream fout(db_path, std::ios_base::trunc);
    fout << "id,brand,capacity,transportation_distance\n";

    Truck *p = list.head;
    while(p)
    {
        fout << p->id << ","
             << p->brand << ","
             << p->capacity << ","
             << p->transportation_distance;
        fout << "\n";
        p = p->next;
    }
}

void TruckDataBase::Find(bool(*fnd)(Truck* t, const std::string &fld), const std::string &fld)
{
    auto e = list.head;
    int index = 0;
    int count = 0;
    while(e)
    {
        if(fnd(e, fld))
        {
            Print(index, count == 0);
            ++count;
        }
        e = e->next;
        ++index;
    }
    std::cout << "Found " << count << " items." << std::endl;
}

void TruckDataBase::Sort(bool(*gt)(Truck*, Truck*))
{
    _qsort(gt, list.head, list.tail);
}

/*
@breif: Quick Sort implementation
*/
void TruckDataBase::_qsort(bool(*gt)(Truck*, Truck*), Truck *left, Truck *right)
{
    if(right != nullptr && right != left && left != right->next)
    {
        Truck *mid = _partition(gt, left, right);
        _qsort(gt, left, mid->prev);
        _qsort(gt, mid->next, right);
    }
}

/*
@breif: Splits list in two parts and returns index of pivot
*/
Truck *TruckDataBase::_partition(bool(*gt)(Truck*, Truck*), Truck *left, Truck *right)
{
    Truck *pivot = new Truck(*right);
    Truck *smallest_i = left->prev;
    for(auto current_j = left; current_j != right; current_j = current_j->next)
    {
        if(!gt(current_j, pivot))
        {
            smallest_i = (smallest_i == nullptr) ? left : smallest_i->next;
            _swap(smallest_i, current_j);
        }
    }
    smallest_i = (smallest_i == nullptr) ? left : smallest_i->next;
    _swap(smallest_i, right);
    delete pivot;
    return smallest_i;
}

void TruckDataBase::_swap(Truck *a, Truck *b)
{   
    std::string brand = a->brand;
    a->brand = b->brand;
    b->brand = brand;

    float cap = a->capacity;
    a->capacity = b->capacity;
    b->capacity = cap;

    int dist = a->transportation_distance;
    a->transportation_distance = b->transportation_distance;
    b->transportation_distance = dist;
}



