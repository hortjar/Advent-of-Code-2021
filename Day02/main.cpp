#include <iostream>
#include <fstream>
#include <string>

int A()
{
    std::ifstream input;
    input.open("input");

    int horizontal = 0;
    int depth = 0;

    std::string line;
    while (input.good())
    {
        std::getline(input, line);
        if (line.empty())
        {
            break;
        }

        std::string command = line.substr(0, line.find(" "));
        std::string valueStr = line.substr(line.find(" ") + 1, line.length());

        int value = std::stoi(valueStr);

        if (command == "forward")
        {
            horizontal += value;
        }
        else if (command == "down")
        {
            depth += value;
        }
        else if (command == "up")
        {
            depth -= value;
        }
    }

    return horizontal * depth;
}

int B()
{
    std::ifstream input;
    input.open("input");

    int horizontal = 0;
    int depth = 0;
    int aim = 0;

    std::string line;
    while (input.good())
    {
        std::getline(input, line);
        if (line.empty())
        {
            break;
        }

        std::string command = line.substr(0, line.find(" "));
        std::string valueStr = line.substr(line.find(" ") + 1, line.length());

        int value = std::stoi(valueStr);

        if (command == "forward")
        {
            horizontal += value;
            depth += (aim * value);
        }
        else if (command == "down")
        {
            aim += value;
        }
        else if (command == "up")
        {
            aim -= value;
        }
    }

    return horizontal * depth;
}

int main()
{
    int a = A();
    int b = B();

    std::cout << "A: " << a << std::endl
        << "B: " << b << std::endl;
}