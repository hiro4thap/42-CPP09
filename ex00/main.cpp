#include "BitcoinExchange.hpp"
#include "Log.hpp"

//bool	validate(int argc, char *file)
//{
//	std::ifstream	price(file);
//	if (!price.is_open())
//	{
//		std::cout << RED << "Error: cannot open \"" << file << "\"" << "\n";
//		data.close();
//		return 1;
//	}
//	data.close();
//	price.close();
//	return 0;
//}

int	main(int argc, char *argv[])
{
	// validation
	//  argc == 2
	//  "data.csv" exists and openable
	//  input exists and openable
	// construct instance
	//  "data.csv" into _data
	// loop line in input file
	//  validation
	//   date -> exists and Year-Month-Day '00'
	//   | -> exists
	//   value -> exists and 0-1000 float
	//  search ex-rate in the closest data from _data
	//  display message

	if (argc != 2 || !*argv[1])
	{
		Log::nl("Error: invalid argument", RED);
		return 1;
	}
	BitcoinExchange	btc;
	if (!btc.setData())
		btc.displayValues(std::string(argv[1]));
	return 0;
}

