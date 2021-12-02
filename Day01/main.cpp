#include <iostream>
#include <stack>
#include <fstream>
#include <string>
#include <vector>

int A()
{
	std::stack<int> depths;
	int larger = 0;

	int measurement;

	std::ifstream input;
	input.open("input");

	std::string line;
	std::getline(input, line);
	measurement = std::stoi(line);
	depths.push(measurement);

	bool read = input.good();
	while (read)
	{
		std::getline(input, line);
		if (line.empty() || !input.good())
		{
			read = false;
		}
		else
		{
			measurement = std::stoi(line);
			if (measurement > depths.top())
			{
				++larger;
			}
			depths.push(measurement);
		}
	}

	return larger;
}

int getWindowSum(std::vector<int> collection, int window, int offset)
{
	int windowSum = 0;
	for (int i = 1; i <= window; i++)
	{
		windowSum += collection[collection.size() - (i + offset)];
	}
	return windowSum;
}

int B()
{
	std::vector<int> depths;
	int larger = 0;
	int window = 3;

	int measurement;

	std::ifstream input;
	input.open("input");
	std::string line;

	for (int i = 0; i < window + 1; i++)
	{
		std::getline(input, line);
		measurement = std::stoi(line);
		depths.push_back(measurement);
	}

	bool read = input.good();
	while (read)
	{
		int windowSumA = getWindowSum(depths, window, 1);
		int windowSumB = getWindowSum(depths, window, 0);

		if (windowSumB > windowSumA)
		{
			++larger;
		}

		std::getline(input, line);
		if (line.empty() || !input.good())
		{
			read = false;
		}
		else
		{
			measurement = std::stoi(line);
			depths.push_back(measurement);
		}
	}

	return larger;
}

int main()
{
	int a = A();
	int b = B();

	std::cout << "A: " << a << std::endl
		<< "B: " << b << std::endl;

	return 0;
}