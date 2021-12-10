#include <iostream>
#include <vector>
#include <string>

int main(void)
{
	/* Here's a great example of when we should use a vector as opposed to an array! */

	std::vector<std::string> values{};
	std::string input{}; 
	for(;;)
	{
		std::cout << "Input space-separated data ('exit' when finished): ";
		std::cin >> input;
		std::cout << std::endl;

		if (input.empty())
			continue;
		else if (input.compare("exit") == 0)
			break;
		else
			values.push_back(input);
	}

	for (unsigned i=0; i < values.size(); i++)
		std::cout << i << " : " << values.at(i) << std::endl;

	return 0;
}
