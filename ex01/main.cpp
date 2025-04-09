#include "RPN.hpp"
#include <iostream>

int main(int ac, char* av[]) {
	if (ac != 2) {
		std::cerr << "Usage: ./RPN \"expression\"" << std::endl;
		return 1;
	}

	try {
		int result = RPN::evaluate(av[1]);
		std::cout << result << std::endl;
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
