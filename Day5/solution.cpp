#include "runner.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>

class Day5 : public Runner<std::string, std::string>
{
	struct move {
		int quantity;
		int from_crate_number;
		int to_crate_number;
	};

	using numbered_crates = std::map<int, std::vector<char>>;

	numbered_crates ncrates;
	std::vector<move> moves;

	void load() override
	{
		std::vector<std::string> crates;
		std::vector<std::string> instructions;

		bool read_crates = false;

		std::ifstream input;
		input.open("input.txt");
		std::string templine;
		while (std::getline(input, templine))
		{
			if (templine.empty()) {
				read_crates = true;
				continue;
			}

			if (read_crates)
			{
				instructions.push_back(templine);
			} 
			else
			{
				crates.push_back(templine);
			}
		}

		std::vector<size_t> crate_positions;
		const std::string& crate_number_line = crates[crates.size() - 1];
		for (int i = 0; i < crate_number_line.size(); i++)
		{
			if (std::isdigit(crate_number_line[i]))
			{
				crate_positions.push_back(i);
			}
		}

		//populate numbered crates from end to start
		for (int i = crates.size() - 2; i >= 0; i--)
		{
			for (int j = 0; j < crate_positions.size(); j++)
			{
				char letter = crates[i][crate_positions[j]];
				if (std::isalpha(letter))
				{
					ncrates[j + 1].push_back(letter);
				}
			}
		}

		for (std::string& instruction : instructions)
		{
			size_t move_index_end = instruction.find("move ") + 5;
			size_t from_index_start = instruction.find("from ");
			size_t from_index_end = from_index_start + 5;
			size_t to_index_start = instruction.find("to ");

			int quantity = std::stoi(instruction.substr(move_index_end, from_index_start - move_index_end));
			int from_crate = std::stoi(instruction.substr(from_index_end, to_index_start - from_index_end));
			int to_crate = std::stoi(instruction.substr(to_index_start + 3));

			moves.push_back({quantity, from_crate, to_crate});
		}
	}

	std::string part1() override
	{
		numbered_crates p1crates;
		p1crates.insert(ncrates.begin(), ncrates.end());

		for (move& move : moves)
		{
			for (int i = 0; i < move.quantity; i++)
			{
				std::vector<char>& numbered_crate = p1crates[move.from_crate_number];
				p1crates[move.to_crate_number].push_back(numbered_crate[numbered_crate.size() - 1]);
				numbered_crate.pop_back();
			}
		}

		return get_crates_on_top(p1crates);
	}

	std::string part2() override
	{
		numbered_crates p2crates;
		p2crates.insert(ncrates.begin(), ncrates.end());

		for (move& move : moves)
		{
			std::vector<char>& ncrate = p2crates[move.from_crate_number];
			std::vector<char>& tocrate = p2crates[move.to_crate_number];
			tocrate.insert(tocrate.end(), ncrate.end() - move.quantity, ncrate.end());
			ncrate.erase(ncrate.end() - move.quantity, ncrate.end());
		}

		return get_crates_on_top(p2crates);
	}

	std::string get_crates_on_top(numbered_crates& crates)
	{
		std::string on_top;
		for (int i = 0; i < crates.size(); i++)
		{
			std::vector<char>& numbered_crate = crates[i + 1];
			on_top.push_back(numbered_crate[numbered_crate.size() - 1]);
		}

		return on_top;
	}
};

int main()
{
	Day5().run();
	return 0;
}