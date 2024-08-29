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

std::vector<int> const	&PmergeMe::getVChain() const
{
	return _v_chain;
}

int const	&PmergeMe::getVElapseTime() const
{
	return _v_elapse_time;
}

void	PmergeMe::setVElapseTime(int const elapse_time)
{
	_v_elapse_time = elapse_time;
}

std::vector<int>	PmergeMe::vectorParseInput(int size, char *numbers[]) const
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

void	PmergeMe::mergeInsertSort(int size, char *numbers[])
{
	struct timeval	start, end;
	// sort using vector;
	gettimeofday(&start, NULL);
	std::vector<int> v_input = vectorParseInput(size, numbers);
	std::vector<std::size_t> v_indexes = vectorSortImplement(v_input);
	for (int i = 0; i < size; i++)
		_v_chain.push_back(v_input[v_indexes[i]]);
	gettimeofday(&end, NULL);
	setVElapseTime(end.tv_usec - start.tv_usec);

	//sort using deque;
	gettimeofday(&start, NULL);
	std::deque<int> d_input = dequeParseInput(size, numbers);
	std::deque<std::size_t> d_indexes = dequeSortImplement(d_input);
	for (int i = 0; i < size; i++)
		_d_chain.push_back(d_input[d_indexes[i]]);
	gettimeofday(&end, NULL);
	setDElapseTime(end.tv_usec - start.tv_usec);
}

// 1. assign index on numbers
// ex. 4 9 8 2 1
// ->
// index: 0 1 2 3 4
// value: 4 9 8 2 1
// 
// 2. make pairs and smaller number comes first
// index: [0 1] [3 2] 4
// value: [4 9] [2 8] 1
//
// 3. sort pairs recursively correspoind to the larger numbers
// index: [3 2] [0 1] 4
// value: [2 8] [4 9] 1
// 
// 4. now 8, 9 are sorted, and 2 should come first as it's lower than 8 (call these chain)
//
// 5. insert 1 and 4 into chain
// index: 4 3 0 2 1
// value: 1 2 4 8 9
//
// 6. return vector of indexes
std::vector<std::size_t>	PmergeMe::vectorSortImplement(std::vector<int> input)
{
	int size = input.size();
	if (size == 1)
	{
		std::vector<std::size_t> single(1, 0);
		return single;
	}
	std::vector<std::pair<std::size_t, int> >	numbers;
	for (std::size_t i = 0; i < input.size(); i++)
	{
		numbers.push_back(std::make_pair<std::size_t, int>(i, input[i]));
		if (i % 2 == 1 && input[i] < input[i - 1])
			std::swap(numbers[i - 1], numbers[i]);
	}

	std::vector<int> larger_numbers;
	for (int i = 1; i < size; i += 2)
		larger_numbers.push_back(numbers[i].second);

	std::vector<std::size_t> indexes = vectorSortImplement(larger_numbers);

	std::vector<std::pair<std::size_t, int> >	smaller = vectorArrange(vectorExtractNumbers(numbers.begin(), numbers.end(), 2), indexes);
	std::vector<std::pair<std::size_t, int> >	chain = vectorArrange(vectorExtractNumbers(numbers.begin() + 1, numbers.end(), 2), indexes);
	chain.insert(chain.begin(), smaller[0]);
	for (int i = 2; findJacobDiff(i - 1) <= (int)smaller.size(); i++)
	{
		for (int diff = findJacobDiff(i); findJacobDiff(i - 1) < diff; diff--)
		{
			if (diff <= (int)smaller.size())
				vectorBinaryInsert(chain, 0, pow(2, i - 1), smaller[diff - 1]);
		}
	}
	
	std::vector<std::size_t>	new_indexes;
	for (int i = 0; i < size; i++)
		new_indexes.push_back(chain[i].first);
	return new_indexes;
}

std::vector<std::pair<std::size_t, int> > PmergeMe::vectorExtractNumbers(
		std::vector<std::pair<std::size_t, int> >::iterator start,
		std::vector<std::pair<std::size_t, int> >::iterator end,
		int interval)
{
	std::vector<std::pair<std::size_t, int> >	extracted;
	for (std::vector<std::pair<std::size_t, int> >::iterator it = start; it < end; std::advance(it, interval))
		extracted.push_back(*it);
	return extracted;
}

std::vector<std::pair<std::size_t, int> >	PmergeMe::vectorArrange(std::vector<std::pair<std::size_t, int> > numbers, std::vector<std::size_t> indexes)
{
	std::vector<std::pair<std::size_t, int> >	replaced;
	for (std::size_t i = 0; i < indexes.size(); i++)
		replaced.push_back(numbers[indexes[i]]);
	if (indexes.size() < numbers.size())
		replaced.push_back(numbers.back());
	return replaced;
}

void	PmergeMe::vectorBinaryInsert(std::vector<std::pair<std::size_t, int> > &chain, int low, int high, std::pair<std::size_t, int> num)
{
	if (chain.empty() || chain.back().second < num.second)
	{
		chain.push_back(num);
		return ;
	}
	while (low < high)
	{
		int mid = low + (high - low) / 2;
		if (chain[mid].second < num.second)
			low = mid + 1;
		else if (num.second < chain[mid].second)
			high = mid - 1;
		else
		{
			chain.insert(chain.begin() + mid, num);
			return;
		}
	}
	if (num.second < chain[low].second)
		chain.insert(chain.begin() + low, num);
	else
		chain.insert(chain.begin() + low + 1, num);
}

int	PmergeMe::findJacobDiff(int n)
{
	return ((pow(2, n + 1) + pow(-1, n)) / 3);
}

std::deque<int> const	&PmergeMe::getDChain() const
{
	return _d_chain;
}

int const	&PmergeMe::getDElapseTime() const
{
	return _d_elapse_time;
}

void	PmergeMe::setDElapseTime(int const elapse_time)
{
	_d_elapse_time = elapse_time;
}

std::deque<int>	PmergeMe::dequeParseInput(int size, char *numbers[]) const
{
	int	n;
	std::deque<int> input;

	for (int i = 0; i < size; i++)
	{
		std::string str(numbers[i]);
		std::istringstream	stream(str);
		stream >> n;
		input.push_back(n);
	}
	return input;
}

std::deque<std::size_t>	PmergeMe::dequeSortImplement(std::deque<int> input)
{
	int size = input.size();
	if (size == 1)
	{
		std::deque<std::size_t> single(1, 0);
		return single;
	}
	std::deque<std::pair<std::size_t, int> >	numbers;
	for (std::size_t i = 0; i < input.size(); i++)
	{
		numbers.push_back(std::make_pair<std::size_t, int>(i, input[i]));
		if (i % 2 == 1 && input[i] < input[i - 1])
			std::swap(numbers[i - 1], numbers[i]);
	}

	std::deque<int> larger_numbers;
	for (int i = 1; i < size; i += 2)
		larger_numbers.push_back(numbers[i].second);

	std::deque<std::size_t> indexes = dequeSortImplement(larger_numbers);

	std::deque<std::pair<std::size_t, int> >	smaller = dequeArrange(dequeExtractNumbers(numbers.begin(), numbers.end(), 2), indexes);
	std::deque<std::pair<std::size_t, int> >	chain = dequeArrange(dequeExtractNumbers(numbers.begin() + 1, numbers.end(), 2), indexes);
	chain.insert(chain.begin(), smaller[0]);
	for (int i = 2; findJacobDiff(i - 1) <= (int)smaller.size(); i++)
	{
		for (int diff = findJacobDiff(i); findJacobDiff(i - 1) < diff; diff--)
		{
			if (diff <= (int)smaller.size())
				dequeBinaryInsert(chain, 0, pow(2, i - 1), smaller[diff - 1]);
		}
	}
	
	std::deque<std::size_t>	new_indexes;
	for (int i = 0; i < size; i++)
		new_indexes.push_back(chain[i].first);
	return new_indexes;
}

std::deque<std::pair<std::size_t, int> > PmergeMe::dequeExtractNumbers(
		std::deque<std::pair<std::size_t, int> >::iterator start,
		std::deque<std::pair<std::size_t, int> >::iterator end,
		int interval)
{
	std::deque<std::pair<std::size_t, int> >	extracted;
	for (std::deque<std::pair<std::size_t, int> >::iterator it = start; it < end; std::advance(it, interval))
		extracted.push_back(*it);
	return extracted;
}

std::deque<std::pair<std::size_t, int> >	PmergeMe::dequeArrange(std::deque<std::pair<std::size_t, int> > numbers, std::deque<std::size_t> indexes)
{
	std::deque<std::pair<std::size_t, int> >	replaced;
	for (std::size_t i = 0; i < indexes.size(); i++)
		replaced.push_back(numbers[indexes[i]]);
	if (indexes.size() < numbers.size())
		replaced.push_back(numbers.back());
	return replaced;
}

void	PmergeMe::dequeBinaryInsert(std::deque<std::pair<std::size_t, int> > &chain, int low, int high, std::pair<std::size_t, int> num)
{
	if (chain.empty() || chain.back().second < num.second)
	{
		chain.push_back(num);
		return ;
	}
	while (low < high)
	{
		int mid = low + (high - low) / 2;
		if (chain[mid].second < num.second)
			low = mid + 1;
		else if (num.second < chain[mid].second)
			high = mid - 1;
		else
		{
			chain.insert(chain.begin() + mid, num);
			return;
		}
	}
	if (num.second < chain[low].second)
		chain.insert(chain.begin() + low, num);
	else
		chain.insert(chain.begin() + low + 1, num);
}

