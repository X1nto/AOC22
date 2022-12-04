#pragma once

#include <chrono>
#include <functional>
#include <string>
#include <format>
#include <iostream>

template<typename T1, typename T2>
class Runner
{
private:
	using runner_clock = std::chrono::high_resolution_clock;
	using runner_time = std::chrono::milliseconds;

	virtual void load() = 0;
	virtual T1 part1() = 0;
	virtual T2 part2() = 0;

	runner_time measure_task_time(std::function<void()> task)
	{
		auto start = runner_clock().now();
		task();
		auto end = runner_clock().now();
		return std::chrono::duration_cast<runner_time>(end - start);
	};

public:
	void run()
	{
		T1 part1_result;
		T2 part2_result;

		const runner_time load_time = measure_task_time([&]() { load(); });
		const runner_time part1_time = measure_task_time([&]() { part1_result = part1(); });
		const runner_time part2_time = measure_task_time([&]() { part2_result = part2(); });

		std::cout << std::format(
R"TABLE(|-----------------------|
|- Output --------------|
|-----------------------|
|  Part 1  |  {:8}  |
|  Part 2  |  {:8}  |
|-----------------------|
|- Time ----------------|
|-----------------------|
|  Input   |  {:6}ms  |
|  Part 1  |  {:6}ms  |
|  Part 2  |  {:6}ms  |
|-----------------------|)TABLE",
			part1_result,
			part2_result,
			load_time.count(),
			part1_time.count(),
			part2_time.count()
		);
	};
};