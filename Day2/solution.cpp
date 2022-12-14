#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <map>
#include "runner.h"

class Day2 : public Runner<int, int>
{
	enum struct letter {
		AX,
		BY,
		CZ
	};
	enum struct shape {
		rock = 1,
		paper = 2,
		scissors = 3,
	};
	enum struct result {
		loss = 0,
		draw = 3,
		win = 6,
	};

	std::map<shape, shape> win_map {
		{ shape::rock, shape::scissors },
		{ shape::paper, shape::rock },
		{ shape::scissors, shape::paper }
	};
	std::map<shape, shape> loss_map {
		{ shape::rock, shape::paper },
		{ shape::paper, shape::scissors },
		{ shape::scissors, shape::rock }
	};

	std::vector<std::pair<letter, letter>> rounds;

	void load() override
	{
		std::ifstream input;
		input.open("input.txt");
		std::string templine;
		while (std::getline(input, templine))
		{
			letter opponent = get_letter_for_letterchar(templine[0]);
			letter you = get_letter_for_letterchar(templine[2]);
			rounds.push_back(std::make_pair(opponent, you));
		}
		input.close();
	}

	int part1() override
	{
		int score_actual = 0;
		for (auto& round : rounds)
		{
			shape opponent = get_shape_for_letter(round.first);
			shape you = get_shape_for_letter(round.second);
			score_actual += get_round_score(opponent, you);
		}
		return score_actual;
	}

	int part2() override
	{
		int score_desired = 0;
		for (auto& round : rounds)
		{
			result desired_result = get_result_for_letter(round.second);
			shape opponent = get_shape_for_letter(round.first);
			shape you = get_shape_for_result_comply(opponent, desired_result);
			score_desired += get_round_score(opponent, you);
		}
		return score_desired;
	}

	letter get_letter_for_letterchar(char letter)
	{
		switch (letter)
		{
		case 'A':
		case 'X':
			return letter::AX;
		case 'B':
		case 'Y':
			return letter::BY;
		case 'C':
		case 'Z':
			return letter::CZ;
		}
	}

	shape get_shape_for_letter(letter& letter)
	{
		switch (letter)
		{
		case letter::AX:
			return shape::rock;
		case letter::BY:
			return shape::paper;
		case letter::CZ:
			return shape::scissors;
		}
	}

	result get_result_for_letter(letter& letter)
	{
		switch (letter)
		{
		case letter::AX:
			return result::loss;
		case letter::BY:
			return result::draw;
		case letter::CZ:
			return result::win;
		}
	};

	result get_round_result(shape& opponent, shape& you)
	{
		if (opponent == you)
		{
			return result::draw;
		} else if (win_map[you] == opponent)
		{
			return result::win;
		} else {
			return result::loss;
		}
	}

	shape get_shape_for_result_comply(shape& opponent, result& desired)
	{
		switch (desired)
		{
		case result::win:
			return loss_map[opponent];
		case result::loss:
			return win_map[opponent];
		case result::draw:
			return opponent;
		}
	}

	int get_round_score(shape opponent, shape you) {
		result round_result = get_round_result(opponent, you);
		return static_cast<int>(you) + static_cast<int>(round_result);
	}
};

int main()
{
	Day2().run();
	return 0;
}