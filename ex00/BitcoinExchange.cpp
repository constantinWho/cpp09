#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}
BitcoinExchange::~BitcoinExchange() {}
BitcoinExchange::BitcoinExchange(const BitcoinExchange& btcEx) { *this = btcEx; }
BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
	if (this != &other)
		_btcDB = other._btcDB;
	return *this;
}

void	BitcoinExchange::loadDB(const std::string& db) {

	std::ifstream dbFile(db.c_str());
	if (!dbFile.is_open()) {
		std::cerr << "Error: could not open the db file." << std::endl;
		return;
	}

	std::string line;
	std::getline(dbFile, line);

	while (std::getline(dbFile, line)) {
		std::istringstream ss(line);
		std::string date, price;

		if (!std::getline(ss, date, ',') || !std::getline(ss, price)) {
			std::cerr << "Erorr: wrong db format: " << line << std::endl;
			continue;
		}

		float value = std::strtof(price.c_str(), NULL);
		_btcDB[date] = value;
	}

	dbFile.close();
}

bool BitcoinExchange::isValidDate(const std::string& date) {
	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
		return false;

	int y, m, d;
	char dash1, dash2;
	std::istringstream ss(date);
	ss >> y >> dash1 >> m >> dash2 >> d;

	if (ss.fail() || dash1 != '-' || dash2 != '-')
		return false;

	if (y < 2009 || m < 1 || m > 12)
		return false;

	int daysInMonth[] = { 31, 28, 31, 30, 31, 30,
							31, 31, 30, 31, 30, 31 };

	if (m == 2) {
		bool isLeap = (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0));
		if (isLeap)
			daysInMonth[1] = 29;
	}

	if (d < 1 || d > daysInMonth[m - 1])
		return false;

	return true;
}


bool BitcoinExchange::isValidValue(const std::string& valueStr, float& value) {
	std::istringstream ss(valueStr);
	ss >> value;

	if (ss.fail() || !ss.eof()) {
		std::cerr << "Error: bad value => " << valueStr << std::endl;
		return false;
	}

	if (value < 0.0f) {
		std::cerr << "Error: not a positive number." << std::endl;
		return false;
	}

	if (value > 1000.0f) {
		std::cerr << "Error: too large a number." << std::endl;
		return false;
	}

	return true;
}


void	BitcoinExchange::processInput(const std::string& input) {
	std::ifstream input_file(input.c_str());
	if (!input_file.is_open()) {
		std::cerr << "Error: could not open the input file." << std::endl;
		return;
	}

	std::string line;
	std::getline(input_file, line);

	while (std::getline(input_file, line)) {
		size_t sep = line.find(" | ");
		if (sep == std::string::npos) {
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		std::string date = line.substr(0, sep);
		std::string amount = line.substr(sep + 3);
		float value;

		if (!isValidDate(date)) {
			std::cerr << "Error: wrong input => " << line << std::endl;
			continue;
		}

		if (!isValidValue(amount, value)) {
			continue;
		}

		std::map<std::string, float>::const_iterator it = _btcDB.lower_bound(date);
		if (it == _btcDB.end() || it->first != date) {
			if (it != _btcDB.begin()) {
				--it;
			} else {
				std::cerr << "Error: no earlier date available." << std::endl;
				continue;
			}
		}

		float price = it->second;
		std::cout << date << " => ";
		if (value == static_cast<int>(value))
			std::cout << static_cast<int>(value);
		else
		std::cout << value;
		float result = value * price;
		std::cout << " = " << result << std::endl;
	}
	input_file.close();
}




