#include <iostream>
#include <vector>
#include <cassert>

/* Hey, look at this nifty C++! We're really taking advantage of the language now!
 * I'm opting to take advantage of templating here. This is just a forward declaration here.
 * I use templating so we can use any type of array we want.
 */

// PARAMS:
// 	const T arr[]		: Array of objects to vectorize
// So this is a pretty complicated function.
// 	I pretty much know the fastest way to instantiate a vector from memory is to use some variation of iterable (which is NOT my strong suit)
// 	This also really takes advantage of some advanced, advanced concepts of C++. I even made sure to define the C++17 standard in the makefile here
// 		because I wasn't too sure this was allowed in anything but C++20 (it is okay, compiles fine!)
// Pretty much we take advantage of templates and constexpr to create a modular way to convert arrays to vectors which is workable at compile-time and runtime.
//	It's good to note that template<typename T, size_t N> is a predefined template where T some type of array and N is the size of that array (as arguments passed to the function)
//	We can then use (T (&arr)[N]) as a reference to the array arr of type T and length N. Highly important to note that declaring the array size N is NOT OPTIONAL.
//	Because the size must be definite, the compiler will spit out errors about how arr(*)([]) and arr[3] are different types if we don't declare the array with size [N]
//	Pretty nifty, huh?
template<typename T, size_t N>
constexpr std::vector<T> arrToVec(T (&arr)[N])
{
	std::vector<T> vect = std::vector<T>();
	vect.insert(vect.begin(), std::begin(arr), std::end(arr));
	return vect;
}

int main(void)
{
	int iArr[] { 1, 2, 3 };
	std::vector<int> iVec = arrToVec<int>(iArr);


	for(auto i : iVec)
		std::cout << i << " ";
	assert(iVec[0] == iArr[0] && iVec[1] == iArr[1] && iVec[2] == iArr[2]);
	std::cout << std::endl;

	const char* cStrArr[] { "Hello", ",", "world", "!" };
	std::vector<const char*> cStrVec = arrToVec<const char*>(cStrArr);
	
	std::cout << "LENGTH: " << cStrVec.size() << std::endl;
	for(auto cstr : cStrVec)
		std::cout << cstr << " ";
	assert(cStrVec[0] == cStrArr[0] && cStrVec[1] == cStrArr[1] && cStrVec[2] == cStrArr[2] && cStrVec[3] == cStrArr[3]);
	std::cout << std::endl;


	return 0;
}

