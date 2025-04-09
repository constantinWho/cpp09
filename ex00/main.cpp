#include "BitcoinExchange.hpp"
#include <iostream>

int main(int ac, char *av[]) {

	if (ac != 2) {
		std::cerr << "Error: invalid arguments.\n"
			<< "Usage: ./btc <file>" << std::endl;
		return 1;
	}

	BitcoinExchange btc;
	btc.loadDB("data.csv");
	btc.processInput(av[1]);

	return 0;
}
