#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <iomanip>

class BitcoinExchange {

	private:
		std::map<std::string, float>		_btcDB;
		BitcoinExchange(const BitcoinExchange& btcEx);
		BitcoinExchange& operator=(const BitcoinExchange& other);

	public:
		BitcoinExchange();
		~BitcoinExchange();

		void	loadDB(const std::string& db);
		void	processInput(const std::string& input);
};

#endif
