#ifndef LAB3_TRUCK_DB_H
#define LAB3_TRUCK_DB_H

#define CSV_IO_NO_THREAD

#include <iomanip>
#include <fstream>

#include "../fast-cpp-csv-parser/csv.h"
#include "truck_list.h"
#include "input.h"

struct TruckDataBase
{
    TruckList list{};

    TruckDataBase() = default;
    void PrintAll() const;
    void Print(int index, bool print_header = false) const;
    void Add();
    void Clear();
    void Load(const std::string& db_path);
    void Save(const std::string& db_path) const;
};

#endif //LAB3_TRUCK_DB_H
