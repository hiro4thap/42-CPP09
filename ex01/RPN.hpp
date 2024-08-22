#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <stack>

class	Rpn
{
public:
	Rpn();
	~Rpn();
	Rpn(Rpn const &rhs);
	Rpn	&operator=(Rpn const &rhs);

	static bool	isValidRpn(std::string const &rpn);
	static bool	isOperator(char const c);
	static bool	isDigit(char const c);

	std::string	calculate(std::string const &rpn);

	class	ZeroDivisionException : public std::exception
	{
	public:
		ZeroDivisionException();
		char const *what() const throw();
	};

private:
	std::stack<std::string>	_stack;
};

#endif
