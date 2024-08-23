#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <fstream>
# include <sstream>
# include <map>
# include <string>
# include "Log.hpp"

class	BitcoinExchange
{
public:
	BitcoinExchange();
	~BitcoinExchange();
	BitcoinExchange(BitcoinExchange const &rhs);
	BitcoinExchange	&operator=(BitcoinExchange const &rhs);

	int		setData();
	void	displayValues(std::string const &file);
	
private:
	bool 	isValidDate(std::string const &date) const;
	bool	validateData(std::string const &line, char const delimiter) const;
	bool	validatePrice(std::string const &line, char const delimiter, std::string const &file) const;
	float	findExchangeRate(std::string const &date) const;
	void	trimSpace(std::string &str);

	std::map<std::string, float>	_data;
};

#endif
