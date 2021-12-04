#include <iostream>
#include <stack>
#include <fstream>
#include <string>
#include <vector>
#include <ios>
#include <stdio.h>


void print_binary(unsigned int number)
{
    if (number >> 1)
    {
        print_binary(number >> 1);
    }
    putc((number & 1) ? '1' : '0', stdout);
}

int A()
{
    std::ifstream input;
    input.open("input");

    int ones = 0;
    int zeros = 0;

    int gamma = 0;
    int epsilon = 0;

    int power = 0;

    std::string line;
    unsigned long number;
    bool readAll = false;
    std::streampos inputStart = input.tellg();
    int col = 0;

    while (!readAll)
    {
        input.clear();
        input.seekg(0, std::ios::beg);

        ones = 0;
        zeros = 0;
        while (input.good())
        {
            std::getline(input, line);
            if (line.empty())
            {
                break;
            }

            if (line.length() == col)
            {
                readAll = true;
                break;
            }

            char bit = line[col];

            if (bit == '0')
            {
                ++zeros;
            }
            else if (bit == '1')
            {
                ++ones;
            }
        }

        if (readAll)
        {
            break;
        }

        ++col;

        gamma <<= 1;
        epsilon <<= 1;
        if (ones > zeros)
        {
            gamma |= 1;
        }
        else
        {
            epsilon |= 1;
        }

    }

    return gamma * epsilon;
}

bool getSignificantNumber(std::vector<std::string> input, int col)
{
    int zeroes = 0;
    int ones = 0;
    for (auto& line : input)
    {
        char bit = line[col];

        if (bit == '0')
        {
            ++zeroes;
        }
        else if (bit == '1')
        {
            ++ones;
        }
    }
    return ones >= zeroes;
}

int B()
{
    // read all first
    std::ifstream input;
    input.open("input");

    std::vector<std::string> lines;
    std::string line;
    int cols = 0;

    while (input.good())
    {
        std::getline(input, line);
        if (line.empty())
        {
            break;
        }
        cols = line.length();
        lines.push_back(line);
    }

    std::vector<std::string> oxygenRatingNumbers;
    std::vector<std::string> co2RatingNumbers;
    std::vector<std::string> backupOxygen;
    std::vector<std::string> backupCo2;

    int zeroes = 0;
    int ones = 0;
    for (int col = 0; col < cols; col++)
    {
        // most siginificant bit
        bool significantOxygen = getSignificantNumber(col == 0 ? lines : oxygenRatingNumbers, col);
        bool significantCo2 = getSignificantNumber(col == 0 ? lines : co2RatingNumbers, col);

        // filter 
        backupOxygen = col == 0 ? lines : oxygenRatingNumbers;
        if (backupOxygen.size() > 1)
        {
            oxygenRatingNumbers.clear();
            for (auto& line : backupOxygen)
            {
                char bit = line[col];

                if ((significantOxygen && bit == '1') || (!significantOxygen && bit == '0'))
                {
                    oxygenRatingNumbers.push_back(line);
                }
            }
        }

        backupCo2 = col == 0 ? lines : co2RatingNumbers;
        if (backupCo2.size() > 1)
        {
            co2RatingNumbers.clear();
            for (auto& line : backupCo2)
            {
                char bit = line[col];

                if ((!significantCo2 && bit == '1') || (significantCo2 && bit == '0'))
                {
                    co2RatingNumbers.push_back(line);
                }
            }
        }
    }

    int oxygen = std::stoi(oxygenRatingNumbers.front(), nullptr, 2);
    int co2 = std::stoi(co2RatingNumbers.front(), nullptr, 2);

    return oxygen * co2;
}

int main()
{
    int a = A();
    int b = B();

    std::cout << "A: " << a << std::endl
        << "B: " << b << std::endl;

    return 0;
}