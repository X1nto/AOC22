#include <string>
#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include "runner.h"

class Day4 : public Runner<int, int>
{
	using room_ranges = std::pair<int, int>;
	using deer_pair = std::pair<room_ranges, room_ranges>;
	std::vector<deer_pair> deer_pairs;

	void load() override
	{
		std::ifstream input;
		input.open("input.txt");
		std::string templine;
		while (std::getline(input, templine))
		{
			deer_pairs.push_back(get_deer_pair(templine));
		}
		input.close();
	}

	int part1() override
	{
		int fully_covered = 0;
		for (deer_pair& deer_pair : deer_pairs)
		{
			fully_covered += rooms_cover(deer_pair);
		}
		return fully_covered;
	};

	int part2() override
	{
		int overlapped = 0;
		for (deer_pair& deer_pair : deer_pairs)
		{
			overlapped += rooms_overlap(deer_pair);
		}
		return overlapped;
	}

	room_ranges get_room_ranges(const std::string& assignment)
	{
		const size_t divider_pos = assignment.find('-');

		const int first_room = std::stoi(assignment.substr(0, divider_pos));
		const int second_room = std::stoi(assignment.substr(divider_pos + 1));

		return room_ranges {first_room, second_room};
	}

	deer_pair get_deer_pair(const std::string& input)
	{
		const size_t comma_pos = input.find(',');

		const room_ranges first_pair = get_room_ranges(input.substr(0, comma_pos));
		const room_ranges second_pair = get_room_ranges(input.substr(comma_pos + 1));

		return deer_pair {first_pair, second_pair};
	}

	bool rooms_cover(const deer_pair& deers)
	{
		return
			(deers.second.first >= deers.first.first &&
				deers.second.second <= deers.first.second) ||
			(deers.first.first >= deers.second.first &&
				deers.first.second <= deers.second.second);
	}

	bool rooms_overlap(const deer_pair& deers)
	{
		return deers.first.first <= deers.second.second &&
			deers.second.first <= deers.first.second;
	}

};

int main()
{
	Day4().run();
	return 0;
}