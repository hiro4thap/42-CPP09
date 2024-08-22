#include "RPN.hpp"
#include "Log.hpp"

int	main(int argc, char *argv[])
{
	if (argc != 2)
	{
		Log::nl("Error: Invalid number of arguments", YELLOW);
		return 1;
	}
	if (!Rpn::isValidRpn(argv[1]))
	{
		Log::nl("Error: The given RPN is invalid ", YELLOW);
		return 1;
	}

	Rpn	rpn;
	try
	{
		Log::nl(rpn.calculate(std::string(argv[1])));
	}
	catch (std::exception const &e)
	{
		Log::nl(e.what(), RED);
	}
	return 0;
}
