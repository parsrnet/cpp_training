#include <iostream>
#include <iomanip> // std::setw, std::left, std::right functions
#include <map>
#include <string>

// MACROS //
/* Macros for custom 'table-like' spacing */
#define TBL_COL_SPACING 15 
#define TBL_COL_LEFT(a) std::setw(TBL_COL_SPACING) << std::left << a
#define TBL_COL_RIGHT(a) std::setw(TBL_COL_SPACING) << std::right << a

/* Shorthand macros for simplifying operations */
// PROMPT(a): print 'a'
#define prompt(a) (std::cout << a)
// AUTOMAP(a): shorthand for intializing map key-value
#define automap(a) { #a, sizeof(a) }


// TYPES //
/* Types that I use inside the program: */
typedef unsigned char uchar; // Shorthand 'unsigned char' (which is a byte)
typedef std::map<const std::string, unsigned long> typesizemap_t; // Shorthand for our map so we don't have to write out the template every time

/* You'll find the following types all allocate the same size of char (1B)
 * 	I'll elaborate on more detail some of the understanding I have on these types in the 2nd code Assignment 
 * 	As someone who really loves core C programming, I've done a lot of research into how these are handled and tricks we can pull off! */

typedef struct { uchar a : 1; } bit_t;			// bit type (aka: bool)
typedef struct { uchar a : 4; } nibble_t;		// nibble type (4 bits to a nibble!)
typedef struct { uchar a : 8; } byte_t;			// byte type (8 bits to a byte, or 2 nibbles to a byte!)

/* And just for fun... */
typedef union { bit_t bit; nibble_t nibble; byte_t byte; } bytesizes_ut;	// In a union, members share memory! (not very common in C++)
typedef struct { bit_t bit; nibble_t nibble; byte_t byte; } bytesizes_st;	// In a struct, memory is sequential! (very common in C++)

int main(void)
{
	typesizemap_t typeSizeMap = typesizemap_t
	{
		/* PRIMITIVE TYPES */
		automap(bool), automap(char), automap(short), automap(int), automap(float), automap(double), automap(long int), automap(long long int),
		automap(long double),
		
		/* CUSTOM TYPES */
		{ "bit", sizeof(bit_t) }, { "nibble", sizeof(nibble_t) }, { "byte", sizeof(byte_t) },
		{ "union", sizeof(bytesizes_ut) }, { "struct", sizeof(bytesizes_st) },

		/* REFERENCE TYPE */
		{ "pointer", sizeof(void*) },
		
	};

	std::string input("");
	bool doLoop=true;
	
	while(doLoop)
	{

		prompt("What would you like to know about? ('all' for all supported types, 'exit' to exit) ");
		getline(std::cin, input); // We want to use 'getline' to handle spaces, otherwise cin << buffers them.
		
		if (input.compare("exit") == 0)
		{
			doLoop = false;
			continue;
		}
		else if (input.compare("all") == 0)
		{
			std::cout << TBL_COL_LEFT("TYPE") << TBL_COL_RIGHT("SIZE(BYTES)") << std::endl;
			for (auto a : typeSizeMap)
				std::cout << TBL_COL_LEFT(a.first) << TBL_COL_RIGHT(a.second) << std::endl;
			continue;
		}
		else if (typeSizeMap.find(input) != typeSizeMap.end())
		{
			std::cout << TBL_COL_LEFT("TYPE") << TBL_COL_RIGHT("SIZE(BYTES)") << std::endl
				<< TBL_COL_LEFT(input) << TBL_COL_RIGHT(typeSizeMap[input]) << std::endl;
			continue;
		}
		else
			std::cout << "Sorry, " << input << " isn't a recognized type." << std::endl;
	}

	return 0;
}
