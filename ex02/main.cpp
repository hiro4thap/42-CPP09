#include "PmergeMe.hpp"
#include "Log.hpp"
#include <sstream>

void	printInput(int argc, char *argv[])
{
	Log::out("Before: ");
	for (int i = 1; i < argc; i++)
		std::cout << ' ' << argv[i];
	std::cout << std::endl;
}

int	main(int argc, char *argv[])
{
	if (argc == 1)
	{
		Log::nl("Error: No argument is found", YELLOW);
		return 1;
	}
	int number;
	for (int i = 1; i < argc; i++)
	{
		std::istringstream	stream(argv[i]);
		stream >> number;
		if (stream.fail() || number < 0 || !stream.eof())
		{
			Log::nl("Error: Invalid number is found", YELLOW);
			return 1;
		}
	}
	printInput(argc, argv);

	PmergeMe	pm;

	pm.mergeInsertSort(--argc, ++argv);
	pm.printChain();
	std::cout << "Time to process a range of " << argc
		<< " elements with std::vector<int> : " 
		<< pm.getVElapseTime() << " us" 
		<< std::endl; 

	// take 2 integers
	//  make pair
	//  insert pair into _v_pairs
	// if 1 interger left
	//  insert into pair's back (inserted into main chain finally)
	// 
	/////////////////////////////
	// where ai < bi
	// a1   a2   a3   a4   a5   a6
	//  b1 <  b2 < b3 < b4 < b5 < b6
	/////////////////////////////
	//
	// put into main chain
	//  p(a1) -> p(b1) -> p(b2) ... -> p(b6)
	//  i(a3) -> i(a2) : twice
	//  i(a5) -> i(a4) : three times
	//  i(a11) -> .... -> i(a6)
	return 0;
}
