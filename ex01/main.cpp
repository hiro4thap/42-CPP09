#include "RPN.hpp"

int	main(int argc, char *argv[])
{
	if (argc != 2 || !*argv[1])
	{
		std::cout << "Invalid number of arguments" << std::endl;
	}
	//if (!Rpn::isValidRpn(argv[1]))
	//{
	//	std::cout << "Invalid RPN is given as argument" << std::endl;
	//	return 1;
	//}
	Rpn	rpn;
	std::string str(argv[1]);
	//rpn.setStack(str);
	std::cout << rpn.calculate(str) << std::endl;
	return 0;
}
