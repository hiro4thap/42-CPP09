#include "RPN.hpp"

Rpn::Rpn()
{
}

Rpn::~Rpn()
{
}

Rpn::Rpn(Rpn const &rhs)
{
	_stack = rhs._stack;
}

Rpn	&Rpn::operator=(Rpn const &rhs)
{
	if (this != &rhs)
		_stack = rhs._stack;
	return *this;
}

std::string	Rpn::calculate(std::string const &rpn)
{
	for (std::size_t i = 0 ; i < rpn.size(); i += 2)
	{
		if (isDigit(rpn[i]))
			_stack.push(rpn.substr(i, 1));
		else if (isOperator(rpn[i]))
		{
			int	i1 = std::stoi(_stack.top());
			_stack.pop();
			int	i2 = std::stoi(_stack.top());
			_stack.pop();
			char	op = rpn[i];

			int res = 0;
			if (op == '+')
				res = i2 + i1;
			else if (op == '-')
				res = i2 - i1;
			else if (op == '*')
				res = i2 * i1;
			else if (op == '/' && i1 == 0)
				throw ZeroDivisionException();
			else if (op == '/' && i1 != 0)
				res = i2 / i1;
			_stack.push(std::to_string(res));
			
		}
	}
	return _stack.top();
}

Rpn::ZeroDivisionException::ZeroDivisionException()
{
}

char const *Rpn::ZeroDivisionException::what() const throw()
{
	return "Numbers cannot be divided by 0";
}

bool	Rpn::isOperator(char const c)
{
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool	Rpn::isDigit(char const c)
{
	return ('0' <= c  && c <= '9');
}

bool	Rpn::isValidRpn(std::string const &rpn)
{
	if (rpn.empty())
		return false;

	std::size_t	index = 0;
	if (!isDigit(rpn[index++]))
		return false;
	int	nums = 1;
	while (index < rpn.size())
	{
		if (rpn[index++] != ' ')
			return false;
		if (isDigit(rpn[index]))
		{
			nums++;
			index++;
		}
		else if (isOperator(rpn[index]))
		{
			nums--;
			index++;
		}
		else
			return false;
		if (nums < 1)
			return false;
	}
	return (nums == 1);
}
