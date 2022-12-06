#include "runner.h"
#include <vector>
#include <string>
#include <fstream>

class Day6 : public Runner<int, int>
{
	std::string stream;
	
	void load() override
	{
		std::ifstream input;
		input.open("input.txt");
		std::string templine;
		while (std::getline(input, templine))
		{
			stream = templine;
		}
		input.close();
	};

	int part1() override
	{
		return get_start_of_unique_string(4);
	}

	int part2() override
	{
		return get_start_of_unique_string(14);
	}

	int get_start_of_unique_string(const int char_count) const
	{
		int start = 0;
		std::string temp;
		for (int i = 0; i < stream.size(); i++)
		{
			if (temp.size() < char_count)
			{
				size_t existing_pos = temp.find(stream[i]);
				if (existing_pos != std::string::npos)
				{
					temp.erase(temp.begin(), temp.begin() + existing_pos + 1);
				}
				temp.push_back(stream[i]);
			} else
			{
				start = i;
				break;
			}
		}
		return start;
	}

};

int main()
{
	Day6().run();
	return 0;
}