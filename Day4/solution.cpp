#include <string>
#include <iostream>
#include <fstream>
#include <utility>

using room_ranges = std::pair<int, int>;
using deer_pair = std::pair<room_ranges, room_ranges>;

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

int main()
{
	int fully_covered = 0;
	int overlapped = 0;

	std::ifstream input;
	input.open("input.txt");
	std::string templine;
	while (std::getline(input, templine))
	{
		const deer_pair assignments = get_deer_pair(templine);
		fully_covered += rooms_cover(assignments);
		overlapped += rooms_overlap(assignments);
	}
	input.close();

	std::cout << "Part 1: " << fully_covered << '\n';
	std::cout << "Part 2: " << overlapped << '\n';

	return 0;
}