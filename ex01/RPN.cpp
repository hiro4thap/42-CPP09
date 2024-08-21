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
			else if (op == '/') //TODO: hanle zero deivision
				res = i2 / i1;
			_stack.push(std::to_string(res));
			
		}
	}
	return _stack.top();
}

bool	Rpn::isOperator(char const c)
{
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool	Rpn::isDigit(char const c)
{
	return ('0' <= c  && c <= '9');
}

// TODO: to be fixed
bool	Rpn::isValidRpn(std::string const &rpn)
{
	if (rpn.size() < 5 || rpn.size() % 4 != 1)
		return false;

	std::size_t	index = 0;
	if (!isDigit(rpn[index++]))
		return false;
	while (index < rpn.size())
	{
		if (rpn[index++] != ' ')
			return false;
		if (!isDigit(rpn[index++]))
			return false;
		if (rpn[index++] != ' ')
			return false;
		if (!isOperator(rpn[index++]))
			return false;
	}
	// Zero Division should be checked??
	return true;
}
