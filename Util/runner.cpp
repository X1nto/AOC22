#include "runner.h"
#include <iostream>
#include <format>

std::string table = R"TABLE(
|- Output ------------------|
| Part 1      |  {}         |
| Part 2      |  {}         |
|- Time --------------------|
| Input parse |  {}ms       |
| Part 1      |  {}ms       |
| Part 2      |  {}ms       |
|---------------------------|
)TABLE";

template<typename T1, typename T2>
void Runner<T1, T2>::run()
{
	T1 part_1_output;
	T2 part_2_output;

	const runner_time load_time = measure_time([&]() { load(); });
	const runner_time part_1_time = measure_time([&]() { 
		part_1_output = run_part_1();
	});
	const runner_time part_2_time = measure_time([&]() { 
		part_2_output = run_part_2();
	});

	std::string table = std::format(
		table, 
		part_1_output,
		part_2_output,
		load_time.count(), 
		part_1_time.count(),
		part_2_time.count()
	);
}

template<typename T1, typename T2>
runner_time Runner<T1, T2>::measure_time(std::function<void()> task) const {
	auto start = runner_clock().now();
	task();
	auto end = runner_clock().now();
	return std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
}