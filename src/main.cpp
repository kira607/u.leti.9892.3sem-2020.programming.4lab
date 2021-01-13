#include "cmd.h"

int main()
{
    TruckDataBase db{};
    Command command;
    Cmd cmd;
    db.Load("../build/t");
    db.PrintAll();
    cmd.SortByDistance();
    return 111;
    //cmd.Help();
    
    do
    {
        command = cmd.Get();
        cmd.Run(db);
    } while(command != Command::Exit);

    db.Clear();
    return 0;
}