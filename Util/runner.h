#pragma once

#include <chrono>
#include <functional>
#include <string>
#include <iostream>
#include <iomanip>

template<typename T1, typename T2>
class Runner
{
private:
	using runner_clock = std::chrono::high_resolution_clock;
	using runner_time = std::chrono::milliseconds;

	virtual void load() = 0;
	virtual T1 part1() = 0;
	virtual T2 part2() = 0;

	std::string measure_task_time(std::function<void()> task) const
	{
		auto start = runner_clock().now();
		task();
		auto end = runner_clock().now();
		runner_time time = std::chrono::duration_cast<runner_time>(end - start);
		return std::to_string(time.count()) + "ms";
	};

	template <typename... T>
	int get_table_width(T&... values) const
	{
		int width = 0;
		([&]
		{
			int value_width = static_cast<int>(values.size());
		if (value_width > width)
		{
			width = value_width;
		}
		} (), ...);
		return width;
	}

	std::string get_padded_string(int padding, const std::string& string) const
	{
		size_t str_size = string.size();
		if (str_size < padding)
		{
			std::string new_str(padding - str_size, ' ');
			new_str += string;
			return new_str;
		}
		else
		{
			return string;
		}
	}

	template<typename T>
	std::string get_value_string(const T& value) const
	{
		std::stringstream value_string;
		value_string << value;
		return value_string.str();
	}


public:
	void run()
	{
		T1 part1_result;
		T2 part2_result;

		const std::string load_time_str = measure_task_time([&]() { load(); });
		const std::string part1_time_str = measure_task_time([&]() { part1_result = part1(); });
		const std::string part2_time_str = measure_task_time([&]() { part2_result = part2(); });
		const std::string part1_result_str = get_value_string(part1_result);
		const std::string part2_result_str = get_value_string(part2_result);

		const int table_width = get_table_width(
			part1_result_str,
			part2_result_str,
			load_time_str,
			part1_time_str,
			part2_time_str
		);
		const std::string outline = std::string(table_width, '-') + "--|";

		std::cout << "|-------------" << outline << '\n';
		std::cout << "|- Output ----" << outline << '\n';
		std::cout << "|-------------" << outline << '\n';
		std::cout << "|  Part 1  |  " << get_padded_string(table_width, part1_result_str) << "  |" << '\n';
		std::cout << "|  Part 2  |  " << get_padded_string(table_width, part2_result_str) << "  |" << '\n';
		std::cout << "|-------------" << outline << '\n';
		std::cout << "|- Time ------" << outline << '\n';
		std::cout << "|-------------" << outline << '\n';
		std::cout << "|  Input   |  " << get_padded_string(table_width, load_time_str) << "  |" << '\n';
		std::cout << "|  Part 1  |  " << get_padded_string(table_width, part1_time_str) << "  |" << '\n';
		std::cout << "|  Part 2  |  " << get_padded_string(table_width, part2_time_str) << "  |" << '\n';
		std::cout << "|-------------" << outline << '\n';
	}
};