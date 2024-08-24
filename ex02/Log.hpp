#ifndef LOG_HPP
# define LOG_HPP

# include <iostream>

# define NONE		"\033[0;0m"
# define RED 		"\033[0;31m"
# define GREEN		"\033[0;32m"
# define YELLOW		"\033[0;33m"
# define BLUE		"\033[0;34m"
# define PURPLE		"\033[0;35m"
# define CYAN		"\033[0;36m"

class Log
{
public:
	Log();
	~Log();
	Log(const Log &rhs);
	Log operator=(const Log &rhs);
	static void out(const std::string &message, std::string color = NONE);
	static void out(const int number, std::string color = NONE);
	static void out(const double number, std::string color = NONE);
	static void out(const float number, std::string color = NONE);
	static void nl(const std::string &message = "", std::string color = NONE);
	static void nl(const int number, std::string color = NONE);
	static void nl(const double number, std::string color = NONE);
	static void nl(const float number, std::string color = NONE);
	static void	setColor(std::string color = NONE);
};

#endif
