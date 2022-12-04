#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "runner.h"

class Day1 : public Runner<long, long>
{
	std::vector<long> calories_per_deer {0};

	void load() override
	{
		std::ifstream input;
		input.open("input.txt");
		std::string templine;
		while (std::getline(input, templine))
		{
			if (templine.empty()) {
				calories_per_deer.push_back(0);
				continue;
			}
			const size_t last_index = calories_per_deer.size() - 1;
			calories_per_deer[last_index] = calories_per_deer[last_index] + std::stol(templine);
		}
		input.close();

		auto predicate = [](long a, long b) { return a > b; };
		std::sort(calories_per_deer.begin(), calories_per_deer.end(), predicate);
	}

	long part1() override
	{
		return sum_of(calories_per_deer, 1);
	}

	long part2() override
	{
		return sum_of(calories_per_deer, 3);
	}

	long sum_of(const std::vector<long>& elements, const int element_count)
	{
		long sum = 0;
		for (size_t i = 0; i < element_count; i++)
		{
			sum += elements[i];
		}
		return sum;
	}
};

int main()
{
	Day1().run();
	return 0;
}