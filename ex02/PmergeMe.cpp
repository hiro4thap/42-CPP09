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
	//insertToChain();
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

vector<int>	parseInput(int size, char *numbers[]) const
{
	int	n;
	vector<int> input;

	for (int i = 0; i < size; i++)
	{
		std::istringstream	stream(numbers[i]);
		stream >> n;
		input.push_back(n);
	}
	return input;
}

void	PmergeMe::setPairs(vector<int> input)
{
	bool	has_alone = input.size() % 2;
	std::vector<int>iterator end = has_alone : input.end() ? --(input.end());
	for (std::vector<int>iterator it = input.begin(); it < end; it++)
	{
		std::vector<int>	pair;
		pair.push_back(it++);
		if (pair.front() < *it)
			pair.push_back(*it);
		else
			pair.push_front(*it);
		insertToParis(pair);
	}
	if (has_alone)
	{
		std::vector<int>	alone;
		alone.push_back(input.end());
		_v_paris.push_back(alone);
	}
}

void	PmergeMe::initializeChain()
{
}

// WIP
void	PmergeMe::insertToParis(vector<int> pair)
{
	if (_v_paris.empty())
		_v_paris.push_back(pair);
	int	low = 0;
	int	high = _v_paris.size() - 1;
	while (low != high)
	{
		int mid = low + (high - low) / 2;
		if (_v_paris[mid] < pair.back())
			low = mid + 1;
		else if (pair.back() < _v_paris[mid])
			high = mid - 1;
		else
			_v_paris.insert(_v_paris.begin() + mid, pair);
	}
	_v_paris.insert(_v_paris.begin() + mid, pair);
}

void	PmergeMe::insertToChain(int compare_times, int n)
{
	(void)compare_times;
	(void)n;
}
