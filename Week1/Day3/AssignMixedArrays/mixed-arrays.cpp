#include <iostream>
#include <cassert>

// NO Structs, NO classes

// Helper functions for my unique solution to the problem...
//	I use unsigned char to hold the enum data 
//	the next pointer should hold the value of the corresponding data.
// 	This really just enforces that I'm using the correct sequence of data,
// 	because sequence matters!
#define destructure_int(val) new unsigned char(INT), new int(val)
#define destructure_float(val) new unsigned char(FLOAT), new float(val)
#define destructure_double(val) new unsigned char(DOUBLE), new double(val)

// I use an enum type here for readability,
// 	but this just evaluates down to a simple identity...
// 		  	       ==0   ==1     ==2
typedef enum : unsigned char { INT, FLOAT, DOUBLE } next_type_et; // ': unsigned char' just makes this take up as much space as a char(1B)

int main(void)
{
	/* 2.1: Dissimilar Arrays */

	// Here's a great way to take advantage of the reference type in C to allow for arrays of different value types!
	// 	The real trick here is that none of these are of a different type. They are ALL pointers!
	void* mixedArr[6] { new int(1), new float(1.5f), new int(2), new float(2.5f), new int(3), new float(3.5f) };
	
	const size_t mixedArrSize = sizeof(mixedArr) / sizeof(mixedArr[0]);
	assert(mixedArrSize > 0);

	std::cout << "Array 1 values:" << std::endl;
	// We used a pattern in the array: Every 2nd pointer points to an int, otherwise it points to a float!
	for (int i=0; i < 6; i++)
	{
		assert(sizeof(mixedArr) / sizeof(mixedArr[0]) >= i);
		assert(mixedArr[i] != NULL);
		if (i % 2 == 0)
			std::cout << *((int*) mixedArr[i]); // We can read this as: The integer value pointed to by the ith index of mixedArr.
		else
			std::cout << *((float*) mixedArr[i]); // Pretty much the same as above, except the float value!

		std::cout << " ";
	}
	std::cout << std::endl;

	/* 2.2: Types in Array */

	// I may not be qualified enough to give an absolute answer on this,
	// 	but I don't believe it is possible to recognize the type without using a struct or some clever programming. (I am almost 100% certain of this)
	// Even with the most clever of programming, you need to be explicit about the type.
	//
	// So to answer the question: Can we totally 100% autonomously tell the type of the variable implicitly? No, not like in
	// 	C# or Java where we have a common 'object' type which holds metadata about its own type.
	// Can we do so by structuring the design of our data using explicit delcarations? Absolutely, and using the
	// 	C++ templating system, structs, and unions, we can so very easily!
	
	/* 2.2 (cont.) "clever programming" */
	
	// This is a special way to circumvent that strictness while still abiding by the rules you set in the assignment, but it requires being explicit 
	//	AND designing a completely different way of interpreting our untyped arrays (as I stated before, 'untyped' arrays are actually pointer type arrays).
	// 
	// I call this method struct destructuring and I can take advantage of my knowledge of how structs are stored in contiguous memory to
	// 	pretty much just identically copy how it'd typically be stored without actually using structs.
	// 	We could even cast this as a struct and it'd come out correctly, given our data types match up!
	// 	struct { void* type; void* val; }
	//
	// This is the concept behind tagged unions!
	
	void* typedMixedArray[]
	{
		destructure_int(1),
		destructure_float(1.5),
		destructure_double(1.75),
		destructure_int(2),
		destructure_float(2.5),
		destructure_double(2.75),
	};
	
	const size_t typedMixedArraySize = sizeof(typedMixedArray) / sizeof(typedMixedArray[0]);
	assert(typedMixedArraySize > 0);

	std::cout << "Array 2 values:" << std::endl;
	for (unsigned i=0; i < typedMixedArraySize; i+=2)
	{
		assert(typedMixedArraySize >= i+1);
		assert(typedMixedArray[i] != NULL && typedMixedArray[i+1] != NULL);

		next_type_et nextType = *((next_type_et*) typedMixedArray[i]);
		void* nextVal = typedMixedArray[i+1];
		
		if (nextType == INT)
			std::cout << "INT " << *((int*) nextVal) << std::endl;
		else if (nextType == FLOAT)
			std::cout << "FLOAT " << *((float*) nextVal) << std::endl;
		else if (nextType == DOUBLE)
			std::cout << "DOUBLE " << *((double*) nextVal) << std::endl;
		else
			continue;
	}

	return 0;
}
