#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::~BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &rhs)
{
	_data = rhs._data;
}

BitcoinExchange	&BitcoinExchange::operator=(BitcoinExchange const &rhs)
{
	if (this != &rhs)
		_data = rhs._data;
	return *this;
}

int		BitcoinExchange::setData()
{
	std::ifstream	data("data.csv");
	if (!data.is_open())
	{
		Log::nl("Error: cannot open \"data.csv\"", YELLOW);
		return 1;
	}
	char delimiter = ',';
	std::string	line;
	std::getline(data, line);
	while (std::getline(data ,line))
	{
		if (!validateData(line, delimiter))
			return 1;
		std::string	date = line.substr(0, line.find(delimiter));
		float		exchange_rate = std::stof(line.substr(line.find(delimiter) + 1));
		_data.insert(std::pair<std::string, float>(date, exchange_rate));
	}
	return 0;
}

void	BitcoinExchange::displayValues(std::string const &file)
{
	std::ifstream	istream(file);
	if (!istream.is_open())
	{
		Log::nl("Error: cannot open \"" + file + "\"", YELLOW);
		return ;
	}
	char delimiter = '|';
	std::string	line;
	std::getline(istream, line);
	while (std::getline(istream ,line))
	{
		if (!validatePrice(line, delimiter))
			continue ;
		std::string	date = line.substr(0, line.find(delimiter));
		float		value = std::stof(line.substr(line.find(delimiter) + 1));
		float		exchange_rate = findExchangeRate(date);
		std::cout << date << " => " << value << " = " << value * exchange_rate << std::endl;
	}
}

bool BitcoinExchange::isValidDate(std::string const &date) const
{
	int		year;
	int		month;
	int		day;
	char	delimiter1;
	char	delimiter2;

	std::istringstream 	iss(date);
	iss >> year >> delimiter1 >> month >> delimiter2 >> day;
	//std::cout << year << ' ' << month << ' ' << day << std::endl;
	if (delimiter1 != '-' || delimiter2 != '-')
		return false;
	if (year < 0 || 9999 < year)
		return false;
	if (month < 1 || 12 < month)
		return false;
	if (day < 1 || 31 < day)
		return false;
	if ((month == 4 || month == 6 || month == 9 || month == 11)
			&& 30 < day)
		return false;
	if (month == 2)
	{
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
			return (day <= 29);
		else 
			return (day <= 28);
	}
	return true;
}

bool	BitcoinExchange::validateData(std::string const &line, char const delimiter) const
{
	if (line.find(delimiter) == std::string::npos)
	{
		Log::nl("Error: exchange rate does not exist", YELLOW);
		return false;
	}
	std::string	date = line.substr(0, line.find(delimiter));
	float		exchange_rate = std::stof(line.substr(line.find(delimiter) + 1));
	if (!isValidDate(date))
	{
		Log::nl("Error: date format is invalid", YELLOW);
		return false;
	}
	if (exchange_rate < 0)
	{
		Log::nl("Error: exchange rate is negative", YELLOW);
		return false;
	}
	return true;
}

bool	BitcoinExchange::validatePrice(std::string const &line, char const delimiter) const
{
	if (line.find(delimiter) == std::string::npos)
	{
		Log::nl("Error: value does not exist", YELLOW);
		return false;
	}
	std::string	date = line.substr(0, line.find(delimiter));
	float		value;
	try
	{
		value = std::stof(line.substr(line.find(delimiter) + 1));
	}
	catch (std::exception &e)
	{
		Log::nl("Error: value is invalid", YELLOW);
		return false;
	}
	if (!isValidDate(date))
	{
		Log::nl("Error: date format is invalid", YELLOW);
		return false;
	}
	if (value < 0 || 1000 < value)
	{
		Log::nl("Error: value is invalid", YELLOW);
		return false;
	}
	return true;
}

float	BitcoinExchange::findExchangeRate(std::string const &date) const
{
	std::map<std::string, float>::const_iterator	cit = _data.upper_bound(date);
	if (cit == _data.cbegin() && _data.find(date) != _data.begin())
	{
		Log::nl("No info");
		return -1;
	}
	return (--cit)->second;
}
