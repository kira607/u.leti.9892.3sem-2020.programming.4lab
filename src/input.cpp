#include "input.h"

int Input(int &element, const std::string& message, int l, int r)
{
    bool input = true;
    while (input)
    {
        std::cout << message;
        std::cin >> element;
        if (std::cin.fail() || (element < l || element > r))
            std::cout << "Wrong input!\n";
        else
            input = false;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return element;
}

float Input(float &element, const std::string& message, float l, float r)
{
    bool input = true;
    while (input)
    {
        std::cout << message;
        std::cin >> element;
        if (std::cin.fail() || (element < l || element > r))
            std::cout << "Wrong input!\n";
        else
            input = false;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return element;
}

std::string Input(std::string &element, const std::string &message)
{
    bool input = true;
    while (input)
    {
        std::cout << message;
        std::cin >> element;
        if (std::cin.fail())
            std::cout << "Wrong input!\n";
        else
            input = false;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return element;
}
