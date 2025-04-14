#include "PmergeMe.hpp"
#include <iostream>
#include <sstream>
#include <ctime>

int main(int ac, char** av) {
	if (ac < 2) {
		std::cerr << "Usage: ./PmergeMe <positive integers>" << std::endl;
		return 1;
	}

	try {
		std::vector<int> input;
		for (int i = 1; i < ac; ++i) {
			std::istringstream ss(av[i]);
			int num;
			if (!(ss >> num) || num < 0)
				throw std::invalid_argument("Invalid input");
			input.push_back(num);
		}

		PmergeMe sorter;
		sorter.sortAndPrint(input);
	} catch (std::exception& e) {
		std::cerr << "Error" << std::endl;
		return 1;
	}

	return 0;
}
