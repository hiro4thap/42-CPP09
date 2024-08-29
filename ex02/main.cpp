#include "PmergeMe.hpp"
#include "Log.hpp"
#include <sstream>

void	printInput(int argc, char *argv[])
{
	Log::out("Before: ");
	for (int i = 0; i < argc; i++)
		std::cout << ' ' << argv[i];
	std::cout << std::endl;
}

void	printChain(PmergeMe const &pm)
{
	std::cout << "After:  ";
	std::vector<int> chain = pm.getVChain();
	for (std::vector<int>::const_iterator it = chain.cbegin(); it < chain.cend(); it++)
		std::cout << ' ' << *it;
	std::cout << std::endl;
}

int	validateInput(int argc, char *argv[])
{
	if (argc == 1)
	{
		Log::nl("Error: No argument is found", YELLOW);
		return false;
	}

	int number;
	for (int i = 1; i < argc; i++)
	{
		std::istringstream	stream(argv[i]);
		stream >> number;
		if (stream.fail() || number < 0 || !stream.eof())
		{
			Log::nl("Error: Invalid number is found", YELLOW);
			return false;
		}
	}
	return true;
}

int	main(int argc, char *argv[])
{
	if (!validateInput(argc, argv))
		return 1;
	printInput(--argc, ++argv);

	PmergeMe	pm;
	pm.mergeInsertSort(argc, argv);
	printChain(pm);
	std::cout
		<< "Time to process a range of " << argc << " elements with std::vector<int> : " 
		<< pm.getVElapseTime() << " us" 
		<< std::endl
		<< "Time to process a range of " << argc << " elements with std::deque<int>  : " 
		<< pm.getDElapseTime() << " us" 
		<< std::endl; 

	return 0;
}
