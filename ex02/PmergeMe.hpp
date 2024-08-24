#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <list>
# include <vector>
# include <iostream>
# include <ctime>
# include <cmath>
# include <algorithm>
# include <sys/time.h>

class	PmergeMe
{
public:
	PmergeMe();
	~PmergeMe();
	PmergeMe(PmergeMe const &rhs);
	PmergeMe	&operator=(PmergeMe const &rhs);
	
	void		printChain() const;
	void		mergeInsertSort(int size, char *numbers[]);
	int const	&getVElapseTime() const;
	void		setVElapseTime(int const elapse_time);
	
private:
	vector<int>	parseInput(int size, char *numbers[]) const;
	void		setPairs(vector<int> input);
	void		initializeChain();
	void		insertToParis(vector<int> pair);
	void		insertToChain(int compare_times, int n);
	std::vector<std::vector<int> >	_v_pairs;
	std::vector<int>				_v_chain;
	int								_v_elapse_time;
//	list<list<int> >		_lstore;
};

#endif
