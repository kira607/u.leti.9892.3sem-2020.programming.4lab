#ifndef LAB3_CMD_H
#define LAB3_CMD_H

#include <iostream>
#include <sstream>
#include <cstring>
#include <filesystem>

#include "input.h"
#include "truck_db.h"

enum Command
{
    Add,
    Load,
    Save,
    Print,
    PrintAll,
    Help,
    Exit,
    Skip,
    NONE,
};

struct Cmd
{
    Command command = Command::NONE;
    std::string command_str{};
    const std::string prompt = "LR $>";
    TruckDataBase *tp;

    Command Get();
    Command Parse();
    static bool YN(const std::string &message);
    void Run(TruckDataBase &db);

    //!Commands
    void Add() const;
    void Load() const;
    void Save() const;
    void Print() const;
    void PrintAll() const;
    static void Help();
};

#endif //LAB3_CMD_H
