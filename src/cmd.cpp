#include "cmd.h"

Command Cmd::Get()
{
    std::cout << prompt;
    std::cin >> std::noskipws >> command_str;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return Parse();
}

Command Cmd::Parse()
{
    command = Command::NONE;
    if(command_str == "add") command = Command::Add;
    if(command_str == "load") command = Command::Load;
    if(command_str == "save") command = Command::Save;
    if(command_str == "print") command = Command::Print;
    if(command_str == "printall") command = Command::PrintAll;
    if(command_str == "help") command = Command::Help;
    if(command_str == "exit") command = Command::Exit;
    if(command_str == "insert") command = Command::Insert;
    if(command_str == "delete") command = Command::Delete;
    if(command_str == "edit") command = Command::Edit;
    if(command_str == "sortbr") command = Command::SortByBrand;
    if(command_str == "sortcap") command = Command::SortByCapacity;
    if(command_str == "sortdist") command = Command::SortByDistance;
    if(command_str == "findbr") command = Command::FindByBrand;
    if(command_str == "findcap") command = Command::FindByCapacity;
    if(command_str == "finddist") command = Command::FindByDistance;
    if(command_str.empty()) command = Command::Skip;
    return command;
}

bool Cmd::YN(const std::string &message)
{
    std::string choice;
    Input(choice, message + " (y/n): ");
    return choice == "y";
}

void Cmd::Run(TruckDataBase &db)
{
    tp = &db;
    switch(command)
    {
        case Command::Add:
            Add();
            break;
        case Command::Load:
            Load();
            break;
        case Command::Save:
            Save();
            break;
        case Command::Print:
            Print();
            break;
        case Command::PrintAll:
            PrintAll();
            break;
        case Command::Help:
            Help();
            break;
        case Command::Insert:
            Insert();
            break;
        case Command::Delete:
            Delete();
            break;
        case Command::Edit:
            Edit();
            break;
        case Command::SortByBrand:
            SortByBrand();
            break;
        case Command::SortByCapacity:
            SortByCapacity();
            break;
        case Command::SortByDistance:
            SortByDistance();
            break;
        case Command::FindByBrand:
            FindByBrand();
            break;
        case Command::FindByCapacity:
            FindByCapacity();
            break;
        case Command::FindByDistance:
            FindByDistance();
            break;
        case Command::Exit:
        case Command::Skip:
            break;
        case Command::NONE:
            std::cout << "Unknown command '" << command_str << "'. Try 'help'.\n";
            break;
    }
}

void Cmd::Add() const
{
    tp->Add();
}

void Cmd::Load() const
{
    if(tp->list.size > 0)
    {
        if(!YN("Loading file will rewrite current list. Continue loading?"))
            return;
    }
    tp->Clear();
    try
    {
        std::string file;
        Input(file, "Path to file: ");
        tp->Load(file);
    }
    catch (const std::exception &e)
    {
        std::cout << "Error loading: " << e.what() << " Loading aborted.\n";
    }
}

void Cmd::Save() const
{
    std::string file;
    Input(file, "Path to file: ");
    if(std::filesystem::is_directory(file))
    {
        std::cout << "'" << file << "' is a directory.\n";
        return;
    }
    if(!std::filesystem::exists(file))
    {
        tp->Save(file);
        return;
    }
    std::cout << "File '" << file << "' exists already\n";
    if(!YN("Rewrite it?"))
    {
        std::cout << "Saving aborted\n";
        return;
    }
    std::cout << "Saving...\n";
    tp->Save(file);
    std::cout << "Saved\n";
}

void Cmd::Print() const
{
    if (tp->list.size == 0)
    {
        std::cout << "Nothing to print. Try 'add'.\n";
        return;
    }
    int index;
    Input(index, "Index: ");
    try
    {
        tp->Print(index, true);
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << "\n";
    }
}

void Cmd::PrintAll() const
{
    if (tp->list.size == 0)
    {
        std::cout << "Nothing to print. Try 'add'.\n";
        return;
    }
    tp->PrintAll();
}

void Cmd::Help()
{
    std::cout << "\nCommands:\n";
    std::cout << "  add - add new item in list\n";
    std::cout << "  load - load list from file\n";
    std::cout << "  save - save list in file\n";
    std::cout << "  print - print item by index\n";
    std::cout << "  printall - print all items\n";
    std::cout << "  help - see this help\n";
    std::cout << "  exit - exit program\n";
    std::cout << "  insert - insert item at a certian position in list\n";
    std::cout << "  delete - delete item by index\n";
    std::cout << "  edit - edit item by index\n";
    std::cout << "  sortbr - sort items by brand\n";
    std::cout << "  sortcap - sort items by capacity\n";
    std::cout << "  sortdist - sort items by transportation distance\n";
    std::cout << "  findbr - find items by brand\n";
    std::cout << "  findcap - find items by capacity\n";
    std::cout << "  finddist - find items by transportation distance\n\n";
}

void Cmd::Insert() const
{
    if (tp->list.size == 0)
    {
        std::cout << "You can't insert in empty list. Try 'add'.\n";
        return;
    }
    int index;
    Input(index, "Index (item will be inserted BEFORE it): ");
    try
    {
        tp->Insert(index);
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << "\n";
    }
}

void Cmd::Delete() const
{
    if (tp->list.size == 0)
    {
        std::cout << "List is empty. Try 'add'.\n";
        return;
    }
    int index;
    Input(index, "Index if item to delete: ");
    try
    {
        tp->Delete(index);
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << "\n";
    }
}

void Cmd::Edit() const
{
    if (tp->list.size == 0)
    {
        std::cout << "List is empty. Try 'add'.\n";
        return;
    }
    int index;
    Input(index, "Index if item to delete: ");
    try
    {
        tp->Edit(index);
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << "\n";
    }
}

void Cmd::SortByBrand() const
{
    auto cmp = 
    [](Truck *a, Truck *b)->bool
    {
        return a->brand > b->brand;
    };
    tp->Sort(cmp);
}

void Cmd::SortByCapacity() const
{
    auto cmp = 
    [](Truck *a, Truck *b)->bool
    {
        return a->capacity > b->capacity;
    };
    tp->Sort(cmp);
}

void Cmd::SortByDistance() const
{
    auto cmp = 
    [](Truck *a, Truck *b)->bool
    {
        return a->transportation_distance > b->transportation_distance;
    };
    tp->Sort(cmp);
}

void Cmd::FindByBrand() const
{
    std::string input;
    Input(input, "Brand value: ");
    auto fnd =
    [](Truck *a, const std::string& fld)->bool
    {
        std::stringstream ss;
        std::string target_filed;
        ss << fld;
        ss >> target_filed;
        return a->brand == target_filed;
    };
    std::string fld;
    std::stringstream ss;
    ss << input;
    ss >> fld;
    tp->Find(fnd, fld);
}

void Cmd::FindByCapacity() const
{
    float input;
    Input(input, "Capacity value: ");
    auto fnd =
    [](Truck *a, const std::string& fld)->bool
    {
        std::stringstream ss;
        float target_filed;
        ss << fld;
        ss >> target_filed;
        return a->capacity == target_filed;
    };
    std::string fld;
    std::stringstream ss;
    ss << input;
    ss >> fld;
    tp->Find(fnd, fld);
}

void Cmd::FindByDistance() const
{
    int input;
    Input(input, "Transportation distance value: ");
    auto fnd =
    [](Truck *a, const std::string& fld)->bool
    {
        std::stringstream ss;
        int target_filed;
        ss << fld;
        ss >> target_filed;
        return a->transportation_distance == target_filed;
    };
    std::string fld;
    std::stringstream ss;
    ss << input;
    ss >> fld;
    tp->Find(fnd, fld);
}
