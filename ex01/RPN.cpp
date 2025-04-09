#include "RPN.hpp"
#include <sstream>
#include <stdexcept>

int RPN::evaluate(const std::string& expression) {
	std::stack<int> stack;
	std::istringstream iss(expression);
	std::string token;

	while (iss >> token) {
		if (token.length() == 1 && std::isdigit(token[0])) {
			stack.push(token[0] - '0');
		} else if (token == "+" || token == "-" || token == "*" || token == "/") {
			if (stack.size() < 2)
				throw std::runtime_error("Error");

			int b = stack.top(); stack.pop();
			int a = stack.top(); stack.pop();
			int result = 0;

			if (token == "+") result = a + b;
			else if (token == "-") result = a - b;
			else if (token == "*") result = a * b;
			else if (token == "/") {
				if (b == 0)
					throw std::runtime_error("Error: division by zero");
				result = a / b;
			}

			stack.push(result);
		} else {
			throw std::runtime_error("Error");
		}
	}

	if (stack.size() != 1)
		throw std::runtime_error("Error");

	return stack.top();
}

