#include "PmergeMe.hpp"
#include <iostream>
#include <algorithm>
#include <ctime>

PmergeMe::PmergeMe() {}
PmergeMe::~PmergeMe() {}

void PmergeMe::sortAndPrint(const std::vector<int>& input) {
	std::cout << "\033[31mBefore: \033[0m";
	for (std::size_t i = 0; i < input.size(); ++i)
		std::cout << input[i] << " ";
	std::cout << std::endl;

	std::vector<int> vec(input.begin(), input.end());
	std::deque<int> deq(input.begin(), input.end());

	clock_t startVec = clock();
	fordJohnson(vec);
	clock_t endVec = clock();

	clock_t startDeq = clock();
	fordJohnson(deq);
	clock_t endDeq = clock();

	std::cout << "\033[32mAfter: \033[0m";
	for (std::size_t i = 0; i < vec.size(); ++i)
		std::cout << vec[i] << " ";
	std::cout << std::endl;

	double timeVec = static_cast<double>(endVec - startVec) / CLOCKS_PER_SEC * 1000000.0;
	double timeDeq = static_cast<double>(endDeq - startDeq) / CLOCKS_PER_SEC * 1000000.0;

	std::cout << "Time to process a range of " << vec.size()
	          << " elements with std::vector : " << timeVec << " us" << std::endl;
	std::cout << "Time to process a range of " << deq.size()
	          << " elements with std::deque  : " << timeDeq << " us" << std::endl;
}

template<typename T>
void PmergeMe::binaryInsert(T& container, const typename T::value_type& val) {
	typename T::iterator it = container.begin();
	typename T::iterator end = container.end();
	while (it != end && *it < val)
		++it;
	container.insert(it, val);
}

void PmergeMe::fordJohnson(std::vector<int>& data) {
	if (data.size() <= 1) return;

	std::vector<int> winners;
	std::vector<int> losers;

	for (std::size_t i = 0; i + 1 < data.size(); i += 2) {
		if (data[i] > data[i + 1]) {
			winners.push_back(data[i]);
			losers.push_back(data[i + 1]);
		} else {
			winners.push_back(data[i + 1]);
			losers.push_back(data[i]);
		}
	}

	if (data.size() % 2 != 0)
		losers.push_back(data.back());

	fordJohnson(winners);

	data = winners;
	for (std::size_t i = 0; i < losers.size(); ++i)
		binaryInsert(data, losers[i]);
}

void PmergeMe::fordJohnson(std::deque<int>& data) {
	if (data.size() <= 1) return;

	std::deque<int> winners;
	std::deque<int> losers;

	for (std::size_t i = 0; i + 1 < data.size(); i += 2) {
		if (data[i] > data[i + 1]) {
			winners.push_back(data[i]);
			losers.push_back(data[i + 1]);
		} else {
			winners.push_back(data[i + 1]);
			losers.push_back(data[i]);
		}
	}

	if (data.size() % 2 != 0)
		losers.push_back(data.back());

	fordJohnson(winners);

	data = winners;
	for (std::size_t i = 0; i < losers.size(); ++i)
		binaryInsert(data, losers[i]);
}
