#include "Log.hpp"

Log::Log()
{
}

Log::~Log()
{
}

Log::Log(const Log &rhs)
{
	(void)rhs;
}

Log Log::operator=(const Log &rhs)
{
	(void)rhs;
	return *this;
}

void Log::out(const std::string &message, std::string color) 
{
	std::cout << color << message << NONE;
}

void Log::out(const int number, std::string color) 
{
	std::cout << color << number << NONE;
}

void Log::out(const double number, std::string color)
{
	std::cout << color << number << NONE;
}

void Log::out(const float number, std::string color) 
{
	std::cout << color << number << NONE;
}

void Log::nl(const std::string &message, std::string color) 
{
	std::cout << color << message << NONE << "\n";
}

void Log::nl(const int number, std::string color) 
{
	std::cout << color << number << NONE << "\n";
}

void Log::nl(const double number, std::string color)
{
	std::cout << color << number << NONE << "\n";
}

void Log::nl(const float number, std::string color) 
{
	std::cout << color << number << NONE << "\n";
}

void Log::setColor(std::string color)
{
	std::cout << color;
}
