#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>

class PmergeMe {
public:
	PmergeMe();
	~PmergeMe();

	void sortAndPrint(const std::vector<int>& input);

private:
	void fordJohnson(std::vector<int>& container);
	void fordJohnson(std::deque<int>& container);

	template<typename T>
	void binaryInsert(T& container, const typename T::value_type& val);
};

#endif
