#include <iostream>
#include <regex>
#include <string_view>
#include <cstdlib>
#include <iomanip>

#define MAX_INPUT_BYTES 1024

// Hey! I did this before... Deja vu. //
typedef unsigned int uint;
typedef union { float f; struct { uint jVal : 23; uint nVal : 8; uint sVal : 1; } vals; } float_explode;

bool split(const std::string_view&, std::string_view&, std::string_view&);

int main(void)
{
	std::cout << "Please enter number in fraction format (x/y) or decimal format (x.y) >";

	std::regex validFraction("[0-9]+/[0-9]+");
	std::regex validFractionDec("[0-9]+\\.[0-9]+");

	std::string input_raw;
	std::getline(std::cin, input_raw);
	std::string_view input(input_raw);

	if (regex_match(input_raw, validFraction))
	{
		std::string_view lhs, rhs;
		bool success = split(input, lhs, rhs);

		int numerator = atoi(lhs.data()), 
			denominator =  atoi(rhs.data());

		float f = (float) numerator / (float) denominator;
		float_explode fExp {f};

		std::cout << "J = " << fExp.vals.jVal << ", "
			<< "N = " << fExp.vals.nVal << std::endl
			<< std::setprecision(40) << f << std::endl;
	}
	else if (regex_match(input_raw, validFractionDec))
	{
		float f = atof(input.data());
		float_explode fExp {f};

		std::cout << "J = " << fExp.vals.jVal << ", "
			<< "N = " << fExp.vals.nVal << std::endl
			<< std::setprecision(40) << f << std::endl;
	}
	else
		std::cout << "invalid input" << std::endl;

	return 0;
}

bool split(const std::string_view& str, std::string_view& lhs, std::string_view& rhs)
{
	size_t pos = 0;
	if ((pos = str.find("/")) != std::string_view::npos)
	{
		lhs = std::string_view {str.substr(0, pos)};
		rhs = std::string_view {str.substr(pos+1)};
		return true; 
	}
	return false;
}
