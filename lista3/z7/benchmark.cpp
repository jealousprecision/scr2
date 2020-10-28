#include <iostream>
#include <chrono>
#include <algorithm>
#include <vector>
#include <ctime>
#include <future>

constexpr std::size_t kLen = 10000;

auto getTask()
{
	return []() -> double
		{
			using us = std::chrono::microseconds;
			using clock = std::chrono::high_resolution_clock;

			std::vector<int> vec(kLen);

			for (int& el : vec)
				el = std::rand();

			auto start = clock::now();
			std::sort(vec.begin(), vec.end());
			auto end = clock::now();

			return std::chrono::duration_cast<us>(end - start).count() / 1000.0;
		};
}

/*
int main(int argc, char** argv)
{
	std::srand(std::time(nullptr));
	std::vector<std::future<double>> futures;

	for (int i = 0; i < 10; ++i)
		futures.push_back(std::async(getTask()));

	double avgMs = 0;
	for (auto& future : futures)
		avgMs += future.get() / futures.size();

	std::cout << "avg: " << avgMs << " ms" << std::endl;
}
*/

int main()
{
	constexpr int kNo = 10000;

	double avgMs = 0;
	for (int i = 0; i < kNo; ++i)
		avgMs += getTask()() / kNo;

	std::cout << "avg: " << avgMs << std::endl;
}
