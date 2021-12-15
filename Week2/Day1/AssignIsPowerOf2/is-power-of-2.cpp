#include <iostream>
#include <cassert>

// No arithmetic operators (except for +=)
// No math library

// This is a great way of going about this problem, and it's probably very fast.
// 	I'll do you one better. No += operator!
// 	Note that you didn't say anything about bitwise operators...

bool isPowerOf2(unsigned long input)
{
	for (unsigned long i=1; i != 0; i = i << 1) // Here's something interesting about binary: If a value in binary can be represented by a single 1 followed by any amount of zeroes, it is a power of 2.
		if (i == input) return true;
	return false;
}

int main(void)
{
	unsigned long i;
	for (;;)
	{
		std::cout << "enter a number >";
		std::cin >> i;
		if (std::cin.fail())
		{
			std::cout << "INPUT MUST BE A VALID INTEGER NUMBER" << std::endl;
			assert(false);
		}
		std::cout << i << (isPowerOf2(i) ? " is a power of 2" : " is not a power of 2") << std::endl;
	}
	return 0;
}
