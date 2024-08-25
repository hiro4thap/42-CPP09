#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
}

PmergeMe::~PmergeMe()
{
}

PmergeMe::PmergeMe(PmergeMe const &rhs)
{
	*this = rhs;
}

PmergeMe	&PmergeMe::operator=(PmergeMe const &rhs)
{
	(void)rhs;
	return *this;
}


void	PmergeMe::printChain() const
{
	std::cout << "After:  ";
	for (std::vector<int>::const_iterator it = _v_chain.cbegin(); it < _v_chain.cend(); it++)
		std::cout << ' ' << *it;
	std::cout << std::endl;
}

void	PmergeMe::mergeInsertSort(int size, char *numbers[])
{
	struct timeval	start, end;
	gettimeofday(&start, NULL);
	// sort with vector;
	std::vector<int> input = parseInput(size, numbers);
	setPairs(input);
	initializeChain();
	for (int i = 2; i < 10; i++) //TODO:numbers
	{
		for (int diff = findJacobDiff(i); findJacobDiff(i - 1) < diff; diff--)
		{
			if ((size + 1) / 2 < diff)
				continue ;
			insertToChain(i, _v_pairs[diff - 1].front());
		}
	}
	gettimeofday(&end, NULL);
	setVElapseTime(end.tv_usec - start.tv_usec);
	// sort with list;
}

int const	&PmergeMe::getVElapseTime() const
{
	return _v_elapse_time;
}
void		PmergeMe::setVElapseTime(int const elapse_time)
{
	_v_elapse_time = elapse_time;
}

std::vector<int>	PmergeMe::parseInput(int size, char *numbers[]) const
{
	int	n;
	std::vector<int> input;

	for (int i = 0; i < size; i++)
	{
		std::string str(numbers[i]);
		std::istringstream	stream(str);
		stream >> n;
		input.push_back(n);
	}
	return input;
}

void	PmergeMe::setPairs(std::vector<int> input)
{
	bool	has_alone = (input.size() % 2 == 1);
	std::vector<int>::iterator end = has_alone ? --(input.end()) : input.end();
	for (std::vector<int>::iterator it = input.begin(); it < end; std::advance(it, 2))
	{
		std::vector<int>	pair;
		if (*it < *(it + 1))
		{
			pair.push_back(*it);
			pair.push_back(*(it + 1));
		}
		else
		{
			pair.push_back(*(it + 1));
			pair.push_back(*it);
		}
		insertToPairs(pair);
	}
	if (has_alone)
	{
		std::vector<int>	alone;
		alone.push_back(input.back());
		_v_pairs.push_back(alone);
	}
}

void	PmergeMe::initializeChain()
{
	_v_chain.push_back(_v_pairs.front().front());
	for (std::size_t i = 0; i < _v_pairs.size(); i++)
	{
		if (_v_pairs[i].size() == 2)
			_v_chain.push_back(_v_pairs[i].back());
	}
}

//int	PmergeMe::binarySearch(std::vector<int> container, int n)
//{
//	int low = 0;
//	int	high = container.size() - 1;
//	
//	if (container.empty())
//		return 0;
//	if (container.back() < n)
//		return container.size();
//	while (low < high)
//	{
//		int mid = low + (high - low) / 2;
//		if (container[mid] < n)
//			low = mid + 1;
//		else if (n < container[mid])
//			high = mid - 1;
//		else
//			return mid;
//	}
//	return (n < container[low] : low ? low + 1);
//}

void	PmergeMe::insertToPairs(std::vector<int> pair)
{
	int	low = 0;
	int	high = _v_pairs.size() - 1;

	if (_v_pairs.empty() || _v_pairs.back().back() < pair.back())
	{
		_v_pairs.push_back(pair);
		return ;
	}
	while (low < high)
	{
		int mid = low + (high - low) / 2;
		if (_v_pairs[mid].back() < pair.back())
			low = mid + 1;
		else if (pair.back() < _v_pairs[mid].back())
			high = mid - 1;
		else
		{
			_v_pairs.insert(_v_pairs.begin() + mid, pair);
			return ;
		}
	}
	if (pair.back() < _v_pairs[low].back())
		_v_pairs.insert(_v_pairs.begin() + low, pair);
	else
		_v_pairs.insert(_v_pairs.begin() + low + 1, pair);
}

void	PmergeMe::insertToChain(int compare_times, int n)
{
	int low = 0;
	int	high = pow(2, compare_times - 1);
	
	if (_v_chain.empty())
		return ;
	if (_v_chain.back() < n)
	{
		_v_chain.push_back(n);
		return ;
	}
	while (low < high)
	{
		int mid = low + (high - low) / 2;
		if (_v_chain[mid] < n)
			low = mid + 1;
		else if (n < _v_chain[mid])
			high = mid - 1;
		else
		{
			_v_chain.insert(_v_chain.begin() + low, n);
			return;
		}
	}
	if (n < _v_chain[low])
		_v_chain.insert(_v_chain.begin() + low, n);
	else
		_v_chain.insert(_v_chain.begin() + low + 1, n);
}

int	PmergeMe::findJacobDiff(int n)
{
	return ((pow(2, n + 1) + pow(-1, n)) / 3);
}
