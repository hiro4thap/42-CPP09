#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <list>
# include <deque>
# include <vector>
# include <iostream>
# include <ctime>
# include <cmath>
# include <algorithm>
# include <sys/time.h>
# include <sstream>

class	PmergeMe
{
public:
	PmergeMe();
	~PmergeMe();
	PmergeMe(PmergeMe const &rhs);
	PmergeMe	&operator=(PmergeMe const &rhs);
	
	std::vector<int> const	&getVChain() const;
	int const				&getVElapseTime() const;
	std::deque<int> const	&getDChain() const;
	int const				&getDElapseTime() const;

	void					mergeInsertSort(int size, char *numbers[]); // common

private:
	std::vector<int>							vectorParseInput(int size, char *numbers[]) const;
	void										vectorBinaryInsert(
			std::vector<std::pair<std::size_t, int> > &chain,
			int low,
			int high,
			std::pair<std::size_t, int> n);
	std::vector<std::size_t>					vectorSortImplement(std::vector<int> input);
	std::vector<std::pair<std::size_t, int> >	vectorExtractNumbers(
			std::vector<std::pair<std::size_t, int> >::iterator start,
			std::vector<std::pair<std::size_t, int> >::iterator end,
			int interval);
	std::vector<std::pair<std::size_t, int> >	vectorArrangeOrder(
			std::vector<std::pair<std::size_t, int> > numbers,
			std::vector<std::size_t> indexes);

	std::vector<int>							_v_chain;
	int											_v_elapse_time;

	std::size_t									findJacobDiff(int n);

	std::deque<int>							dequeParseInput(int size, char *numbers[]) const;
	void										dequeBinaryInsert(
			std::deque<std::pair<std::size_t, int> > &chain,
			int low,
			int high,
			std::pair<std::size_t, int> n);
	std::deque<std::size_t>					dequeSortImplement(std::deque<int> input);
	std::deque<std::pair<std::size_t, int> >	dequeExtractNumbers(
			std::deque<std::pair<std::size_t, int> >::iterator start,
			std::deque<std::pair<std::size_t, int> >::iterator end,
			int interval);
	std::deque<std::pair<std::size_t, int> >	dequeArrangeOrder(
			std::deque<std::pair<std::size_t, int> > numbers,
			std::deque<std::size_t> indexes);

	std::deque<int>								_d_chain;
	int											_d_elapse_time;
};

#endif
