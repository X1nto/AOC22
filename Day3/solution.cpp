#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "runner.h"

class Day3 : public Runner<int, int>
{
	std::vector<std::string> rucksacks;

	void load() override
	{
		std::ifstream input;
		input.open("input.txt");
		std::string templine;
		while (std::getline(input, templine))
		{
			rucksacks.push_back(templine);
		}
		input.close();
	}

	int part1() override
	{
		int halves_priority_sum = 0;
		for (std::string& rucksack : rucksacks)
		{
			int half = rucksack.size() / 2;
			std::vector<std::string> halves {
				rucksack.substr(0, half),
				rucksack.substr(half)
			};
			halves_priority_sum += get_priority_for_matching_items(halves);
		}
		return halves_priority_sum;
	}

	int part2() override
	{
		int triples_priority_sum = 0;
		for (int i = 2; i < rucksacks.size(); i+=3)
		{
			std::vector<std::string> group_of_three {
				rucksacks[i - 2],
				rucksacks[i - 1],
				rucksacks[i]
			};
			triples_priority_sum += get_priority_for_matching_items(group_of_three);
		}
		return triples_priority_sum;
	}


	char get_matching_char(std::vector<std::string>& items)
	{
		char match = '\0';

		//sort by descending of string size in order for the first item to be the largest one
		std::sort(
			items.begin(),
			items.end(),
			[](const std::string& a, const std::string& b) { return a.size() > b.size(); }
		);

		for (int i = 0; i < items[0].size(); i++)
		{
			char inner_match = items[0][i];
			for (int j = 1; j < items.size(); j++) {
				if (items[j].find(items[0][i]) == std::string::npos)
				{
					inner_match = '\0';
					break;
				}
			}

			if (inner_match != '\0')
			{
				match = inner_match;
				break;
			}
		}

		return match;
	}

	int get_priority(char letter)
	{
		if (letter >= 65 && letter <= 90)
		{
			return letter - 65 + 27;
		} else if (letter >= 97 && letter <= 122)
		{
			return letter - 97 + 1;
		}
	}

	int get_priority_for_matching_items(std::vector<std::string>& items)
	{
		return get_priority(get_matching_char(items));
	}

};

int main()
{
	Day3().run();
	return 0;
}